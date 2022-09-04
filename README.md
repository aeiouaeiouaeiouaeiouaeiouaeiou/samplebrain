# s a m p l e   b r a i n

## What is this?

A custom sample granulation app designed by Aphex Twin


   
## Linux install:

Install libraries for the sample engine:
    
    $ sudo apt install libsndfile1-dev portaudio19-dev liblo-dev libfftw3-dev

Install dependancies for the graphical user interface:
        
    $ sudo apt install build-essential qtcreator qt5-default

Build it:

    $ qmake
    $ make

## What's here

1. app:
    main app and QT gui code
2. brain:
    sample granulation engine code
3. cooking:
    * sketches and ideas
    * proof of concept written in python
    * initial attept at clojure version (abandoned)
    
