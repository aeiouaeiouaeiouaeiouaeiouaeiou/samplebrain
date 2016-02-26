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

#include "feedback.h"
#include "sound_items.h"
#include <iostream>

using namespace spiralcore;
using namespace std;

feedback::feedback(string address) :
    m_osc(address)
{
    m_osc.run();
}


void feedback::poll(QStatusBar *s, sound_items *sound_items) {
    command_ring_buffer::command cmd;

    while (m_osc.get(cmd)) {
        string name = cmd.m_name;
        if (name=="/report") {
          s->showMessage(QString(cmd.get_string(0)));
        }
        if (name=="/sound-item") {
          sound_items->change_colour(cmd.get_string(0),
                                     cmd.get_string(1));
        }
        if (name=="/sound-item-refresh") {
          sound_items->recolour();
        }
    }
}
