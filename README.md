# DWM fork - dynamic window manager

[dwm](dwm.suckless.org) is an extremely fast, small, and dynamic window manager for X.


## Requirements

In order to build dwm you need the Xlib header files.


## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
        sleep 1
    done &
    exec dwm


## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.


## Applied Patches

- [Alpha](https://dwm.suckless.org/patches/alpha/dwm-alpha-20180613-b69c870.diff): Allow dwm to have translucent bars, while keeping all the text on it opaque
- [Autostart](https://dwm.suckless.org/patches/autostart/dwm-autostart-20161205-bb3bd6f.diff): This patch will make dwm run "\~/.dwm/autostart_blocking.sh" and "\~/.dwm/autostart.sh &" before entering the handler loop. One or both of these files can be ommited. Be aware that dwm will not startup as long as autostart_blocking.sh is running and will stay completely unresponsive.
-
