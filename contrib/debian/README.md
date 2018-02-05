
Debian
====================
This directory contains files used to package fujicoind/fujicoin-qt
for Debian-based Linux systems. If you compile fujicoind/fujicoin-qt yourself, there are some useful files here.

## fujicoin: URI support ##


fujicoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install fujicoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your fujicoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/fujicoin128.png` to `/usr/share/pixmaps`

fujicoin-qt.protocol (KDE)

