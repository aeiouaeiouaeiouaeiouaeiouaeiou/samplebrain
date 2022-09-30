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

#include <lo/lo.h>
#include <string>
#include <iostream>

#pragma once

namespace spiralcore {

class status {
public:
  static void _update(const std::string &msg);
  static void update(const char *msg, ...);
  static void sound_item(const std::string &name, const std::string &colour);
  static void sound_item_refresh();
  static void add_audio_device(const std::string &name);
  static lo_address m_address;
};

}
