[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=18723990)
<h2 align="center">
CS3560 Homework Assignment: Documentation Tools (Doxygen) (100 Points)<br/>
Due date: Please see the due date on Canvas 
</h2>

The purpose of this assignment is to put GitHub, Git, Make, and source code documentation tool (doxygen) to use in a small project.

## Step 1 - Setup Doxygen

Install [Doxygen](https://www.doxygen.nl/) and create its configuration file (usually named `Doxyfile`) with the following modifications.

- The name of the project ([`PROJECT_NAME`](https://www.doxygen.nl/manual/config.html#cfg_project_name)) must be your full name and your OHIO email address in parentheses (e.g. `Krerkkiat Chusap (kc555014@ohio.edu)`).
- [`GENERATE_LATEX`](https://www.doxygen.nl/manual/config.html#cfg_generate_latex) must be turned off.
- Tell doxygen that a program called `dot` is not available (using the setting [`HAVE_DOT`](https://www.doxygen.nl/manual/config.html#cfg_have_dot)) (this is here for the students who are installing the older version of doxygen and `HAVE_DOT` is set to `YES`.)

## Step 2 - Modify the Makefile

Modify the given `Makefile` so that running `make docs` will generate the HTML documentation.

## Step 3 - Document the Source Code

### 3.1 - Write Documentation for the Functions

Document **two** functions from any of the following classes: `game`, `Othello`, `piece`. The documentation for each of the function should include

- Description of the function on what it does.
- The return type of the function should be documented.
- The name, type and short description of the arguments of the function (if there is any) should be documented.

- At least three unique [Doxygen's special commands](https://www.doxygen.nl/manual/commands.html) must be correctly used across the two functions.

### 3.2 - Write Documentation for a File

Convert the comment at the beginning of `piece.hpp` to a Doxygen's documentation. Also this file must be clickable in the "File List" page (hint: [the `\file` command](https://www.doxygen.nl/manual/commands.html#cmdfile)).

### 3.3 - Create a Tag

Once finished, create a tag with the name `step-3-doc-ready` and push this tag to GitHub.

## Step 4 - Prepare for the submission

### Step 4.1 - Taking screenshots

- Generate the documentation using `make docs`. Create a gzipped tar archive file of the generated `html` folder. Name it `docs.tar.gz`.
- Take one screenshot for each of the
  function you documented. Example of one of the screenshots can be seen below. For Doxygen, to
  take the screenshot, you can open `html/index.html` file in your browser. Then click on `Classes` then the class (or classes) where your two functions are in.

  <img src=".github/images/submission-screenshot-example.png" width="600" />

  (this screenshot does not show the description of the return value).

- Take another screenshot of `html/files.html` when it is opened in a browser. The
  example of this screenshot is shown below.

  <img src=".github/images/submission-screenshot-example-file-list.png" width="600" />

On GitHub Codespaces you may want to install ["Live Server" extension](https://marketplace.visualstudio.com/items?itemName=ritwickdey.LiveServer). With this extension you can right click
on the `index.html` file and click "Open with Live Server" to view the file in the browser.

### Step 4.2 - Creating a release on GitHub

Next, we will be creating a release on the repository on GitHub. Please read through the two articles to
get general ideas on GitHub Releases.

- [About releases](https://docs.github.com/en/repositories/releasing-projects-on-github/about-releases)
- [About release management](https://docs.github.com/en/repositories/releasing-projects-on-github/managing-releases-in-a-repository#about-release-management)

Then create a release using the tag you created earlier in step 3.3 (the `task-3-doc-ready` tag). Give the release the same name as your tag.
In the description of the release use the following template

```plain
# Homework Submission

Release Author's Full Name: <YOUR_FULL_NAME>
Email Handle: <YOUR_EMAIL_HANDLE>

## List of Files Screenshot

<UPLOAD_YOUR_FIRST_SCREENSHOT_HERE>

## 1st Function's Screenshot

<UPLOAD_YOUR_FIRST_SCREENSHOT_HERE>

## 2nd Function's Screenshot

<UPLOAD_YOUR_SECOND_SCREENSHOT_HERE>
```

Attach the zip file of the generated documentation as an asset of the release. Don't forget to replace `<YOUR_FULL_NAME>`, `<YOUR_EMAIL_HANDLE>` with actual values. Also don't forget to upload your screenshots. For example, of how the release should look like please see Appendix E. Once the release is created, take note of its URL for submission.

## Submission

Submit on Canvas, a link to your repository on GitHub.

## Appendix A - Doxygen Installation

The installation process is slightly different depending on your operating system / environment. These sections are just the summary of the information found in the [Doxygen's manual](https://www.doxygen.nl/manual/install.html)

### Linux and GitHub Codespaces

Doxygen can be installed from package manager with a command `sudo apt-get install doxygen`.

### macOS

There are three options to install Doxygen on macOS.

#### Install from source code

You will need CMake for this, and you can follow the instruction in [Compiling from source on UNIX](https://www.doxygen.nl/manual/install.html#install_src_unix).

#### Install using homebrew

The command `brew install doxygen` should do the job. You will need to have brew installed. Visit https://brew.sh/ for how to install it.

#### Install with dmg file

The dmg file can be downloaded from https://www.doxygen.nl/download.html (under "A binary distribution for Mac OS X 10.14 and later" of the "Sources and Binaries" section).

To install it, drag the folder from the dmg installation page into the `Applications` folder on your macOS.
Then you should be able to double click the application for a GUI. You can also use the doxygen via a command
line by using `/Applications/Doxygen.app/Contents/Resources/doxygen` instead of just `doxygen`.

To run it with just `doxygen`, you need to add `/Applications/Doxygen.app/Contents/Resources` to your 
environment variable named `PATH`. This can be done by the following command `export PATH=$PATH:/Applications/Doxygen.app/Contents/Resources/`.

This `export` command, however, will not be persistent. To make a persistent change you can add the command to
your shell start-up script file (typically `~/.zshrc`).

If the above step does not work, please let the TA know. The TA who updates this instruction does not have Mac device, so it may not be accurate.

### Windows

You can download a precompiled binary from https://www.doxygen.nl/download.html. You will need to update environment variable name `PATH` so that a path to your installation  (It will be somewhere in `C:\Program Files\doxygen\bin`) is included. Consult a search engine on how to modify your `PATH` environment variable on Windows.

## Appendix B - Documentation Tools

| Language             | Tool          |
| -----------          | -----------   |
| C/C++                | Doxygen       |
| Python               | Sphinx        |
| C#                   | Doxygen       |
| JavaScript / Node.js | jsdoc         |
| Rust                 | rustdoc       |

## Appendix C - Example of a Release

Example of release (right click and open image in new tab for the full image)

<img src=".github/images/gh-release-example.png" width="100"/>

Example of a release having custom asset/file attached to the release.

<img src=".github/images/gh-release-assets-example.png" width="600"/>

## Appendix D - Rubric

Total Points: 100 points

### Doxygen Configuration (15 points)

- (+5) The `PROJECT_NAME` is set properly.
- (+5) The `GENERATE_LATEX` is set to no.
- (+5) The `HAVE_DOT` is set to no.

### Function Documentation (25 points)

For each function,

- (+2.5) Uses the correct style of comment.
- (+5) The arguments and/or return type is correctly documented.
- (+5) Function has a reasonable description.

(12.5 points/function)

### File Documentation (25 points)

- (+10) The `piece.hpp` show up on the "File List" page and is clickable.
- (+15) The file-level documentation for `piece.hpp` renders properly.

### Doxygen Command Usage (5 points)

- (+5) Correctly use at least 3 uniques Doxygen special commands across the whole codebase.

### Makefile (5 points)

- (+5) Running `make docs` create HTML documentation in the `html/` folder.

### GitHub Release (25 points)

- (+5) A screenshot of the rendered HTML documentation of the "File List" page is included in the release description. This indicates that the student may not know how to view the generate HTML documentation.
- (+5) A screenshot of the rendered HTML documentation of the first function is included in the release description.
- (+5) A screenshot of the rendered HTML documentation of the second function is included in the release description.
- (+5) The `docs.tar.gz` is attached to the release. This serves as a proof that students know how to run doxygen to generate the documentation. They also know where the output is.
- (+5) The `docs.tar.gz` contains the generated HTML documentation files.
