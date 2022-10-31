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

#include "status.h"
#include <iostream>

using namespace spiralcore;
using namespace std;

lo_address status::m_address = lo_address_new_from_url("osc.udp://localhost:8890");

void status::set_port(const std::string &port) {
  status::m_address = lo_address_new_from_url(string("osc.udp://localhost:"+port).c_str());
}

void status::_update(const std::string &msg) {
    lo_send(m_address,"/report","s",msg.c_str());
}

void status::sound_item(const std::string &name, const std::string &colour) {
  lo_send(m_address,"/sound-item","ss",name.c_str(),colour.c_str());
}

void status::sound_item_refresh() {
  lo_send(m_address,"/sound-item-refresh","");
}

void status::update(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    char s[4096];
    vsnprintf(s,4096,msg,args);
    status::_update(s);
    va_end(args);
}
