# Samplebrain

A custom sample mashing app designed by Aphex Twin.

Samplebrain chops samples up into a 'brain' of interconnected small
sections called blocks which are connected into a network by
similarity. It processes a target sample, chopping it up into blocks
in the same way, and tries to match each block with one in its brain
to play in realtime.

This allows you to interpret a sound with a different one. As we
worked on it (during 2015 and 2016) we gradually added more and more
tweakable parameters until it became slightly out of control.

![](docs/pics/screenshot.png)

Quick start:

1. Load a bunch of samples into the brain
2. Click (re)generate brain
3. Load a loop sample into the target
4. Click (re)generate blocks
5. Press play
6. Tweak brain

The default block size (3000) is really high to prevent CPU glitches -
500 to 1000 is a better range.

# [Demo brain session](https://static.thentrythis.org/samplebrain/demo.samplebrain)

Load this file using "load session" not "load brain" (sessions contain
both the target and brain samples).

# [Manual](docs/manual.md)

Full description of all the parameters and a bit of the thinking
behind it.

# Binaries

* **Windows**: (new fix for ridiculous CPU usage) [samplebrain_0.18.1_win.zip](https://static.thentrythis.org/samplebrain/samplebrain_0.18.1_win.zip)
* **Mac (new fix for silence/should work on m1)**: [samplebrain_0.18.1_macintel.zip](https://static.thentrythis.org/samplebrain/samplebrain_0.18.1_macintel.app.zip)

Thank you to [Nik Gaffney](http://fo.am) for help with the Apple builds

Mac note: As this software is not on the apple store, to run the
binary you need to tell your mac it's ok: Go to System Preferences >
Security & Privacy > General. At the bottom of the window, select
"Allow apps to be downloaded from Anywhere".

Windows note: Some people are reporting problems with windows 11.
          
# Old/broken/spurious binaries
    
* **Windows* *: [samplebrain_0.18_win.zip](https://static.thentrythis.org/samplebrain/samplebrain_0.18_win.zip)
* **Mac (intel)**: [samplebrain_0.18_macintel.zip](https://static.thentrythis.org/samplebrain/samplebrain_0.18_macintel.zip)
* **Mac (m1)**: [samplebrain_0.18_m1_v2.dmg](https://static.thentrythis.org/samplebrain/samplebrain_0.18_m1_v2.dmg) 
            
**Linux install (Ubuntu)**

    $ sudo add-apt-repository ppa:thentrythis/samplebrain
    $ sudo apt update
    $ sudo apt install samplebrain

If you'd like the right font, optionally:

    $ sudo apt install ttf-mscorefonts-installer

# Building from source
## Linux (Ubuntu)
Install libraries for the sample engine (use brew on mac, MinGW on win):

    $ sudo apt install libsndfile1-dev portaudio19-dev liblo-dev libfftw3-dev

Install dependancies for the interface:

    $ sudo apt install build-essential qtcreator qt5-default

Build & run it:

    $ mkdir build
    $ cd build
    $ qmake ..
    $ make
    $ sudo make install
    $ samplebrain

## Mac
Install libraries for sample engine:

    $ brew install fftw portaudio liblo

Install dependancies for the interface:

    $ brew install qt
    $ brew link qt

Build & run it:

    $ mkdir build
    $ cd build
    $ qmake ..
    $ make
    $ sudo make install
    $ samplebrain

# Mac build additions

To make a mac app bundle:

Run `macdeployqt` to copy all dependencies inside the app.

Create Mac app bundle:

    $ cd build
    $ macdeployqt

Copy desktop/samplebrain.icns (the icon) to the Resources directory in the bundle.

    $ cp ../desktop/samplebrain.icns samplebrain.app/Contents/Resources

Edit Info.plist to add samplebrain.icns to CFBundleIconFile. Key `CFBundleIconFile` should match:

	<key>CFBundleIconFile</key>
	<string>samplebrain.icns</string>

## What's here

1. brain:
    * samplebrain engine code
2. app:
    * code to build the Qt GUI app
3. gui:
    * qt designer project files
4. desktop:
    * various icon files etc
4. cooking:
    * some sketches and ideas
    * proof of concept written in python
    * brief initial (abandoned) attempt at clojure version

MFCC algo courtesy of the Aquila library by Zbigniew Siciarz MIT/X11
licence 2007-2014 (see brain/src/aquila/LICENCE)

This program is free software licenced under GNU General Public
License version 2 (see LICENCE).

Written by [Dave Griffiths at Then Try This](http://thentrythis.org).

