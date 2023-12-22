This is an automatic translation, may be incorrect in some places. See sources and examples!

#using-the-libory-manager) Index.

## Table of Contents

<!-TOC->

-[Frequently Asked Questions]
-[Adding a Library to Library Manager] (# Adding-A-Library-to-Library-Manager)
  - [Instructions] (# Instructions)
    -[If the Problem Is with The Pull Request:] (# IF-THE-PROBLEM-WITH-THE-PULL-REM
    -[If the Problem Is with The Library:] (#if-the-Problem-With-the-Library)
-[Changing the URL of A Library Alread in Library Manager] (# Changing-The-Uf-A-Library-in-in-Library-Manager)
-[Removing a Library from Library Manager] (# Removing-A-Library-From-Library-Manager)
-[Report a Problem with Library Manager] (# Report-A-Problem-With-Library-Manager)

<!-Tocstop->

## Frequently Asked Questions

For More Information ABOUT Arduino Library Manager and How the Index Is Maintained, Please See [The Faq.md).

## Adding a Library to Library Manager

IF YOU WOULD LIKE to MAKE A LIBRARY AVAILABLE For Installation Via Library Manager, Just Submit a
[Pull Request] (https://docs.github.com/pull-requests/collaborating-pull-requests/proposing-changes-to-work-with-pull-requests)
That adds the repository url to [the list] (repositories.txt).You are welcome to add multiple libraries at once.

See the Instructions Below for Detailed Instructions on Howing Via The Github Web Interface.

### Instructions

1. You may want to first take a look at
   [The Requirements for Admission Into the Arduino Library Manager (Faq.md# Submsion-Requirements).Each Submission Will Be Cherited For
   Compliance Before Being Accepted.
1. Click The Following Link: <br />
   https://github.com/arduino/libry-registry/Fork <br />
   The "** Create A New Fork **" Page Will Open.
1. Click the <kbd> Create FORK </KBD> BUTTON in the "** CREATE A New FORK **" PAGE. <Br />
   A "** FORKING ARDUINO/LIBRARY-SEGISTRY **" PAGE WILL OPEN WHILE THE FORK IS in the Process of Being Creed.
1. Wait for the "Forking" Process to Finish. <br />
   The Home Page of your [forks] (https://docs.github.com/get-started/quickstart/Fork-a-Repo) of the ** Library-registry ** Repository Will Open.
1. Click on the File `Repositories.txt` under the list of films you in that pass. <br />
   The "** Library-registry/Repositories.txt **" Page Will Open.
1. Click The Pencil icon ("Edit this File") At the Right Side of the Toolbar in the "** Library-Registry /Repositories.txt **" Page />
   The `repositories.txt` file Will Open in the Online Text Editor.
1. Add The Library Repository's url to the list (Itsn 'Matter Where in the List).This Shoup Be the Url of the Repository Home Page.For example:
   `https: // github.com/arduino-libraries/servo`
1. Click the <kbd> comit changes ... </ kbd> button located Near the Top Right Corner of the Page. <br />
   The "** comit changes **" Dialog Will Open.
1. Click the <kbd> comit changes </ kbd> button in the "** comit changes **" dialog. <br />
   The "** Library-registry/Repositories.txt **" Page Will Open.
1. Click The "** Library-Registry **" Link at the Top of the "** Library-Segistry /Repositories.txt **" Page. <br />
   The Home Page of Your Fork of the ** Library-Registry ** Repository Will Open.
1. You should see a banner on the pass:

   > ** This Branch is 1 comit ahead of arduino: Main. **

   Click The "** Contribute **" Link Near The Right Side of that Banner. <br />
   A Menu Will Open.

1. Click the <kbd> open pull Request </ kbd> button in the menu. <br />
   The "** Open a pull request **" Page Will Open.
1. In the ** "Open a pull Request" ** Window That Opens, Click the <kbd> Create Pull Request </ KBD> BUTTON.

The Library Will BE Automatical Cheshed for Compliance as Soon as the Pull Request is Submitted.If no problems were
Found, The Pull Request Will BE Immediatly Merged and the Library Will Be Avalable for InstituteAllation Via Library
Manager Within a Day's Time.

IF ANY PROBLEMS ARE FOUND, A BOT Will Comment On the Pull Request To Tell You What Is Wrong.The Problem May Be Either
With your pull Request or with The Library.

### if the Problem Is with the Pull Request:

Edit the File in the
[Branch] (https://docs.github.com/pull-requests/collaborating-pull-reques/proposing-to-your-work-with-pull-requests/aabouut-branche)
You Submitted the Pull Request from in Your Fork of the `Arduino/Library-Registry` Repository, The Commit.

Doing this Will update the Pull Request and Cause The Automated Checks to Run AGain.

### if the Problem Is with the Library:

1. Make The Necessary Fix in the Library Repository.
1. Increment the `Version` Value in the Library
   [Library.Properties File] (https://arduino.github.io/arduino-cli/latest/libry-specification/#libry-metadata).
1. Create a
   [Release] (https://docs.github.com/repositories/releasing-projects-on-github/managing-releases-in- a-Repository)
   or [tag] (https://git-scm.com/docs/git-tag).The Library Manager Index Always Uses Tagged Versions of the Libraries,
   So Even If the Development Version of the Library Is Compliant, It Can't Be Accepted Until The Latest Release Or Tag
   IS Compliant.Alternatively, You can red the Existing Release/Tag IF You Prefer.
1. Comment on Your Pull Request Here in the `Arduino/Library-Registry` Repository, Mental **@ardinobot ** in the
   Comment.Doing this Will Cause The Automated Check To Run Again.

## Changing the url of a Library Alread in Library Manager

Submit a Pull Request that Changes The url as desired in [repositories.txt] (repositories.txt).This can be done by
Following [The Instructions ABOVE] (# Instructions).

SINCE THIS TYPE of Request MUST Be Reviewed by A Human Maintainer, Please Write an Explanation in the Pull Receist
Description, MAKING IT CLEAR that url is intentionally Being Changed.

## Removing a Library from Library Manager

Submit a Pull Request that removs the url from [repositories.txt] (repositories.txt).This Can Be Done by Following
[The Instructions ABOVE] (# Instructions).

SINCE THIS TYPE of Request MUST Be Reviewed by A Human Maintainer, Please Write an Explanation in the Pull Receist
Description, MAKING IT CLEAR that url is intentionally Being Removed.

## Report a Problem with Library Manager

FIRST, please TAKE A LOOK AT [The FAQ] (FAQ.md).IF A Library Release is Missing from Library Manager, it is usually
Because it was not compliant with all [The Requirements] (Faq.md# Update-Requirements) Listed in that doCument.

This repository is not an appropriate Place to Request Support or Report Problems with A Library.Check The Library's
OWN Documentation for Instructions or ask on the [arduino forum] (https://forum.arduino.cc/).

If the Problem Is ABOUT SOMETHING ELSE, please Submit an isesue report [hese] (https://github.com/arduino/libary-registry/issues/new/chooose).