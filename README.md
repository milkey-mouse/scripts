# scripts

The contents of my `/usr/local/bin`: useful scripts that are too small to
warrant their own page.

# Disclaimer
Some of these were meant to solve a one-off problem, so they are the code
equivalent of this:

![There, I fixed it](https://www.banpei.net/files/tifi-mmmpringles.jpg)

Use at your own risk!

But some others I have spent more time on, and are pretty cool/work well. Here
are some of the best scripts in this repo:

 - [`cover`](cover): display album covers for music playing in mpv
 - [`licenser`](licenser): put a license in your project with one command
 - [`fzf_run`](fzf_run): replace dmenu with a normal terminal & fzf
 - [`play`](play): search for and play music with mpv simply
 - [`play?`](play?): query metadata for currently playing music
 - [`singleton`](singleton): kill old instances of a program so one copy runs at a time
 - [`switch_focus`](switch_focus): global Alt-Tab for [sway](https://swaywm.org)

# Dependencies

All of these scripts have a dependency on the coreutils (find, grep, etc.).
Many of them need these additional programs to run:

 - [fzf](https://github.com/junegunn/fzf)
 - [jq](https://stedolan.github.io/jq)
