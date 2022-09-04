// Copyright (C) 2015 Foam Kernow
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

#include "window.h"
#include <cmath>
#include <iostream>

using namespace std;
using namespace spiralcore;

#ifndef M_PI
#define M_PI 3.141592653589
#endif

window::window() :
    m_current_type(RECTANGLE)
{
}

void window::clear() {
    for (vector<sample*>::iterator i=m_windows.begin(); i!=m_windows.end(); ++i) {
        delete *i;
    }
    m_windows.clear();
}

void window::init(u32 size) {
    clear();
    for (u32 i=0; i<MAX_TYPES; i++) {
        window::type t = (window::type)i;
        sample *s = new sample(size);

        switch(t) {
        case DODGY: {
            u32 start=size/6;
            u32 end=size/6;
            for (u32 n=0; n<size; ++n) {
                (*s)[n] = 1;
            }
            for(u32 i=0; i<start; ++i) {
                (*s)[i]=i/(float)start;
            }
            for(u32 i=0; i<end; ++i) {
                (*s)[(size-1)-i]=i/(float)end;
            }
        } break;
        case BARTLETT: {
            for (u32 n=0; n<size; ++n) {
                (*s)[n]=1.0 - (2.0 * fabs(n - (size - 1) / 2.0)) / (double(size - 1));
            }
        } break;
        case BLACKMAN: {
            for (u32 n=0; n<size; ++n) {
                (*s)[n]= 0.42 - 0.5 * cos(2.0 * M_PI * n / double(size - 1)) +
                    0.08 * cos(4.0 * M_PI * n / double(size - 1));
            }
        } break;
        case FLAT_TOP: {
            for (u32 n=0; n<size; ++n) {
                (*s)[n]=
                    1.0 - 1.93 * cos(2.0 * M_PI * n / double(size - 1)) +
                    1.29 * cos(4.0 * M_PI * n / double(size - 1)) -
                    0.388 * cos(6.0 * M_PI * n / double(size - 1)) +
                    0.0322 * cos(8.0 * M_PI * n / double(size - 1));
            }
        } break;
        case GAUSSIAN: {
            float sigma=0.5;
            for (u32 n=0; n<size; ++n) {
                (*s)[n]= exp((-0.5) * pow((n - (size - 1.0) / 2.0)/(sigma * (size - 1.0) / 2.0), 2.0));
            }
        } break;
        case HAMMING : {
            for (u32 n=0; n<size; ++n) {
                (*s)[n]= 0.53836 - 0.46164 * cos(2.0 * M_PI * n / double(size - 1));
            }
        } break;
        case HANN : {
            for (u32 n=0; n<size; ++n) {
                (*s)[n]= 0.5 * (1.0 - cos(2.0 * M_PI * n / double(size - 1)));
            }
        } break;
        case RECTANGLE : {
            for (u32 n=0; n<size; ++n) {
                (*s)[n] = 1;
            }
        } break;
        default: assert(0);
        }
        m_windows.push_back(s);
    }
}


void window::run(const sample &input) const {
    //assert(input.get_length()==m_windows[0]->get_length());

    for (u32 n=0; n<input.get_length(); ++n) {
        input[n]*=(*m_windows[m_current_type])[n];
    }
}

ios &spiralcore::operator||(ios &s, window &b) {
    u32 version=0;
    string id("window");
    s||id||version;
    s||b.m_current_type;
    std::ofstream *pos=dynamic_cast<std::ofstream*>(&s);
    if (pos!=NULL) {
        u32 size=0;
        // get the size from the first window
        if (b.m_windows.size()>0) {
            size=b.m_windows[0]->get_length();
        }
        s||size;
    } else {
        u32 size=0;
        s||size;
        // reinit using size if we are reading in
        b.init(size);
    }
    return s;
}
