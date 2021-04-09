# Arduino Library Manager FAQ

### Library Manager overview

The Arduino Library Manager is a feature of the Arduino IDE (**Sketch > Include Library > Manage Libraries...**) which makes it easy for users to find, install, and update both official and 3rd party libraries. When your library is added to the library list, every release/tag version of the library in your repository will automatically be made available for installation via Library Manager. The users can set their preferences to display an update notification when a new version of any installed library on the list is available and easily update to the new version with just a couple clicks. More information: <br />
https://www.arduino.cc/en/Guide/Libraries#toc3

### What are the requirements for a library to be added to Library Manager?

<a id="submission-requirements"></a>

- [ ] The library must be fully compliant with the [Arduino Library Specification](https://arduino.github.io/arduino-cli/latest/library-specification).
- [ ] The library must have [a library.properties file](https://arduino.github.io/arduino-cli/latest/library-specification/#library-metadata), in compliance with the Arduino Library 1.5 format.
- [ ] The library.properties file must be located in the root of the repository.
- [ ] The library must not have the same library.properties `name` value (regardless of case) as another library previously added to the Library Manager list.
- [ ] For 3rd party libraries, the `name` field in library.properties must not start with `Arduino`.
- [ ] The library repository must not contain any `.exe` files.
- [ ] The library repository must not contain a [`.development` file](https://arduino.github.io/arduino-cli/latest/library-specification/#development-flag-file).
- [ ] The library repository must not contain any [symlinks](https://en.wikipedia.org/wiki/Symbolic_link).
- [ ] The library repository must not contain any files detected as infected by our antivirus scan.
- [ ] The library repository must have a [Git tag](https://git-scm.com/book/en/v2/Git-Basics-Tagging) (or [release](https://help.github.com/articles/creating-releases/)) and must have been compliant with all the above requirements at the time of that tag.
- [ ] The library repository must be hosted on a major Git-hosting website like GitHub, BitBucket or GitLab (other hosting sites may be considered on request).

Arduino has created a command line tool to check libraries for compliance with all the Library Manager requirements:

https://github.com/arduino/arduino-lint

Arduino Lint is also available as a GitHub Actions action that can be used in the CI systems of Arduino library repositories to ensure continued compliance:

https://github.com/arduino/arduino-lint-action

### How is the Library Manager index generated?

[The Library Manager index](http://downloads.arduino.cc/libraries/library_index.json) contains the data for every release of every one of the thousands of libraries that have been added to the Library Manager list. This index is used by Library Manager to provide installation and updates of the libraries as well as to generate automated documentation pages for the [Arduino Library Reference](https://www.arduino.cc/reference/en/libraries/).

Every hour, the automated Library Manager indexer system:

1. checks every repository in the Library Manager list for new tags
1. checks whether those tags meet [the requirements for addition to the index](#update-requirements)
1. adds entries to the index for compliant tags
1. pushes the updated index to Arduino's download server

### How can I add my library to Library Manager?

Follow the submission instructions [here](README.md#adding-a-library-to-library-manager).

### How can I publish a new release once my library is in the list?

1. Make sure the library is compliant with [all requirements](#update-requirements).
1. Update the `version` in your `library.properties`.
1. Tag your library once more and push the new tag (or create a release if your web hosting offers a way to do it, for example with GitHub "releases").

[Our indexer](#how-is-the-library-manager-index-generated) checks for new releases every hour and will eventually fetch and publish your new release.

### What are the requirements for publishing new releases of libraries already in the Library Manager list?

<a id="update-requirements"></a>

- [ ] The library must be compliant with all the same [requirements that apply to submissions](#submission-requirements).
- [ ] The `name` property in library.properties must not have changed from the value it had when the library was submitted. If you must change the library name, see [this](#how-can-i-change-my-librarys-name).
- [ ] The `version` property in library.properties must not be the same as it was in a tag previously added to the Library Manager index.

### Sorry, I did something wrong! How can I change or unpublish an already published library?

In order to change contents of an already published library version, you can recreate its related tag.

In order to **un**publish a library version, delete its related tag/release.

Once you have done that, open an issue in [the issue tracker of this repository](https://github.com/arduino/library-registry/issues), specifying the URL of the library repository and requesting that the library be updated.

### Why aren't releases of my library being picked up by Library Manager?

The Library Manager indexer job will reject any releases which aren't compliant with all [the requirements](#update-requirements).

### How can I change my library's name?

For the sake of continuity, libraries in the Library Manager list are locked in to the name they had at the time they were added to the list. If you wish to change the name it will need to be done manually by request:

1. Change the `name` value in your [library.properties file](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format) and update the `version`.
1. Create a release or tag that matches the updated `version` value in library.properties.
1. Submit an [issue report](https://github.com/arduino/library-registry/issues) requesting the name be changed and the URL of your library's repository.

### How can I delete a library?

Open your sketchbook's `libraries` folder with your OS file explorer (Windows: Explorer, Mac: Finder, Linux: Nautilus, kfiles...) and delete the folder containing your library.

##### Rationale

No, we don't have a delete button. Libraries managed by the Library Manager are mixed with those you've manually installed, maybe libraries you've written: making a mistake and deleting the wrong library is too easy. That's why trash bins exist. Since the IDE has no knowledge of your trash bin, we didn't implement a "delete" button.

## Limitations

### Is my Git repo OK?

Your repo is OK if it meets all [the requirements listed here](#submission-requirements).

### Are Git submodules supported?

No. The library archive distributed by Library Manager will only contain an empty folder where the submodule should be.

### Can I add my own URL with my own library index?

No. At the moment, the IDE handles one URL only, and that's written into the code (dev jargon: it's hardcoded), this is a known limitation.
However, if you know your way through the code, you can change that URL with another one.

### When I install a library that I know depends on another library, will this other library be installed as well?

You can specify the dependencies of your library in the `depends` field of library.properties. As of Arduino IDE 1.8.10, the user will be prompted to install those libraries when they install your library via Library Manager. For more information, see the [`library.properties` file format documentation](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format).

### Can I install multiple versions of one library and use the proper one in my sketches?

Library Manager installs libraries into your sketchbook's `libraries` folder. Since you cannot create two folders with the same name, we can't install two versions of the same library. However, you can switch between library versions by selecting the appropriate one from the version dropdown that pops up on Library Manager when more than one version is available.
