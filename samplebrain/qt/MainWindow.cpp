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

#include <QtGui>
#include <iostream>

#include "MainWindow.h"
#include "feedback.h"

using namespace std;

MainWindow::MainWindow() :
    m_last_file("."),
    m_feedback("8890")
{
    m_Ui.setupUi(this);
    setUnifiedTitleAndToolBarOnMac(true);

    m_audio_address = lo_address_new_from_url("osc.udp://localhost:8888");
    m_process_address = lo_address_new_from_url("osc.udp://localhost:8889");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_status()));
    timer->start(1000);
    timer->setInterval(500);

    m_save_wav="";
    m_record_id=0;
}
