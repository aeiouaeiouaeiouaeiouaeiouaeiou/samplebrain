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

#ifndef SETTINGS_DIALOG
#define SETTINGS_DIALOG

#include <QtGui>
#include <QDialog>
#include <QLineEdit>
#include <QSettings>
#include "gui/ui_settings.h"

#include <iostream>
#include <lo/lo.h>
#include <string>
#include <list>

using namespace std;


class MainWindow;

class SettingsDialog : public QDialog
{
  Q_OBJECT
 public:
  SettingsDialog(MainWindow *parent, QSettings *settings);

  Ui_SettingsDialog m_Ui;
  string m_device;

 protected:

  private slots:

   void samplerate(QString str) {
     try { m_samplerate=stoi(str.toStdString()); }
     catch(std::exception const & e) {
       m_samplerate=44100;
     }
   }
   void output_device(QString v) { m_device=v.toStdString();  }
   void buffersize(QString str) {
     try { m_buffersize=stoi(str.toStdString()); }
     catch(std::exception const & e) {
       m_buffersize=44100;
     }
   }
   void accept() { connect(); hide(); }
   void reject() { hide(); }
   void apply() { connect(); }

  void gui_port(QString str) {
    m_settings->setValue("gui_port",str);
  }

  void process_port(QString str) {
    m_settings->setValue("process_port",str);
  }

  void audio_port(QString str) {
    m_settings->setValue("audio_port",str);
  }

 private:

  void connect();
  MainWindow *m_parent;

  unsigned int m_buffersize;
  unsigned int m_samplerate;
  
  QSettings *m_settings;
};

#endif
