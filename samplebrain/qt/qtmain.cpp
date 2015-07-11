#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <QtGui>
#include "MainWindow.h"

#include "jellyfish/audio.h"

#include "process_thread.h"
#include "audio_thread.h"

using namespace std;

audio_device *a = NULL;

void run_audio(void* c, unsigned int frames) {
    audio_thread *at = (audio_thread*)c;
    a->left_out.zero();
    at->process(a->left_out);
}

int main( int argc , char *argv[] ){
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();

    process_thread pt;
    audio_thread at(pt);

    a = new audio_device("samplebrain",44100,2048);
	a->m_client.set_callback(run_audio, &at);

    return app.exec();
}
