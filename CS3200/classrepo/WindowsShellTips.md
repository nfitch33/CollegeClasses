# Installation of OCAML in Windows Power Shell

In your windows search for Windows `Power Shell`

Run    `wsl --install`

```console
       wsl --install -d Ubuntu         
```

When the Ubuntu download is completed, it will likely ask you to reboot. Do so. The installation will automatically resume after the reboot.

Note: If it not resume after the reboot please run the above 2 commands again.

You will be prompted to use a Unix username and password. You can use  username and password which is provided by school. After entering you Username and password follow the below commands to continue:

Run the following command to update the APT package manager, which is what helps to install Unix packages:     

 ```
 sudo apt update
```

Now run this command to upgrade all the APT software packages:

```
sudo apt upgrade -y
```

Then install some useful packages that we will need:
```
sudo apt install -y zip unzip build-essential
```
Install OPAM

Mac---> If you’re using Homebrew, run this command:
```
brew install opam
```
If you’re using MacPorts, run this command:
```
sudo port install opam
```
Windows---> Run this command from Ubuntu:
```
sudo apt install opam
```       
Initialize OPAM

Warning:

Do not put sudo in front of any opam commands. That would break your OCaml installation.

Linux, Mac, and WSL2. Run:
```
opam init --bare -a -y
```
Don’t worry if you get a note about making sure .profile is “well-sourced” in .bashrc. You don’t need to do anything about that.

If you get a warning that OPAM is out of date, update it by running:
```
opam update
```
WSL1. Hopefully you are running WSL2, not WSL1. But on WSL1, run:
```
opam init --bare -a -y --disable-sandboxing
```
Create an OPAM Switch
```
opam switch create cs3200-2024fa ocaml-base-compiler.5.2.0
```
You might be prompted to run the next command. It won’t matter whether you do or not, because of the very next step we’re going to do (i.e., logging out).

```
eval $(opam env)
```
Now we need to make sure your OCaml environment was configured correctly. Logout from your OS (or just reboot). Then re-open your terminal and run this command:

```
opam switch list
```
You should get output like this:

#  switch         compiler
→  cs3110-2024fa  ocaml-base-compiler.5.2.0

There might be other lines if you happen to have done OCaml development before. There will be another column named “description” whose contents are not shown here. Double check the following:

You must not get a warning that “The environment is not in sync with the current switch. You should run eval $(opam env)”. If either of the two issues below also occur, you need to resolve this issue first.

There must be a right arrow in the first column next to the current semester’s switch.

That switch must have the right name and the right compiler version.

Warning:

If you do get that warning about opam env, something is wrong. Your shell is probably not running the OPAM configuration commands that opam init was meant to install. You could try opam init --reinit to see whether that fixes it. Also, make sure you really did log out of your OS (or reboot).

Continue by installing the OPAM packages we need:

opam install -y utop odoc ounit2 qcheck bisect_ppx menhir ocaml-lsp-server ocamlformat
Make sure to grab that whole line above when you copy it. You will get some output about editor configuration. Unless you intend to use Emacs or Vim for OCaml development, you can safely ignore that output. We’re going to use VS Code as the editor in these instructions, so let’s ignore it.

You should now be able to launch utop, the OCaml Universal Toplevel.
```
Run   utop
```
Enter 3110 followed by two semicolons. Press return. The # is the utop prompt; you do not type it yourself.

# 3110;;
- : int = 3110
Stop to appreciate how lovely 3110 is. Then quit utop. Note that this time you must enter the extra # before the quit directive.

# #quit;;

Download Visual Studio Code

Launch VS Code. Open the extensions pane, either by going to View → Extensions, or by clicking on the icon for it in the column of icons on the left — it looks like four little squares, the top-right of which is separated from the other three.

At various points in the following instructions you will be asked to “open the Command Palette.” To do that, go to View → Command Palette. There is also an operating system specific keyboard shortcut, which you will see to the right of the words “Command Palette” in that View menu.

Windows only: Install the “WSL” extension.

Mac only: Open the Command Palette and type “shell command” to find the “Shell Command: Install ‘code’ command in PATH” command. Run it.

Third, regardless of your OS, close any open terminals — or just logout or reboot — to let the new path settings take effect, so that you will later be able to launch VS Code from the terminal.

Fourth, on Windows only, open the Command Palette and run the command “WSL: Connect to WSL”. (If you on Mac, skip ahead to the next step.) The first time you do this, it will install some additional software. After that completes, you will see a “WSL: Ubuntu” indicator in the bottom-left of the VS Code window. Make sure that you see “WSL: Ubuntu” there before proceeding with the next step below. If you see just an icon that looks like >< then click it, and choose “Connect to WSL” from the Command Palette that opens.

Fifth, again open the VS Code extensions pane. Search for and install the “OCaml Platform” extension from OCaml Labs. Be careful to install the extension with exactly that name.

Warning:

The extensions named simply “OCaml” or “OCaml and Reason IDE” are not the right ones. They are both old and no longer maintained by their developers.

Try to excute the Hello World programme in the VS code and run the output
create hello file,  save it, then run this command : ocamlc -o test test2.ml
then run ./test

Note: test2.ml is the name of the code which you have choose
