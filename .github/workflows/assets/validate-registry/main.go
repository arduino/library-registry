package main

import (
	"fmt"
	"os"
	"reflect"

	"github.com/arduino/libraries-repository-engine/libraries"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintln(os.Stderr, "error: Registry data file path argument is missing")
		os.Exit(1)
	}
	reposFile := os.Args[1]

	info, err := os.Stat(reposFile)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: While loading registry data file: %s\n", err)
		os.Exit(1)
	}

	if info.IsDir() {
		fmt.Fprintf(os.Stderr, "error: Registry data file argument %s is a folder, not a file\n", reposFile)
		os.Exit(1)
	}

	rawRepos, err := libraries.LoadRepoListFromFile(reposFile)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: While loading registry data file: %s\n", err)
		os.Exit(1)
	}

	filteredRepos, err := libraries.ListRepos(reposFile)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: While filtering registry data file: %s\n", err)
		os.Exit(1)
	}

	if !reflect.DeepEqual(rawRepos, filteredRepos) {
		fmt.Fprintln(os.Stderr, "error: Registry data file contains duplicate URLs")
		os.Exit(1)
	}

	nameMap := make(map[string]bool)
	for _, entry := range rawRepos {
		if _, found := nameMap[entry.LibraryName]; found {
			fmt.Fprintf(os.Stderr, "error: Registry data file contains duplicates of name %s\n", entry.LibraryName)
			os.Exit(1)
		}
		nameMap[entry.LibraryName] = true
	}
}
