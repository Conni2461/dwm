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
- [Fullgaps](https://dwm.suckless.org/patches/fullgaps/dwm-fullgaps-6.2.diff): Added gaps to dwm. Change gap size in config.h
- [Statuspadding](https://dwm.suckless.org/patches/statuspadding/dwm-statuspadding-20150524-c8e9479.diff): This makes the amount of horizontal and vertical padding in the status bar into configurable options.
- [Rotatestack](https://dwm.suckless.org/patches/rotatestack/dwm-rotatestack-20161021-ab9571b.diff): Stack rotation moves a client from the bottom to the top of the stack (or the other way round). This effectively rotates the clients by one position clockwise (or CCW, respectively).
- [Attachaside](https://dwm.suckless.org/patches/attachaside/dwm-attachaside-20180126-db22360.diff): Make new clients get attached and focused in the stacking area instead of always becoming the new master.
- [Cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/dwm-cyclelayouts-20180524-6.2.diff): Cycles through all avaiable layouts using MOD-CTRL-, and MOD-CTRL-.
- [center](https://dwm.suckless.org/patches/center/dwm-center-20160719-56a31dc.diff): Ability to center floating windows
- [centeredwindowname](http://dwm.suckless.org/patches/centeredwindowname/dwm-centeredwindowname-20180909-6.2.diff): Centered window names


## Added layouts
- [Grid Layout](https://dwm.suckless.org/patches/gridmode/dwm-gridmode-20170909-ceac8c9.diff) in which the windows are arranged in a grid of equal sizes.
- [centeredmaster](https://dwm.suckless.org/patches/centeredmaster/dwm-centeredmaster-6.1.diff): Centered master layout
