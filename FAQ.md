# Arduino Library Manager FAQ

## Table of Contents

<!-- toc -->

- [General](#general)
  - [What is the Arduino Library Manager?](#what-is-the-arduino-library-manager)
  - [How is the Library Manager index generated?](#how-is-the-library-manager-index-generated)
- [Submission](#submission)
  - [How can I add a library to Library Manager?](#how-can-i-add-a-library-to-library-manager)
  - [What are the requirements for a library to be added to Library Manager?](#what-are-the-requirements-for-a-library-to-be-added-to-library-manager)
  - [Who is allowed to add a library to Library Manager?](#who-is-allowed-to-add-a-library-to-library-manager)
- [Updates](#updates)
  - [How can I publish a new release once my library is in the list?](#how-can-i-publish-a-new-release-once-my-library-is-in-the-list)
  - [What are the requirements for publishing new releases of libraries already in the Library Manager list?](#what-are-the-requirements-for-publishing-new-releases-of-libraries-already-in-the-library-manager-list)
  - [Why aren't releases of my library being picked up by Library Manager?](#why-arent-releases-of-my-library-being-picked-up-by-library-manager)
  - [Can I check on library releases being added to Library Manager?](#can-i-check-on-library-releases-being-added-to-library-manager)
  - [How can I remove a release of my library from Library Manager?](#how-can-i-remove-a-release-of-my-library-from-library-manager)
  - [How can I change a library's name?](#how-can-i-change-a-librarys-name)
- [Limitations](#limitations)
  - [Is my Git repository OK?](#is-my-git-repository-ok)
  - [Are Git submodules supported?](#are-git-submodules-supported)
- [Usage](#usage)
  - [Can I add my own URL with my own library index?](#can-i-add-my-own-url-with-my-own-library-index)
  - [When I install a library that I know depends on another library, will this other library be installed as well?](#when-i-install-a-library-that-i-know-depends-on-another-library-will-this-other-library-be-installed-as-well)
  - [Can I install multiple versions of one library and use the proper one in my sketches?](#can-i-install-multiple-versions-of-one-library-and-use-the-proper-one-in-my-sketches)
  - [How can I remove a library I installed via Library Manager?](#how-can-i-remove-a-library-i-installed-via-library-manager)
- [Security & Malware Reporting](#security--malware-reporting)

<!-- tocstop -->

## General

### What is the Arduino Library Manager?

Library Manager is a feature of the Arduino development software which makes it easy for users to find, install, and update both official and 3rd party libraries.

- In the Arduino IDE: **Sketch > Include Library > Manage Libraries...**
- In Arduino CLI: `arduino-cli lib --help`
- In Arduino Web Editor: all Library Manager libraries are pre-installed.

When a library is [added to the library list](README.md#adding-a-library-to-library-manager), every release of the library will automatically be made available for installation via Library Manager. Users can set their preferences to display an update notification when a new version of any installed library on the list is available and easily update to the new version with just a couple clicks.

More information:

- https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library#installing-a-library
- https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries#using-the-library-manager
- https://arduino.github.io/arduino-cli/latest/commands/arduino-cli_lib/
- https://docs.arduino.cc/arduino-cloud/guides/editor/#library-manager

### How is the Library Manager index generated?

[The Library Manager index](http://downloads.arduino.cc/libraries/library_index.json) contains the data for every release of every one of the thousands of libraries that have been added to the Library Manager list. This index is used by Library Manager to provide installation and updates of the libraries as well as to generate automated documentation pages for the [Arduino Library Reference](https://www.arduino.cc/reference/en/libraries/).

Every hour, the automated Library Manager indexer system:

1. checks every repository in the Library Manager list for new tags, updating [the logs](#can-i-check-on-library-releases-being-added-to-library-manager) accordingly
1. checks whether those tags meet [the requirements for addition to the index](#update-requirements)
1. adds entries to the index for compliant tags
1. pushes the updated index to Arduino's download server

## Submission

<a id="how-can-i-add-my-library-to-library-manager"></a>

### How can I add a library to Library Manager?

Follow the instructions [here](README.md#adding-a-library-to-library-manager).

<a id="submission-requirements"></a>

### What are the requirements for a library to be added to Library Manager?

- [ ] The library must be something of potential value to the Arduino community.
- [ ] The submitter must behave in a responsible manner in their interactions with the Library Manager Registry.
- [ ] The library must be fully compliant with the [Arduino Library Specification](https://arduino.github.io/arduino-cli/latest/library-specification).
- [ ] The library must have [a library.properties file](https://arduino.github.io/arduino-cli/latest/library-specification/#library-metadata), in compliance with the Arduino Library 1.5 format.
- [ ] The library.properties file must be located in the root of the repository.
- [ ] The library must not have the same library.properties `name` value (regardless of case) as another library previously added to the Library Manager list.
- [ ] For 3rd party libraries, the `name` field in library.properties must not start with `Arduino`.
- [ ] The library repository must not contain any `.exe` files.
- [ ] The library repository must not contain a [`.development` file](https://arduino.github.io/arduino-cli/latest/library-specification/#development-flag-file).
- [ ] The library repository must not contain any [symlinks](https://wikipedia.org/wiki/Symbolic_link).
- [ ] The library repository must not contain any files detected as infected by our antivirus scan.
- [ ] The library repository must have a [Git tag](https://git-scm.com/book/en/v2/Git-Basics-Tagging) (or [release](https://docs.github.com/repositories/releasing-projects-on-github/managing-releases-in-a-repository)) and must have been compliant with all the above requirements at the time of that tag.
- [ ] The library repository must be hosted on a major Git-hosting website like GitHub, BitBucket or GitLab (other hosting sites may be considered on request).

Arduino has created a command line tool to check libraries for compliance with all the Library Manager requirements:

https://github.com/arduino/arduino-lint

Arduino Lint is also available as a GitHub Actions action that can be used in the CI systems of Arduino library repositories to ensure continued compliance:

https://github.com/arduino/arduino-lint-action

### Who is allowed to add a library to Library Manager?

Everyone is welcome to submit libraries for inclusion in Library Manager, regardless of whether you are involved in the library's development.

Note that libraries will need to be compliant with [all requirements](#update-requirements) in order to be accepted. If not, you will need to work with the library maintainer to achieve compliance.

## Updates

### How can I publish a new release once my library is in the list?

1. Make sure the library is compliant with [all requirements](#update-requirements).
1. Update the `version` in the library's [`library.properties`](https://arduino.github.io/arduino-cli/latest/library-specification/#library-metadata)).
1. Tag the library's repository once more and push the new tag (or create a release if the library's Git-hosting site offers a way to do it, for example with [GitHub "releases"](https://docs.github.com/repositories/releasing-projects-on-github/managing-releases-in-a-repository)).

[Our indexer](#how-is-the-library-manager-index-generated) checks for new releases every hour and will eventually fetch and publish the new release.

<a id="update-requirements"></a>

### What are the requirements for publishing new releases of libraries already in the Library Manager list?

- [ ] The library must be compliant with all the same [requirements that apply to submissions](#submission-requirements).
- [ ] The `name` property in library.properties must not have changed from the value it had when the library was submitted. If you must change the library name, see [this](#how-can-i-change-my-librarys-name).
- [ ] The `version` property in library.properties must not be the same as it was in a tag previously added to the Library Manager index.

### Why aren't releases of my library being picked up by Library Manager?

The Library Manager indexer job will reject any releases which aren't compliant with all [the requirements](#update-requirements).

You can check [the indexer logs](#can-i-check-on-library-releases-being-added-to-library-manager) for information about what happened.

### Can I check on library releases being added to Library Manager?

There is a dedicated web page for each library that shows the logs from the Library Manager indexer. The URL of the logs page is based on the library's repository URL:

```
http://downloads.arduino.cc/libraries/logs/<host>/<repository slug>/
```

For example, the Servo library is hosted at https://github.com/arduino-libraries/Servo, so its logs are at:

http://downloads.arduino.cc/libraries/logs/github.com/arduino-libraries/Servo/

<a id="i-did-something-wrong-how-can-i-change-or-unpublish-an-already-published-library"></a>

### How can I remove a release of my library from Library Manager?

If you discover a problem with the library release, simply fix the problem and make a new [release](#how-can-i-publish-a-new-release-once-my-library-is-in-the-list). Library Manager defaults to installing the latest version of the library and offers updates to those with an older version installed, so this is the fastest and most effective method for distributing a fix to the users.

In the event a library release is later discovered to contain something that absolutely can not be published, we do allow removing releases from Library Manager on request by the following procedure:

1. Delete the [tag](https://git-scm.com/book/en/v2/Git-Basics-Tagging) of the problematic release from the library's repository.
1. Open an issue [here](https://github.com/arduino/library-registry/issues/new?labels=topic%3A+release+removal&template=release-removal.yml&title=Library+release+removal+request), specifying the name of the library and the version number of the release that should be removed.

<a id="how-can-i-change-my-librarys-name"></a>

### How can I change a library's name?

For the sake of continuity, libraries in the Library Manager list are locked to the name they had at the time they were added to the list. Changing the library name can be disruptive to its users because this is the unique identifier for the library used by the Arduino development software [command line interfaces](https://arduino.github.io/arduino-cli/latest/commands/arduino-cli_lib/), sketch [metadata](https://arduino.github.io/arduino-cli/latest/sketch-specification/#metadata), library [dependencies](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format), and installation location.

If you wish to change the name it will need to be done manually by request:

1. Change the `name` value in the [library.properties file](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format) and update the `version`.
1. Create a release or tag.
1. Open an issue [here](https://github.com/arduino/library-registry/issues/new?labels=topic%3A+rename&template=rename.yml&title=Library+name+change+request) specifying the URL of the library's repository.

## Limitations

### Is my Git repository OK?

Your repo is OK if it meets all [the requirements listed here](#submission-requirements).

### Are Git submodules supported?

No. The library archive distributed by Library Manager will only contain an empty folder where the submodule should be.

## Usage

### Can I add my own URL with my own library index?

No. At the moment, the Arduino development software handles one URL only, and that's written into the code (dev jargon: it's hardcoded), this is a known limitation.
However, if you know your way through the code, you can change that URL with another one.

### When I install a library that I know depends on another library, will this other library be installed as well?

As of Arduino IDE 1.8.10 and Arduino CLI 0.7.0, you can specify the dependencies of a library in the `depends` field of library.properties. Those libraries can be installed automatically when someone installs that library via Library Manager.

For more information, see the [`library.properties` file format documentation](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format).

### Can I install multiple versions of one library and use the proper one in my sketches?

Library Manager installs libraries into your sketchbook's `libraries` folder. Since you cannot create two folders with the same name, we can't install two versions of the same library. However, you can switch between library versions by selecting the appropriate one from the version dropdown that pops up on Library Manager when more than one version is available.

### How can I remove a library I installed via Library Manager?

#### Arduino IDE 2.x

Hover the mouse pointer over the <kbd>INSTALLED</kbd> label on the library listing in Library Manager. It will now change to <kbd>UNINSTALL</kbd>, which you can click to uninstall that library.

#### Classic Arduino IDE

This version of the Arduino IDE does not have an integrated uninstall functionality, so you will need to remove the library manually. Open your sketchbook's `libraries` folder with your operating system's file explorer (Windows: Explorer, Mac: Finder, Linux: Nautilus, kfiles...) and delete the folder containing the library.

#### Arduino CLI

Libraries can be uninstalled via [the `arduino-cli lib uninstall` command](https://arduino.github.io/arduino-cli/latest/commands/arduino-cli_lib_uninstall/).

## Security & Malware Reporting

If you think you found a vulnerability, malware or other security-related defect in any Arduino Library projects, please take a look at our security policy and report it to our Security Team 🛡️.

Thank you!

E-mail contact: security@arduino.cc
