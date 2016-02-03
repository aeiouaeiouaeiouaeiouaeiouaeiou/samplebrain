// Copyright (C) 2015 Dave Griffiths
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <QtGui>
#include "MainWindow.h"

#include "process_thread.h"
#include "audio_thread.h"
//#include "pitchshift.h"

using namespace std;

int main( int argc , char *argv[] ){
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();

    //pitchshift::init(44100);

    process_thread pt;
    audio_thread at(pt);
    pt.register_renderer(at.m_left_renderer, at.m_right_renderer);

    return app.exec();
}
