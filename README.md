# Arduino Library Manager list

This repository contains the list of libraries in the [Arduino Library Manager](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries#using-the-library-manager) index.

## Table of Contents

<!-- toc -->

- [Frequently asked questions](#frequently-asked-questions)
- [Adding a library to Library Manager](#adding-a-library-to-library-manager)
  - [A. Preparation](#a-preparation)
  - [B. Fork the Arduino Library Registry repository](#b-fork-the-arduino-library-registry-repository)
  - [C. Create a feature branch in the fork](#c-create-a-feature-branch-in-the-fork)
  - [D. Add the library URL to the list](#d-add-the-library-url-to-the-list)
  - [E. Make the pull request](#e-make-the-pull-request)
  - [F. Monitor pull request and resolve any problems](#f-monitor-pull-request-and-resolve-any-problems)
    - [If the problem is with the pull request:](#if-the-problem-is-with-the-pull-request)
    - [If the problem is with the library:](#if-the-problem-is-with-the-library)
- [Changing the URL of a library already in Library Manager](#changing-the-url-of-a-library-already-in-library-manager)
- [Removing a library from Library Manager](#removing-a-library-from-library-manager)
- [Report a problem with Library Manager](#report-a-problem-with-library-manager)
- [Security & Malware Reporting](#security--malware-reporting)

<!-- tocstop -->

## Frequently asked questions

For more information about Arduino Library Manager and how the index is maintained, please see [the FAQ](FAQ.md).

<a name="instructions"></a>

## Adding a library to Library Manager

If you would like to make a library available for installation via Library Manager, just submit a [pull request](https://docs.github.com/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests) that adds the repository URL to [the list](repositories.txt). You are welcome to add multiple libraries at once.

---

⚠ If you behave irresponsibly in your interactions with this repository, your Library Manager Registry privileges will be revoked.

Carefully read and follow the instructions in any comments the bot and human maintainers make on your pull requests. If you are having trouble following the instructions, add a comment that provides a detailed description of the problem you are having and a human maintainer will provide assistance.

Although we have set up automation for the most basic tasks, this repository is maintained by humans. So please behave in a manner appropriate for interacting with humans, including being clear in communicating what you are hoping to accomplish.

---

Detailed instructions for submitting a library are provided below.

### A. Preparation

---

❗ Before you begin, please ensure you have 45 minutes of time to dedicate to completing the submission procedure. A submission will typically only take a few minutes, but if your library is not specification compliant or your are not already familiar with the basics of using GitHub, it may take longer. If problems with the submission are detected, we expect you to resolve them promptly.

---

1. Review [the requirements for admission into the Arduino Library Manager index](FAQ.md#submission-requirements). Each submission will be checked for compliance with these requirements before being accepted.
1. If you identify any aspects of the library that do not meet the requirements, please resolve them.

---

**ⓘ** If a requirement is not clear to you, or if you are not able to determine whether the library is in compliance with a requirement, it is OK to proceed with making the submission. The automated submission handling system is designed to help you to resolve any problems that are detected, so you may find that things are more clear once the submission is in progress.

---

### B. Fork the Arduino Library Registry repository

You will first make the changes required to add the library in a copy of the Arduino Library Registry repository under your GitHub account. The term for a copy of a repository is "[fork](https://docs.github.com/get-started/quickstart/fork-a-repo)".

1. Click the following link:<br />
   https://github.com/arduino/library-registry/fork<br />
   The "**Create a new fork**" page will open in your web browser.
1. Click the "**Create fork**" button in the "**Create a new fork**" page.

The fork will be created, and the home page of the fork will open.

### C. Create a feature branch in the fork

Multiple revision histories may be stored in a single repository. The term for each revision history is "[branch](https://docs.github.com/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-branches)". You will create a dedicated branch in which to stage the work to submit the library.

1. Click the "**1 Branch**" link on the home page of your fork.<br />
   The "**Branches**" page will open.
1. Click the "**New branch**" button on the "**Branches**" page.<br />
   The "**Create a branch**" dialog will open.
1. Type `my-submission` (or any other name you like) in the "**New branch name**" field of the "**Create a branch**" dialog.<br />
   The "**Create a branch**" dialog will close.
1. Click on the first drop-down menu under the "**Source**" section of the dialog.<br />
   The drop-down menu will open.
1. Select "**arduino/library-registry**" from the menu.
1. Click on the second drop-down menu under the "**Source**" section of the dialog.<br />
   The drop-down menu will open.
1. Select "**main**" from the menu.
1. Click the "**Create new branch**" button at the bottom of the dialog.<br />
   The "**Create a branch**" dialog will close, returning you to the "**Branches**" page.
1. Look under the "**Your branches**" section of the "**Branches**" page. You will see a link there for the branch you created during the previous step (i.e., `my-submission`). Click that link.<br />
   The home page of your fork will open, with the newly created branch selected.

### D. Add the library URL to the list

Now you are ready to make the change in the repository content that adds the library to the Arduino Library Registry. This is done by adding the URL of the repository to a text file that contains a list of all the registered libraries. The term for a change in a repository's revision history is "[commit](https://git-scm.com/docs/git-commit)".

1. Click on the file `repositories.txt` under the list of files you see on the home page of your fork.<br />
   The "**library-registry/repositories.txt**" page will open.
1. Click the pencil icon ("Edit this file") at the right hand side of the toolbar in the "**library-registry/repositories.txt**" page.<br />
   The `repositories.txt` file will open in the online text editor.
1. Add the URL of the repository of the library you wish to submit to the list in the online text editor.
   - **ⓘ** It doesn't matter at which position in the list you add the URL.
   - **ⓘ** This should be the URL of the repository home page. For example:
     ```text
     https://github.com/arduino-libraries/Servo
     ```
   - ❗ Be careful to avoid making any changes to the other URLs in the list.
1. Click the "**Commit changes...**" button located near the top right hand corner of the page.<br />
   The "**Commit changes**" dialog will open.
1. Select the "**Commit directly to the `my-submission` branch**" radio button in the dialog.<br />
   **ⓘ** If you chose a name other than `my-submission` when creating the branch, the radio button will instead have that branch name.
1. Click the "**Commit changes**" button in the "**Commit changes**" dialog.<br />
   The "**Commit changes**" dialog will close.
1. Click the "**library-registry**" link at the top of the "**library-registry/repositories.txt**" page.<br />
   The home page of your fork will open.

### E. Make the pull request

Now that you have the necessary changes staged in your fork, it is time to propose those changes be accepted into the parent repository. The term for such a proposal is "[pull request](https://docs.github.com/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests)" (PR).

1. Click the "**Contribute**" button on the home page of your fork.<br />
   A menu will open.
1. Click the "**Open pull request**" button in the menu.<br />
   The "**Open a pull request**" page will open.
1. Click the "**Create pull request**" button on the "**Open a pull request**" page.

The pull request will be submitted.

### F. Monitor pull request and resolve any problems

The submission of the pull request will trigger an automated system. This system checks your pull request and the submitted library for problems. It will register the library if no problems are found. It will communicate with you via comments added to the pull request.

---

❗ Please closely monitor the pull request and take prompt action to resolve any problems reported by the automated system and human maintainers.

---

1. Watch your pull request until you see a comment from the bot.<br />
   **ⓘ** You should only need to wait a few minutes at most.
1. If you see that the pull request was merged, this means your library has been successfully registered 🎉 and the library will be available for installation via Library Manager within a day's time. If instead the comment from the bot says that a problem was found, please promptly follow the provided instructions to resolve the problem. There is additional information about resolving problems below.

The problem may be either with your pull request or with the library:

#### If the problem is with the pull request:

Edit the file in the [branch](https://docs.github.com/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-branches) you submitted the pull request from in your fork of the `arduino/library-registry` repository, then commit.

Doing this will update the pull request and cause the automated checks to run again.

#### If the problem is with the library:

1. Make the necessary fix in the library repository.
1. Increment the `version` value in the library's [library.properties file](https://arduino.github.io/arduino-cli/latest/library-specification/#library-metadata).
1. Create a [release](https://docs.github.com/repositories/releasing-projects-on-github/managing-releases-in-a-repository) or [tag](https://git-scm.com/docs/git-tag). The Library Manager index always uses tagged versions of the libraries, so even if the development version of the library is compliant, it can't be accepted until the latest release or tag is compliant. Alternatively, you can redo the existing release/tag if you prefer.
1. Comment on your pull request here in the `arduino/library-registry` repository, mentioning **@ArduinoBot** in the comment. Doing this will cause the automated check to run again.

## Changing the URL of a library already in Library Manager

Submit a pull request that changes the URL as desired in [repositories.txt](repositories.txt). This can be done by following [the instructions above](#instructions).

Since this type of request must be reviewed by a human maintainer, please write an explanation in the pull request description, making it clear that the URL is intentionally being changed.

## Removing a library from Library Manager

Submit a pull request that removes the URL from [repositories.txt](repositories.txt). This can be done by following [the instructions above](#instructions).

Since this type of request must be reviewed by a human maintainer, please write an explanation in the pull request description, making it clear that the URL is intentionally being removed.

## Report a problem with Library Manager

First, please take a look at [the FAQ](FAQ.md). If a library release is missing from Library Manager, it is usually because it was not compliant with all [the requirements](FAQ.md#update-requirements) listed in that document.

This repository is not an appropriate place to request support or report problems with a library. Check the library's own documentation for instructions or ask on the [Arduino Forum](https://forum.arduino.cc/).

If the problem is about something else, please submit an issue report [here](https://github.com/arduino/library-registry/issues/new/choose).

## Security & Malware Reporting

If you think you found a vulnerability, malware or other security-related defect in any Arduino Library projects, please take a look at our security policy and report it to our Security Team 🛡️.

Thank you!

E-mail contact: security@arduino.cc
