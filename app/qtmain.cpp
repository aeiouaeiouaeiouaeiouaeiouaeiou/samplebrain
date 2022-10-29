// Copyright (C) 2022 Then Try This
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
#include <QSettings>

#include "MainWindow.h"

#include "process_thread.h"
#include "audio_thread.h"
#include "status.h"

using namespace std;

int main( int argc , char *argv[] ){

  
  QApplication app(argc, argv);
  
  QSettings settings("thentrythis", "samplebrain");

  // slight over-use of OSC servers here, but the are packaged nicely for
  // threadsafe (nonblocking) communication, and it's useful to expose all
  // moving parts for external control (i.e. the processing and the audio)
  
  if (!settings.contains("gui_port")) settings.setValue("gui_port", "62345");
  if (!settings.contains("audio_port")) settings.setValue("audio_port", "62346");
  if (!settings.contains("process_port")) settings.setValue("process_port", "62347");  

  string gui_port = settings.value("gui_port").toByteArray().constData();  
  string audio_port = settings.value("audio_port").toByteArray().constData();
  string process_port = settings.value("process_port").toByteArray().constData();

  status::set_port(gui_port);
  
  MainWindow mainWin(gui_port,audio_port,process_port,&settings);
  mainWin.show();
  process_thread pt(process_port);
  audio_thread at(audio_port,pt);
  
  pt.register_renderer(at.m_left_renderer, at.m_right_renderer, at.m_block_stream);
  mainWin.set_audio_thread(&at);

  if (!at.ok()) {
    mainWin.message("problem starting audio thread on port "+audio_port);
  }
  if (!pt.ok()) {
    mainWin.message("problem starting process thread on port "+process_port);
  }
  if (!mainWin.ok()) {
    mainWin.message("problem starting gui thread on port "+gui_port);
  }

  return app.exec();
}
