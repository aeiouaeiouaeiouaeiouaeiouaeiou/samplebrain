#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <QtGui>
#include "MainWindow.h"

#include "jellyfish/audio.h"

#include "block.h"
#include "brain.h"
#include "renderer.h"

using namespace std;

audio_device *a = NULL;
renderer *rr = NULL;

void run_audio(void* c, unsigned int frames) {
    a->left_out.zero();
    rr->process(frames,a->left_out.get_non_const_buffer());

//    sleep(1);
}

int main( int argc , char *argv[] ){
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();

    mainWin.init_brain();
    rr = mainWin.m_renderer;
    a = new audio_device("samplebrain",44100,2048);
	a->m_client.set_callback(run_audio, &rr);

    return app.exec();
}
