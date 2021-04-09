# Arduino Library Manager FAQ

### Library Manager overview

The Arduino Library Manager is a feature of the Arduino IDE (**Sketch > Include Library > Manage Libraries...**) which makes it easy for users to find, install, and update both official and 3rd party libraries. When your library is added to the library list, every release/tag version of the library in your repository will automatically be made available for installation via Library Manager. The users can set their preferences to display an update notification when a new version of any installed library on the list is available and easily update to the new version with just a couple clicks. More information: <br />
https://www.arduino.cc/en/Guide/Libraries#toc3

### How is the library list generated?

From a list of public Git repos, a job (a small program that runs regularly) fetches every tag, verifies library files and pushes the updated [list](http://downloads.arduino.cc/libraries/library_index.json) onto the Arduino download server.
Only valid libraries and their tags are published.

A library is **not valid** when:

- it's not in [1.5 format](https://arduino.github.io/arduino-cli/latest/library-specification) and in particular it misses a [library.properties](https://arduino.github.io/arduino-cli/latest/library-specification/#library-metadata) file (1.5 format folder layout is not required)
- its `name` field in library.properties starts with `Arduino`
- its `url` field in library.properties is left blank
- its version number is not [semver compliant](http://semver.org/)
- it contains `.exe` files
- it contains a `.development` file
- it contains symlinks
- our antivirus finds infected files

**The job runs every hour. If a new library has been released, you can expect it to be listed within the hour, but it might take longer**.

Arduino has created a command line tool to check libraries for compliance with all the Library Manager requirements:

https://github.com/arduino/arduino-lint

Arduino Lint is also available as a GitHub Actions action that can be used in the CI systems of Arduino library repositories to ensure continued compliance:

https://github.com/arduino/arduino-lint-action

### How can I add my library to Library Manager?

- Your library repository must be hosted on a major Git-hosting website like GitHub, BitBucket or GitLab (other hosting sites may be considered on request).
- Ensure your library is compliant with [1.5 format](https://arduino.github.io/arduino-cli/latest/library-specification/) (1.5 format folder layout is not required)
- Your library must not have the same library.properties `name` value (regardless of case) as another library previously added to the Library Manager index.
- [Tag](https://git-scm.com/book/en/v2/Git-Basics-Tagging) it and push the tag (or create a release if you web hosting offers a way to do it, for example with [GitHub "releases"](https://help.github.com/articles/creating-releases/))
- Open an issue on [Arduino's GitHub](https://github.com/arduino/Arduino/issues), specifying the URL of the repository from where to download your library. If you have multiple libraries to submit you are welcome to do them all in a single issue.
- After some days, a member of the Arduino team will add your library to the Library Manager index and close the issue. Shortly after that your library will be available for installation via Library Manager.

### How can I publish a new release once my library is in the list?

Ensure you've changed version in your `library.properties`. Then tag your library once more and push the new tag (or create a release if your web hosting offers a way to do it, for example with GitHub "releases").
Our indexer checks for new releases every hour and will eventually fetch and publish your new release.

### Sorry, I did something wrong! How can I change or unpublish an already published library?

In order to change contents of an already published library version, you can recreate its related tag.

In order to **un**publish a library version, delete its related tag/release.

Once you have done that, open an issue on [Arduino's GitHub](https://github.com/arduino/Arduino/issues), specifying the URL of the library repository and requesting that the library be updated.

### Why aren't releases of my library being picked up by Library Manager?

The Library Manager indexer job will not pick up releases which don't have a unique `version` value in library.properties. Remember to always update the `version` value in your library.properties _before_ creating the tag or release.

Make sure your library meets all the requirements listed [here](#how-is-the-library-list-generated).

Changing the `name` value in your library.properties from the one it had at the time when the library was added to the Library Manager index will cause releases to be ignored. You need to request a name change, as explained [here](#how-can-i-change-my-librarys-name).

### How can I change my library's name?

For the sake of continuity, libraries in the Library Manager list are locked in to the name they had at the time they were added to the list. If you wish to change the name it will need to be done manually by request:

1. Change the `name` value in your [library.properties file](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format) and update the `version`.
1. Create a release or tag that matches the updated `version` value in library.properties.
1. Submit an [issue report](https://github.com/arduino/Arduino/issues/new) requesting the name be changed and the URL of your library's repository.

### How can I delete a library?

Open your sketchbook's `libraries` folder with your OS file explorer (Windows: Explorer, Mac: Finder, Linux: Nautilus, kfiles...) and delete the folder containing your library.

##### Rationale

No, we don't have a delete button. Libraries managed by the Library Manager are mixed with those you've manually installed, maybe libraries you've written: making a mistake and deleting the wrong library is too easy. That's why trash bins exist. Since the IDE has no knowledge of your trash bin, we didn't implement a "delete" button.

## Limitations

### Is my Git repo OK?

Your repo is OK if its root folder contains the file `library.properties` and the rest of the library source code. If your library is stored in a subfolder, your repo is not OK and we can't include your library in the list.

### Are Git submodules supported?

No. The library archive distributed by Library Manager will only contain an empty folder where the submodule should be.

### Can I add my own URL with my own library list?

No. At the moment, the IDE handles one URL only, and that's written into the code (dev jargon: it's hardcoded), this is a known limitation.
However, if you know your way through the code, you can change that URL with another one.

### When I install a library that I know depends on another library, will this other library be installed as well?

You can specify the dependencies of your library in the `depends` field of library.properties. As of Arduino IDE 1.8.10, the user will be prompted to install those libraries when they install your library via Library Manager. For more information, see the [`library.properties` file format documentation](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format).

### Can I install multiple versions of one library and use the proper one in my sketches?

Library Manager installs libraries into your sketchbook's `libraries` folder. Since you cannot create two folders with the same name, we can't install two versions of the same library. However, you can switch between library versions by selecting the appropriate one from the version dropdown that pops up on Library Manager when more than one version is available.
