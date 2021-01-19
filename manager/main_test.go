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
	"fmt"
	"net/url"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func Test_parseDiff(t *testing.T) {
	testName := "Multiple files"
	diff := []byte(`
diff --git a/README.md b/README.md
index d4edde0..807b76d 100644
--- a/README.md
+++ b/README.md
@@ -1,0 +2 @@
+hello
diff --git a/repositories.txt b/repositories.txt
index cff484d..e14c179 100644
--- a/repositories.txt
+++ b/repositories.txt
@@ -8,0 +9 @@ https://github.com/arduino-libraries/Ethernet
+https://github.com/foo/bar
`)

	requestType, submissionURLs := parseDiff(diff, "repositories.txt")
	assert.Equal(t, "other", requestType, testName)
	assert.Nil(t, submissionURLs, testName)

	testName = "Not list"
	diff = []byte(`
diff --git a/README.md b/README.md
index d4edde0..807b76d 100644
--- a/README.md
+++ b/README.md
@@ -1 +1,2 @@
	# Arduino Library Manager list
+hello
`)

	requestType, submissionURLs = parseDiff(diff, "repositories.txt")
	assert.Equal(t, "other", requestType, testName)
	assert.Nil(t, submissionURLs, testName)

	testName = "List filename change"
	diff = []byte(`
diff --git a/repositories.txt b/foobar.txt
similarity index 99%
rename from repositories.txt
rename to foobar.txt
index cff484d..e14c179 100644
--- a/repositories.txt
+++ b/foobar.txt
@@ -8,0 +9 @@ https://github.com/arduino-libraries/Ethernet
+https://github.com/foo/bar
`)

	requestType, submissionURLs = parseDiff(diff, "repositories.txt")
	assert.Equal(t, "other", requestType, testName)
	assert.Nil(t, submissionURLs, testName)

	testName = "Submission"
	diff = []byte(`
diff --git a/repositories.txt b/repositories.txt
index cff484d..9f67763 100644
--- a/repositories.txt
+++ b/repositories.txt
@@ -8,0 +9,2 @@ https://github.com/arduino-libraries/Ethernet
+https://github.com/foo/bar
+https://github.com/foo/baz
`)

	requestType, submissionURLs = parseDiff(diff, "repositories.txt")
	assert.Equal(t, "submission", requestType, testName)
	assert.ElementsMatch(t, submissionURLs, []string{"https://github.com/foo/bar", "https://github.com/foo/baz"}, testName)

	testName = "Submission w/ no newline at end of file"
	diff = []byte(`
diff --git a/repositories.txt b/repositories.txt
index cff484d..1b0b80b 100644
--- a/repositories.txt
+++ b/repositories.txt
@@ -3391,0 +3392 @@ https://github.com/lbernstone/plotutils
+https://github.com/foo/bar
\ No newline at end of file
`)

	requestType, submissionURLs = parseDiff(diff, "repositories.txt")
	assert.Equal(t, "submission", requestType, testName)
	assert.ElementsMatch(t, submissionURLs, []string{"https://github.com/foo/bar"}, testName)

	testName = "Submission w/ blank line"
	diff = []byte(`
diff --git a/repositories.txt b/repositories.txt
index cff484d..1b0b80b 100644
--- a/repositories.txt
+++ b/repositories.txt
@@ -3391,0 +3392 @@ https://github.com/lbernstone/plotutils
+https://github.com/foo/bar
\ No newline at end of file
`)

	requestType, submissionURLs = parseDiff(diff, "repositories.txt")
	assert.Equal(t, "submission", requestType, testName)
	assert.ElementsMatch(t, submissionURLs, []string{"https://github.com/foo/bar"}, testName)

	testName = "Removal"
	diff = []byte(`
diff --git a/repositories.txt b/repositories.txt
index cff484d..38e11d8 100644
--- a/repositories.txt
+++ b/repositories.txt
@@ -8 +7,0 @@ https://github.com/firmata/arduino
-https://github.com/arduino-libraries/Ethernet
`)

	requestType, submissionURLs = parseDiff(diff, "repositories.txt")
	assert.Equal(t, "removal", requestType, testName)
	assert.Nil(t, submissionURLs, testName)

	testName = "Modification"
	diff = []byte(`
diff --git a/repositories.txt b/repositories.txt
index cff484d..8b401a1 100644
--- a/repositories.txt
+++ b/repositories.txt
@@ -8 +8 @@ https://github.com/firmata/arduino
-https://github.com/arduino-libraries/Ethernet
+https://github.com/foo/bar
`)

	requestType, submissionURLs = parseDiff(diff, "repositories.txt")
	assert.Equal(t, "modification", requestType, testName)
	assert.Equal(t, submissionURLs, []string{"https://github.com/foo/bar"}, testName)
}

func Test_normalizeURL(t *testing.T) {
	testTables := []struct {
		testName              string
		rawURL                string
		expectedNormalizedURL string
		expectedError         string
	}{
		{"Trailing slash", "https://github.com/foo/bar/", "https://github.com/foo/bar.git", ""},
		{".git suffix", "https://github.com/foo/bar.git", "https://github.com/foo/bar.git", ""},
		{"Too few path elements", "https://github.com/foo", "", "Submission URL must point to the root of the repository"},
		{"Too many path elements", "https://github.com/foo/bar/baz", "", "Submission URL must point to the root of the repository"},
		{"http://", "http://github.com/foo/bar", "https://github.com/foo/bar.git", ""},
		{"git://", "git://github.com/foo/bar", "https://github.com/foo/bar.git", ""},
	}

	for _, testTable := range testTables {
		rawURL, err := url.Parse(testTable.rawURL)
		require.Nil(t, err)
		expectedNormalizedURL, err := url.Parse(testTable.expectedNormalizedURL)
		require.Nil(t, err)

		normalizedURL, err := normalizeURL(rawURL)
		assert.Equal(t, *expectedNormalizedURL, normalizedURL, testTable.testName)
		if testTable.expectedError == "" {
			assert.Nil(t, err, testTable.testName)
		} else {
			assert.Equal(t, fmt.Errorf(testTable.expectedError), err, testTable.testName)
		}
	}
}

func Test_uRLIsUnder(t *testing.T) {
	testTables := []struct {
		testName         string
		childURL         string
		parentCandidates []string
		assertion        assert.BoolAssertionFunc
	}{
		{"Match, root path", "https://github.com/foo/bar", []string{"example.com", "github.com"}, assert.True},
		{"Mismatch, root path", "https://github.com/foo/bar", []string{"example.com", "example.org"}, assert.False},
		{"Match, subfolder", "https://github.com/foo/bar", []string{"example.com/foo", "github.com/foo"}, assert.True},
		{"Mismatch, subfolder", "https://github.com/foo/bar", []string{"example.com/foo", "github.org/bar"}, assert.False},
	}

	for _, testTable := range testTables {
		childURL, err := url.Parse(testTable.childURL)
		require.Nil(t, err)

		t.Run(testTable.testName, func(t *testing.T) {
			testTable.assertion(t, uRLIsUnder(*childURL, testTable.parentCandidates))
		})
	}
}
