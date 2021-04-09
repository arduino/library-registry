# Arduino Library Manager list

This repository contains the list of libraries in the
[Arduino Library Manager](https://www.arduino.cc/en/guide/libraries#toc3) index.

## Adding a library to Library Manager

If you would like to have your library available for installation via Library Manager, just submit a
[pull request](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/about-pull-requests) that
adds the repository URL to [the list](repositories.txt). You are welcome to add multiple libraries at once.

See the instructions below for detailed instructions on how to do this via the GitHub web interface.

### Instructions

1. You may want to first take a look at
   [the requirements for admission into the Arduino Library Manager index](https://github.com/arduino/Arduino/wiki/Library-Manager-FAQ).
   Each submission will be checked for compliance before being accepted.
1. Open this link to [fork](https://guides.github.com/activities/forking/) this repository and edit the list via the
   GitHub web interface: https://github.com/arduino/library-registry/edit/main/repositories.txt
1. Add the library repository's URL to the list. This should be the URL of the repository home page. For example:
   `https://github.com/arduino-libraries/Servo`.
1. At the bottom of the page, select the radio button next to "Create a new branch for this commit and start a pull
   request."
1. Click the "Propose changes" button.
1. In the "Open a pull request" window that opens, click the "Create pull request" button.

The library will be automatically checked for compliance as soon as the pull request is submitted. If no problems were
found, the pull request will be immediately merged and the library will be available for installation via Library
Manager within a day's time.

If any problems are found, a bot will comment on the pull request to tell you what is wrong. The problem may be either
with your pull request or with the library.

#### If the problem is with the pull request:

Edit the file in the
[branch](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/about-branches) you submitted the
pull request from in your fork of the `arduino/library-registry` repository, then commit.

Doing this will update the pull request and cause the automated checks to run again.

#### If the problem is with the library:

1. Make the necessary fix in the library repository.
1. Increment the `version` value in the library's
   [library.properties file](https://arduino.github.io/arduino-cli/latest/library-specification/#library-metadata).
1. Create a [release](https://docs.github.com/en/github/administering-a-repository/managing-releases-in-a-repository) or
   [tag](https://git-scm.com/docs/git-tag). The Library Manager index always uses tagged versions of the libraries, so
   even if the development version of the library is compliant, it can't be accepted until the latest release or tag is
   compliant. Alternatively, you can redo the existing release/tag if you prefer.
1. Comment on your pull request here in the `arduino/library-registry` repository, mentioning **@ArduinoBot** in the
   comment. Doing this will cause the automated check to run again.

## Changing the URL of a library already in Library Manager

Submit a pull request that changes the URL as desired in [repositories.txt](repositories.txt). This can be done by
following [the instructions above](#instructions).

Since this type of request must be reviewed by a human maintainer, please write an explanation in the pull request
description, making it clear that the URL is intentionally being changed.

## Removing the URL of a library already in Library Manager

Submit a pull request that removes the URL from [repositories.txt](repositories.txt). This can be done by following
[the instructions above](#instructions).

Since this type of request must be reviewed by a human maintainer, please write an explanation in the pull request
description, making it clear that the URL is intentionally being removed.

## Report a problem with Library Manager

Please first take a look at
[the Arduino Library Manager FAQ](https://github.com/arduino/Arduino/wiki/Library-Manager-FAQ). If a library release is
missing from Library Manager, it is usually because it was not compliant with all the requirements listed in that
document.

This repository is not an appropriate place to request support or report problems with a library. Check the library's
own documentation for instructions or ask on the [Arduino Forum](https://forum.arduino.cc/).

If the problem is about something else, please make an issue report here:
https://github.com/arduino/library-registry/issues?q=is%3Aissue
