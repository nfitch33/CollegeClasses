<h2 align="center">
CS3560 Homework Assignment 2: Makefile (100 Points)<br/>
Due date: Please check the entry on Canvas
</h2>

The purpose of this assignment is to help you get comfortable with a build system (GNU Make) and shell commands. Be ready to solve any error that occur! You are expected to read and try to understand program's output and error messages.

You are expected to test your implementation yourself (e.g. by running the `make` command against your `Makefile`). Even though the grading script is giving you some feedbacks, it is not a replacement for your own testing.
It is definitely not designed to help with your debugging. You are expected to be able to use tools you learn in this class yourself during quizzes and the exam.

You can view these early feedback by visiting `https://github.com/OU-CS3560/<repository-name>/actions` in your browser (Do not forget to replace `<repository-name>` with your repository name).
Then, click on one of the run and click on the `grade-hw` job (on the left side-bar) to view the run's output.

## 1 - Reading Assignments

Please read the following articles/book.

- At least Chapter 1 to 5 and Chapter 12 of a book "Managing Projects with GNU Make" (2004) [http://www.oreilly.com/openbook/make3/book/](http://www.oreilly.com/openbook/make3/book/) You may want to also take a look at Chapter 7 and 11.
- [Dealing with Multiple (C++) Files](http://csundergrad.science.uoit.ca/courses/cpp-notes/notes/dealing-with-multiple-files.html) by Faisal Qureshi.
- [Creating a personal access token (classic)](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens#creating-a-personal-access-token-classic)
- [Authorizing a personal access token for use with SAML single sign-on](https://docs.github.com/en/enterprise-cloud@latest/authentication/authenticating-with-saml-single-sign-on/authorizing-a-personal-access-token-for-use-with-saml-single-sign-on)
- [Cloning a repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)


If you are planning on using a SSH URL to clone the repository, please also read

- [Generating a new SSH key and adding it to the ssh-agent](https://docs.github.com/en/enterprise-cloud@latest/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)
- [Adding a new SSH key to your GitHub account](https://docs.github.com/en/enterprise-cloud@latest/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)
- [Authorizing an SSH key for use with SAML single sign-on](https://docs.github.com/en/enterprise-cloud@latest/authentication/authenticating-with-saml-single-sign-on/authorizing-an-ssh-key-for-use-with-saml-single-sign-on)
- [Cloning with SSH URLs](https://docs.github.com/en/get-started/getting-started-with-git/about-remote-repositories#cloning-with-ssh-urls)

If you want to know more about SAML SSO, please read [About authentication with SAML single sign-on](https://docs.github.com/en/enterprise-cloud@latest/authentication/authenticating-with-saml-single-sign-on/about-authentication-with-saml-single-sign-on).


## 2 - Installation of the Required Software

This can be skipped if you already have the required software. If you are on Windows, we highly recommend that
you [install WSL](https://learn.microsoft.com/en-us/windows/wsl/install), and then install these softwares inside WSL.

- C++ Compiler: the GNU Compiler Collection (GCC) OR Clang
- GDB (if you install GCC)
- LLDB (if you install Clang)
- GNU Make
- Git (if it is not yet installed)
- tar (if it is not yet installed)

Use keyword like "how to install X on Y" in your preferred search engine if you need to know how to install
these softwares on your system.

## 3 - Solve the problems `:problem-list:`

Solve all of the following problems.

- `sandstorm`
- `odd-or-even-makefile`
- `broken-shell`
- `cs-curriculum`
- `simple-project`

Please read the `README.md` file in each problem's folder for the instructions. If you are spending more than 1 hour on a problem,
make a commit of whatever you have, push it to GitHub and reach out to us.

## 4 - Commit and push to GitHub

We will be using your repository in GitHub Classroom to grade, so make sure to make a commit (or commits) of your solution
and push it out to GitHub.

If you need a refresher on how to push, please read [this article](https://docs.github.com/en/get-started/using-git/pushing-commits-to-a-remote-repository).

## 5 - Submission

1. Make sure that all commits are pushed to GitHub.
2. Submit the link to your Github Classroom repository to Canvas.

## Appendix A - About the Grading Scripts

Once you push your commit to GitHub, the grading scripts will be run. The result for each commit can be viewed
from the "Actions" tab (or `https://github.com/OU-CS3560/<your-repository-name>/actions`). You can
also click on the :x: icon (or the :heavy_check_mark: icon) next to the commit's message of the latest
commit then click "Detail".

These grading scripts are our way of giving you early feedbacks. In most cases, the scores you see
from the grading script's result will be your final scores. However, we reserved the rights to overrule the
result from the grading scripts. In the end, you should be implementing a solution that satisfies the
requirements stated in the problem's prompt. The grading script is piece of software, so it is bounded to have
bugs. We as the author of the the script may forget to check a certain case, and your implementation happen
to be this said case. Thus, double check your work even when the grading script is reporting full mark.

Even though the grading script is giving you feedback, we expect that you will debug your implementation
manually. If you start to randomly change your implementation just to see how the grading script is reacting
to the change, you are on the wrong track. Instead we suggest you use the debugging techniques from
Chapter 12 of the book "Managing Projects with GNU Make" to find out the root cause of the issue.

However, if you honestly believe that the behavior of the grading script is incorrect, make a commit of whatever
you have implemented so far, push it out to GitHub and get in touch with us for clarification.

## Appendix B - Common Errors

### SAML SSO Error

From [Authorizing a personal access token for use with SAML single sign-on](https://docs.github.com/en/enterprise-cloud@latest/authentication/authenticating-with-saml-single-sign-on/authorizing-a-personal-access-token-for-use-with-saml-single-sign-on),

> To use a personal access token (classic) with an organization that uses SAML single sign-on (SSO), you must first authorize the token.

As the quote suggest, the token need to be authorized before it can be used with an organization that uses SAML SSO. Our OU-CS3560 is using
this SAML SSO, so you need to authorize your token. Please read the article above for how to authorize your token.

### "g++ \*.cpp" does not work

This assignment is designed so that `g++ *.cpp` will not work. Instead, please use commands that compile
each file individually then later link object files together to create an executable file.
If you need an example, please read an article by Faisal Qureshi in the reading assignment.

### Other common errors

For each of these errros, please visit its link for details. These are common error we have been seeing throughout the years, so they are
kept in a common location.

- [Git - Git does not ask for a password anymore, so I cannot enter my token](https://github.com/OU-CS3560/examples/tree/main/faq#git---git-does-not-ask-for-a-password-anymore-so-i-cannot-enter-my-token)
- [Git - Unable to access / The requested URL returned error: 403](https://github.com/OU-CS3560/examples/tree/main/faq#git---unable-to-access-the-repository--the-requested-url-returned-error-403)
- [Git - Authentication failed with git clone when using password](https://github.com/OU-CS3560/examples/tree/main/faq#frequently-asked-questions)
- [Shell - Getting a "Command not found" error](https://github.com/OU-CS3560/examples/tree/krerkkiat/add-gh-classroom-docs/faq#shell---getting-a-command-not-found-error)
- [Shell - Getting a "permission denied" when trying to run my program](https://github.com/OU-CS3560/examples/tree/main/faq#shell---getting-a-permission-denied-when-trying-to-run-my-program)

You may find error not listed here in https://github.com/OU-CS3560/examples/tree/main/faq

## Appendix C - Rubric

Total: 100 points

### Problem - sandstorm (10 points)

### Problem - odd-or-even-makefile (10 points)

### Problem - broken-shell (10 points)

### Problem - cs-curriculum (10 points)

### Problem - simple-project (60 points)
