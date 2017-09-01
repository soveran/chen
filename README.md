# chen

Change directory entries.

chen lets you edit a list of directory entries with your default
text editor. Any renamed lines will result in renamed file names.

![chen in action](http://files.soveran.com/misc/chen.gif)

Installation
------------

Download the [latest release][releases] or check the available
[packages][packages]. You can also compile the source code in the
master branch.

[releases]: https://github.com/soveran/chen/releases
[packages]: https://github.com/soveran/chen/wiki/Distribution-Packages

Install chen into `/usr/local/bin` with the following command:

    $ make install

You can use `make PREFIX=/some/other/directory install` if you wish
to use a different destination. If you want to remove chen from
your system, use `make uninstall`.

Motivation
----------

I started this project a few days after reading about [Roamer][1],
a plain text file manager. Among other features, it allows the user
to rename files using a text editor. I became interested in the
renaming aspect and wrote a script with rc shell. This version just
bypassed the need to have the rc shell installed. There are many
similar tools, and if you like the idea of using your text editor
as a file manager, search and you will find :-)

Contributing
------------

If you find a bug, please create an issue detailing the ways to
reproduce it. If you have a suggestion, create an issue detailing
the use case.
