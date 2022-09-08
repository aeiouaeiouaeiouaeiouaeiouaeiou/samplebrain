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

#include <string>
#include <vector>
#include "spiralcore/sample.h"
#include "spiralcore/types.h"

#ifndef WINDOW
#define WINDOW

namespace spiralcore {

class window {
public:
    window();
    void init(u32 length);

    enum type {
        DODGY = 0,
        BARTLETT,
        BLACKMAN,
        FLAT_TOP,
        GAUSSIAN,
        HAMMING,
        HANN,
        RECTANGLE,
        MAX_TYPES
    };

    void set_current_type(type t) { m_current_type=t; }
    void run(const sample &sample) const;

    friend ios &operator||(ios &s, window &b);

private:
    void clear();

    type m_current_type;

    std::vector<sample*> m_windows;

};

ios &operator||(ios &s, window &b);

}

#endif
