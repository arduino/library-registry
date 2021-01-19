// Copyright 2020 ARDUINO SA (http://www.arduino.cc/)
//
// This software is released under the GNU General Public License version 3.
// The terms of this license can be found at:
// https://www.gnu.org/licenses/gpl-3.0.en.html
//
// You can be released from the requirements of the above licenses by purchasing
// a commercial license. Buying such a license is mandatory if you want to
// modify or otherwise use the software for commercial activities involving the
// Arduino software without disclosing the source code of your own applications.
// To purchase a commercial license, send an email to license@arduino.cc.

package main

import (
	"bytes"
	"encoding/json"
	"flag"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"os"
	"os/exec"
	"strings"

	"github.com/sourcegraph/go-diff/diff"

	"github.com/arduino/go-paths-helper"
	properties "github.com/arduino/go-properties-orderedmap"
)

// Git hosts that are supported for library repositories.
var supportedHosts []string = []string{
	"bitbucket.org",
	"github.com",
	"gitlab.com",
}

// Libraries under these organizations will have the "Arduino" type and be linted with Arduino Lint in the "official" setting.
var officialOrganizations []string = []string{
	"github.com/arduino",
	"github.com/arduino-libraries",
	"github.com/bcmi-labs",
	"github.com/vidor-libraries",
}

// Libraries under these organizations will have the "Partner" type.
var partnerOrganizations []string = []string{
	"github.com/Azure",
	"github.com/ms-iot",
	"github.com/ameltech",
}

// Libraries under these organizations will have the "Recommended" type.
var recommendedOrganizations []string = []string{
	"github.com/adafruit",
}

// requestType is the type of the request data.
type requestType struct {
	Type        string           `json:"type"`        // Request type.
	Submissions []submissionType `json:"submissions"` // Data for submitted libraries.
	IndexEntry  string           `json:"indexEntry"`  // Entry that will be made to the Library Manager index source file when the submission is accepted.
}

// submissionType is the type of the data for each individual library submitted in the request.
type submissionType struct {
	SubmissionURL string `json:"submissionURL"` // Library repository URL as submitted by user. Used to identify the submission to the user.
	NormalizedURL string `json:"normalizedURL"` // Submission URL in the standardized format that will be used in the index entry.
	Name          string `json:"name"`          // Library name.
	Official      bool   `json:"official"`      // Whether the library is official.
	Tag           string `json:"tag"`           // Name of the submission repository's latest tag, which is used as the basis for the index entry and validation.
	Error         string `json:"error"`         // Error message.
}

// Command line flags.
var baseRef = flag.String("baseref", "", "")
var repoPath = flag.String("repopath", "", "")
var listName = flag.String("listname", "", "")

func main() {
	// Validate flag input.
	flag.Parse()

	if *baseRef == "" {
		errorExit("--baseref flag is required")
	}

	if *repoPath == "" {
		errorExit("--repopath flag is required")
	}

	if *listName == "" {
		errorExit("--listname flag is required")
	}

	listPath := paths.New(*repoPath, *listName)
	exist, err := listPath.ExistCheck()
	if err != nil {
		panic(err)
	}
	if !exist {
		errorExit(fmt.Sprintf("list file %s not found", listPath))
	}

	// Get the PR diff.
	err = os.Chdir(*repoPath)
	if err != nil {
		panic(err)
	}

	rawDiff, err := exec.Command("git", "diff", "--unified=0", "--ignore-blank-lines", "--ignore-space-at-eol", *baseRef).Output()
	if err != nil {
		panic(err)
	}

	// Parse the PR diff.
	var request requestType
	var submissionURLs []string
	request.Type, submissionURLs = parseDiff(rawDiff, *listName)

	// Process the submissions.
	var indexEntries []string
	for _, submissionURL := range submissionURLs {
		submission, indexEntry := populateSubmission(submissionURL, listPath)
		request.Submissions = append(request.Submissions, submission)
		indexEntries = append(indexEntries, indexEntry)
	}

	// Assemble the index entry for the submissions.
	request.IndexEntry = strings.Join(indexEntries, "%0A")

	// Marshal the request data into a JSON document.
	var marshalledRequest bytes.Buffer
	jsonEncoder := json.NewEncoder(io.Writer(&marshalledRequest))
	// By default, the json package HTML-sanitizes strings during marshalling (https://golang.org/pkg/encoding/json/#Marshal)
	// It's not possible to change this behavior when using the simple json.MarshalIndent() approach.
	jsonEncoder.SetEscapeHTML(false)
	jsonEncoder.SetIndent("", "") // Single line.
	err = jsonEncoder.Encode(request)
	if err != nil {
		panic(err)
	}

	fmt.Println(marshalledRequest.String())
}

// errorExit prints the error message in a standardized format and exits with status 1.
func errorExit(message string) {
	fmt.Printf("ERROR: %s\n", message)
	os.Exit(1)
}

// parseDiff parses the request diff and returns the request type and list of submission URLs.
func parseDiff(rawDiff []byte, listName string) (string, []string) {
	var submissionURLs []string

	diffs, err := diff.ParseMultiFileDiff(rawDiff)
	if err != nil {
		panic(err)
	}

	if (len(diffs) != 1) || (diffs[0].OrigName[2:] != listName) || (diffs[0].OrigName[2:] != diffs[0].NewName[2:]) { // Git diffs have a a/ or b/ prefix on file names.
		// This is not a Library Manager submission.
		return "other", nil
	}

	var addedCount int
	var deletedCount int
	// Get the added URLs from the diff
	for _, hunk := range diffs[0].Hunks {
		hunkBody := string(hunk.Body)
		for _, rawDiffLine := range strings.Split(hunkBody, "\n") {
			diffLine := strings.TrimRight(rawDiffLine, " \t")
			if len(diffLine) < 2 {
				continue // Ignore blank lines.
			}

			switch diffLine[0] {
			case '+':
				addedCount++
				submissionURLs = append(submissionURLs, strings.TrimSpace(diffLine[1:]))
			case '-':
				deletedCount++
			default:
				continue
			}
		}
	}

	var requestType string
	if addedCount > 0 && deletedCount == 0 {
		requestType = "submission"
	} else if addedCount == 0 && deletedCount > 0 {
		requestType = "removal"
	} else {
		requestType = "modification"
	}

	return requestType, submissionURLs
}

// populateSubmission does the checks on the submission that aren't provided by Arduino Lint and gathers the necessary data on it.
func populateSubmission(submissionURL string, listPath *paths.Path) (submissionType, string) {
	indexSourceSeparator := "|"
	var submission submissionType

	submission.SubmissionURL = submissionURL

	// Normalize and validate submission URL.
	submissionURLObject, err := url.Parse(submission.SubmissionURL)
	if err != nil {
		submission.Error = fmt.Sprintf("Invalid submission URL (%s)", err)
		return submission, ""
	}

	// Check if URL is accessible.
	httpResponse, err := http.Get(submissionURLObject.String())
	if err != nil {
		submission.Error = fmt.Sprintf("Unable to load submission URL: %s", err)
		return submission, ""
	}
	if httpResponse.StatusCode != http.StatusOK {
		submission.Error = "Unable to load submission URL. Is the repository public?"
		return submission, ""
	}

	// Resolve redirects and normalize.
	normalizedURLObject, err := normalizeURL(httpResponse.Request.URL)
	if err != nil {
		submission.Error = err.Error()
		return submission, ""
	}

	submission.NormalizedURL = normalizedURLObject.String()

	// Check if URL is from a supported Git host.
	if !uRLIsUnder(normalizedURLObject, supportedHosts) {
		submission.Error = normalizedURLObject.Host + " is not currently supported as a Git hosting website for Library Manager.%0ASee: https://github.com/arduino/Arduino/wiki/Library-Manager-FAQ#how-can-i-add-my-library-to-library-manager"
		return submission, ""
	}

	// Check if the URL is already in the index.
	listLines, err := listPath.ReadFileAsLines()
	occurrences := 0
	for _, listURL := range listLines {
		listURLObject, err := url.Parse(strings.TrimSpace(listURL))
		if err != nil {
			panic(err) // All list items have already passed parsing so something is broken if this happens.
		}
		normalizedListURLObject, err := normalizeURL(listURLObject)
		if err != nil {
			panic(fmt.Errorf("When processing list item %s: %s", listURL, err)) // All list items have already been through normalization without error so something is broken if this happens.
		}

		if normalizedListURLObject.String() == normalizedURLObject.String() {
			occurrences++
			if occurrences > 1 {
				submission.Error = "Submission URL is already in the Library Manager index."
				return submission, ""
			}
		}
	}

	// Determine the library types attributes.
	submission.Official = uRLIsUnder(normalizedURLObject, officialOrganizations)
	var types []string
	if submission.Official {
		types = append(types, "Arduino")
	}
	if uRLIsUnder(normalizedURLObject, partnerOrganizations) {
		types = append(types, "Partner")
	}
	if uRLIsUnder(normalizedURLObject, recommendedOrganizations) {
		types = append(types, "Recommended")
	}
	if types == nil {
		types = append(types, "Contributed")
	}

	submissionClonePath, err := paths.MkTempDir("", "")
	if err != nil {
		panic(err)
	}

	err = exec.Command("git", "clone", "--depth", "1", normalizedURLObject.String(), submissionClonePath.String()).Run()
	if err != nil {
		panic(err)
	}

	// Determine latest tag name in submission repo
	err = os.Chdir(submissionClonePath.String())
	if err != nil {
		panic(err)
	}
	err = exec.Command("git", "fetch", "--tags").Run()
	if err != nil {
		panic(err)
	}
	tagList, err := exec.Command("git", "rev-list", "--tags", "--max-count=1").Output()
	if err != nil {
		panic(err)
	}
	if string(tagList) == "" {
		submission.Error = "The repository has no tags. You need to create a [release](https://docs.github.com/en/github/administering-a-repository/managing-releases-in-a-repository) or [tag](https://git-scm.com/docs/git-tag) that matches the `version` value in the library's library.properties file."
		return submission, ""
	}
	latestTag, err := exec.Command("git", "describe", "--tags", strings.TrimSpace(string(tagList))).Output()
	if err != nil {
		panic(err)
	}
	submission.Tag = strings.TrimSpace(string(latestTag))

	// Checkout latest tag.
	err = exec.Command("git", "checkout", submission.Tag).Run()
	if err != nil {
		panic(err)
	}

	// Get submission library name. It is necessary to record this in the index source entry because the library is locked to this name.
	libraryPropertiesPath := submissionClonePath.Join("library.properties")
	if !libraryPropertiesPath.Exist() {
		submission.Error = "Library is missing a library.properties metadata file."
		return submission, ""
	}
	libraryProperties, err := properties.LoadFromPath(libraryPropertiesPath)
	if err != nil {
		submission.Error = fmt.Sprintf("Invalid library.properties file (%s)", err)
		return submission, ""
	}
	var ok bool
	submission.Name, ok = libraryProperties.GetOk("name")
	if !ok {
		submission.Error = "library.properties is missing a name field"
		return submission, ""
	}

	// Assemble Library Manager index source entry string
	indexEntry := strings.Join(
		[]string{
			submission.NormalizedURL,
			strings.Join(types, ","),
			submission.Name,
		},
		indexSourceSeparator,
	)

	return submission, indexEntry
}

// normalizeURL converts the URL into the standardized format used in the index.
func normalizeURL(rawURL *url.URL) (url.URL, error) {
	normalizedPath := strings.TrimRight(rawURL.Path, "/")
	if !strings.HasSuffix(normalizedPath, ".git") {
		normalizedPath += ".git"
	}
	if len(strings.Split(normalizedPath, "/")) != 3 {
		return url.URL{}, fmt.Errorf("Submission URL must point to the root of the repository")
	}

	return url.URL{
			Scheme: "https",
			Host:   rawURL.Host,
			Path:   normalizedPath,
		},
		nil
}

func uRLIsUnder(childURL url.URL, parentCandidates []string) bool {
	for _, parentCandidate := range parentCandidates {
		if !strings.HasSuffix(parentCandidate, "/") {
			parentCandidate += "/"
		}
		parentCandidateURL, err := url.Parse("https://" + parentCandidate)
		if err != nil {
			panic(err)
		}

		isUnderPath, err := paths.New(childURL.Path).IsInsideDir(paths.New(parentCandidateURL.Path))
		if err != nil {
			panic(err)
		}
		if (childURL.Host == parentCandidateURL.Host) && isUnderPath {
			return true
		}
	}

	return false
}
