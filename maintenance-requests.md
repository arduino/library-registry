# Maintenance Requests

Library maintainers sometimes find the need to request the registration data for libraries that are in the Arduino Library Registry. Instructions for making such requests are provided here.

---

**ⓘ** Unlike our highly automated system for library submissions, maintenance requests are handled by humans. Make sure to communicate clearly in order to ensure we execute your request correctly and efficiently.

Please be patient until we complete the manual operations required to accommodate the request.

---

## Table of Contents

<!-- toc -->

- [Remove library](#remove-library)
- [Remove a library release](#remove-a-library-release)
- [Update library name](#update-library-name)
- [Update library URL](#update-library-url)

<!-- tocstop -->

## Remove library

Submit a pull request that removes the URL from [repositories.txt](repositories.txt). This can be done by a procedure similar to [the one followed when submitting a library](README.md#instructions).

Since this type of request must be reviewed by a human maintainer, please write an explanation in the pull request description, making it clear that the URL is intentionally being removed.

## Remove a library release

If you discover a problem with the library release, simply fix the problem and make a new [release](FAQ.md#how-can-i-publish-a-new-release-once-my-library-is-in-the-list). Library Manager defaults to installing the latest version of the library and offers updates to those with an older version installed, so this is the fastest and most effective method for distributing a fix to the users.

In the event a library release is later discovered to contain something that absolutely can not be published, we do allow removing releases from Library Manager on request by the following procedure:

1. Delete the [tag](https://git-scm.com/book/en/v2/Git-Basics-Tagging) of the problematic release from the library's repository.
1. Click [**this link**](https://github.com/arduino/library-registry/issues/new?labels=topic%3A+release+removal&template=release-removal.yml&title=Library+release+removal+request).
   The "**Create new issue**" page will open in your web browser.
1. Type the name of the library into the "**Library name**" field on the "**Create new issue**" page.
1. Type the version number of the release that should be removed into the "**Version to remove**" field.
1. Click the "**Create**" button on the "**Create new issue**" page.

This will create an issue the registry maintainers will use to track the task of accommodating your request.

## Update library name

For the sake of continuity, libraries in the Library Manager list are locked to the name they had at the time they were added to the list. Changing the library name can be disruptive to its users because this is the unique identifier for the library used by the Arduino development software [command line interfaces](https://arduino.github.io/arduino-cli/latest/commands/arduino-cli_lib/), sketch [metadata](https://arduino.github.io/arduino-cli/latest/sketch-specification/#metadata), library [dependencies](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format), and installation location.

If you wish to change the name it will need to be done manually by request:

1. Change the `name` value in the [library.properties file](https://arduino.github.io/arduino-cli/latest/library-specification/#libraryproperties-file-format) and update the `version`.
1. Create a release or tag.
1. Click [**this link**](https://github.com/arduino/library-registry/issues/new?labels=topic%3A+rename&template=rename.yml&title=Library+name+change+request).
   The "**Create new issue**" page will open in your web browser.
1. Type the URL of the library into the "**Library repository URL**" field on the "**Create new issue**" page.
1. Click the "**Create**" button on the "**Create new issue**" page.

This will create an issue the registry maintainers will use to track the task of accommodating your request.

## Update library URL

Submit a pull request that changes the URL as desired in [repositories.txt](repositories.txt). This can be done by a procedure similar to [the one followed when submitting a library](README.md#instructions).

Since this type of request must be reviewed by a human maintainer, please write an explanation in the pull request description, making it clear that the URL is intentionally being changed.
