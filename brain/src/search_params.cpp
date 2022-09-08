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

#include "search_params.h"

using namespace spiralcore;
using namespace std;

ios &spiralcore::operator||(ios &s, search_params &p) {
    u32 version=0;
    string id("search_params");
    s||id||version;
    s||p.m_ratio||p.m_n_ratio||p.m_fft1_start||p.m_fft1_end;
    s||p.m_usage_importance||p.m_num_synapses||p.m_stickyness;
    return s;
}
