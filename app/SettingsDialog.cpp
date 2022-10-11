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

#include <QtGui>
#include <iostream>
#include <list>

#include "MainWindow.h"
#include "SettingsDialog.h"
#include "feedback.h"

using namespace std;

SettingsDialog::SettingsDialog(MainWindow *parent):
  m_device(""),
  m_parent(parent),
  m_buffersize(2048),
  m_samplerate(44100) {
  m_Ui.setupUi(this);
}

void SettingsDialog::connect() {
  audio_thread *at = m_parent->get_audio_thread();
  at->restart_audio(m_device,m_samplerate,m_buffersize);
  m_Ui.messagesLabel->setText(at->m_audio_device->m_client.m_status.c_str());
}
