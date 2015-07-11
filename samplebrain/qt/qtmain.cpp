#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <QtGui>
#include "MainWindow.h"

#include "process_thread.h"
#include "audio_thread.h"

using namespace std;

int main( int argc , char *argv[] ){
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();

    process_thread pt;
    audio_thread at(pt);

    return app.exec();
}
