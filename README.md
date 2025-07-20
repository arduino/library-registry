# Arduino Library Manager list

This repository contains the list of libraries in the
[Arduino Library Manager](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries#using-the-library-manager) index.

## Table of Contents

<!-- toc -->

- [Frequently asked questions](#frequently-asked-questions)
- [Adding a library to Library Manager](#adding-a-library-to-library-manager)
  - [Instructions](#instructions)
    - [If the problem is with the pull request:](#if-the-problem-is-with-the-pull-request)
    - [If the problem is with the library:](#if-the-problem-is-with-the-library)
- [Changing the URL of a library already in Library Manager](#changing-the-url-of-a-library-already-in-library-manager)
- [Removing a library from Library Manager](#removing-a-library-from-library-manager)
- [Report a problem with Library Manager](#report-a-problem-with-library-manager)
- [Security & Malware Reporting](#security--malware-reporting)

<!-- tocstop -->

## Frequently asked questions

For more information about Arduino Library Manager and how the index is maintained, please see [the FAQ](FAQ.md).

## Adding a library to Library Manager

If you would like to make a library available for installation via Library Manager, just submit a
[pull request](https://docs.github.com/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests)
that adds the repository URL to [the list](repositories.txt). You are welcome to add multiple libraries at once.

See the instructions below for detailed instructions on how to do this via the GitHub web interface.

### Instructions

---

⚠ If you behave irresponsibly in your interactions with this repository, your Library Manager Registry privileges will be revoked.

Carefully read and follow the instructions in any comments the bot and human maintainers make on your pull requests. If you are having trouble following the instructions, add a comment that provides a detailed description of the problem you are having and a human maintainer will provide assistance.

Although we have set up automation for the most basic tasks, this repository is maintained by humans. So behave in a manner appropriate for interacting with humans, including clearly communicating what you are hoping to accomplish.

---

1. You may want to first take a look at
   [the requirements for admission into the Arduino Library Manager index](FAQ.md#submission-requirements). Each submission will be checked for
   compliance before being accepted.
1. Click the following link:<br />
   https://github.com/arduino/library-registry/fork<br />
   The "**Create a new fork**" page will open.
1. Click the <kbd>Create fork</kbd> button in the "**Create a new fork**" page.<br />
   A "**Forking arduino/library-registry**" page will open while the fork is in the process of being created.
1. Wait for the "Forking" process to finish.<br />
   The home page of your [fork](https://docs.github.com/get-started/quickstart/fork-a-repo) of the **library-registry** repository will open.
1. Click on the file `repositories.txt` under the list of files you see in that page.<br />
   The "**library-registry/repositories.txt**" page will open.
1. Click the pencil icon ("Edit this file") at the right side of the toolbar in the "**library-registry/repositories.txt**" page.<br />
   The `repositories.txt` file will open in the online text editor.
1. Add the library repository's URL to the list (it doesn't matter where in the list). This should be the URL of the repository home page. For example:
   `https://github.com/arduino-libraries/Servo`
1. Click the <kbd>Commit changes...</kbd> button located near the top right corner of the page.<br />
   The "**Commit changes**" dialog will open.
1. Click the <kbd>Commit changes</kbd> button in the "**Commit changes**" dialog.<br />
   The "**library-registry/repositories.txt**" page will open.
1. Click the "**library-registry**" link at the top of the "**library-registry/repositories.txt**" page.<br />
   The home page of your fork of the **library-registry** repository will open.
1. You should see a banner on the page that says:

   > **This branch is 1 commit ahead of arduino:main.**

   Click the "**Contribute**" link near the right side of that banner.<br />
   A menu will open.

1. Click the <kbd>Open pull request</kbd> button in the menu.<br />
   The "**Open a pull request**" page will open.
1. In the **"Open a pull request"** window that opens, click the <kbd>Create pull request</kbd> button.

The library will be automatically checked for compliance as soon as the pull request is submitted. If no problems were
found, the pull request will be immediately merged and the library will be available for installation via Library
Manager within a day's time.

If any problems are found, a bot will comment on the pull request to tell you what is wrong. The problem may be either
with your pull request or with the library.

#### If the problem is with the pull request:

Edit the file in the
[branch](https://docs.github.com/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-branches)
you submitted the pull request from in your fork of the `arduino/library-registry` repository, then commit.

Doing this will update the pull request and cause the automated checks to run again.

#### If the problem is with the library:

1. Make the necessary fix in the library repository.
1. Increment the `version` value in the library's
   [library.properties file](https://arduino.github.io/arduino-cli/latest/library-specification/#library-metadata).
1. Create a
   [release](https://docs.github.com/repositories/releasing-projects-on-github/managing-releases-in-a-repository)
   or [tag](https://git-scm.com/docs/git-tag). The Library Manager index always uses tagged versions of the libraries,
   so even if the development version of the library is compliant, it can't be accepted until the latest release or tag
   is compliant. Alternatively, you can redo the existing release/tag if you prefer.
1. Comment on your pull request here in the `arduino/library-registry` repository, mentioning **@ArduinoBot** in the
   comment. Doing this will cause the automated check to run again.

## Changing the URL of a library already in Library Manager

Submit a pull request that changes the URL as desired in [repositories.txt](repositories.txt). This can be done by
following [the instructions above](#instructions).

Since this type of request must be reviewed by a human maintainer, please write an explanation in the pull request
description, making it clear that the URL is intentionally being changed.

## Removing a library from Library Manager

Submit a pull request that removes the URL from [repositories.txt](repositories.txt). This can be done by following
[the instructions above](#instructions).

Since this type of request must be reviewed by a human maintainer, please write an explanation in the pull request
description, making it clear that the URL is intentionally being removed.

## Report a problem with Library Manager

First, please take a look at [the FAQ](FAQ.md). If a library release is missing from Library Manager, it is usually
because it was not compliant with all [the requirements](FAQ.md#update-requirements) listed in that document.

This repository is not an appropriate place to request support or report problems with a library. Check the library's
own documentation for instructions or ask on the [Arduino Forum](https://forum.arduino.cc/).

If the problem is about something else, please submit an issue report [here](https://github.com/arduino/library-registry/issues/new/choose).

## Security & Malware Reporting

If you think you found a vulnerability, malware or other security-related defect in any Arduino Library projects, please take a look at our security policy and report it to our Security Team 🛡️.

Thank you!

E-mail contact: security@arduino.cc
