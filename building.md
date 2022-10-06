# Building from source
## Linux (Ubuntu)
Install libraries for the sample engine (use brew on mac, MinGW on win):

    $ sudo apt install libsndfile1-dev portaudio19-dev liblo-dev libfftw3-dev

Install dependencies for the interface:

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

    $ brew install fftw portaudio liblo libsndfile

Install dependencies for the interface:

    $ brew install qt
    $ brew link qt

Build & run it:

    $ mkdir build
    $ cd build
    $ qmake ..
    $ make

`samplebrain.app` should then be in the app folder for you to run.

# Mac build additions

To make a mac app bundle:

Run `macdeployqt` which copies all dependencies inside the app.

    $ cd build
    $ macdeployqt

If the icon is not visible, you might need to copy desktop/samplebrain.icns (the icon) to the Resources directory in the app bundle.

    $ cp ../desktop/samplebrain.icns samplebrain.app/Contents/Resources

Then edit Info.plist to add samplebrain.icns to CFBundleIconFile. Key `CFBundleIconFile` should match:

	<key>CFBundleIconFile</key>
	<string>samplebrain.icns</string>

You might also need to resign the app bundle after making any changes

    $ codesign --force --deep --sign - samplebrain.app
