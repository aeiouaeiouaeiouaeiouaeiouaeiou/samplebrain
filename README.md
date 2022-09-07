# s a m p l e   b r a i n

## What is this?

A custom sample smashing/re-aggregating app designed by Aphex Twin

Samplebrain chops samples up into a 'brain' of interconnected small
sections (blocks) connected into a network by similarity. It reads a
target sample, chops it up into blocks in the same way, and tries to
match each one with one of the blocks in it's brain to play in
realtime.

This (in theory) allows you to interpret one type of sound with
another. Over time we gradually added more and more controls until it
became slightly out of control and increasingly difficult to explain.

Quick start:

1. Load a bunch of samples into the brain
2. Click (re)generate brain
3. Load a loop sample into the target
4. Click (re)generate target
5. Press play

# [Manual](docs/manual.md)
    
# Binaries

* [Windows]()
* [Mac]()
* Linux - see building below
        
# Installing/building
     
## Linux install:

Install libraries for the sample engine:
    
    $ sudo apt install libsndfile1-dev portaudio19-dev liblo-dev libfftw3-dev

Install dependancies for the graphical user interface:
        
    $ sudo apt install build-essential qtcreator qt5-default

Build $ run it:

    $ cd app
    $ qmake
    $ make
    $ samplebrain
    
## What's here

1. brain:
    * samplebrain engine code
2. app:
    * code to build the Qt GUI app
3. gui:
    * qt designer project files
4. cooking:
    * sketches and ideas
    * proof of concept written in python
    * initial (abandoned) attempt at clojure version 
    
# Todos:

* Write VST version?

