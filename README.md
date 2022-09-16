# Samplebrain

A custom sample mashing app designed by Aphex Twin.

Samplebrain (made in 2015) chops samples up into a 'brain' of
interconnected small sections called blocks which are connected into a
network by similarity. It processes a target sample, chopping it up
into blocks in the same way, and tries to match each block with one in
it's brain to play in realtime.

This allows you to interpret a sound with a different one. Over time
developing it, we gradually added more and more tweakable parameters
until it became slightly out of control.    

![](docs/pics/screenshot.png)
    
Quick start:

1. Load a bunch of samples into the brain
2. Click (re)generate brain
3. Load a loop sample into the target
4. Click (re)generate target
5. Press play
6. Tweak brain

The default block size (3000) is really high to prevent CPU glitches -
500 to 1000 is a better range.
    
# [Manual](docs/manual.md)
        
# [Demo brain session](https://static.thentrythis.org/samplebrain/demo.samplebrain)    

Load this using "load session" not "load brain" - sessions contain
both the target and brain samples.
    
# Windows

* [samplebrain_0.18_win.zip](http://static.thentrythis.org/samplebrain/https://static.thentrythis.org/samplebrain/samplebrain_0.18_win.zip)

# Mac

* [samplebrain_0.18_macintel.zip](https://static.thentrythis.org/samplebrain/samplebrain_0.18_macintel.zip)

Contribution of a universal or apple silicon binary gratefully received (see building instructions below)

# Linux
    
    $ sudo add-apt-repository ppa:thentrythis/samplebrain
    $ sudo apt update
    $ sudo apt install samplebrain

If you'd like the right font, optionally:

    $ sudo apt install ttf-mscorefonts-installer
    
# Building from source:

Install libraries for the sample engine (use brew on mac, MinGW on win):
    
    $ sudo apt install libsndfile1-dev portaudio19-dev liblo-dev libfftw3-dev

Install dependancies for the interface:
        
    $ sudo apt install build-essential qtcreator qt5-default

Build $ run it:

    $ cd app
    $ qmake
    $ make
    $ sudo make install
    $ samplebrain

# Mac build additions:

To make a mac app bundle:
    
* Run `macdeployqt` to copy all dependancies inside the app.
* Copy desktop/samplebrain.icns (the icon) to the Resources directory in the bundle.
* Edit Info.plist to add samplebrain.icns to CFBundleIconFile.
    
## What's here

1. brain:
    * samplebrain engine code
2. app:
    * code to build the Qt GUI app
3. gui:
    * qt designer project files
4. desktop:
    * various icon file etc
4. cooking:
    * sketches and ideas
    * proof of concept written in python
    * initial (abandoned) attempt at clojure version 
    


