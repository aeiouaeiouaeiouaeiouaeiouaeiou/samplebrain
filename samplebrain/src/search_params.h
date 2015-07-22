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

#ifndef SEARCH_PARAMS
#define SEARCH_PARAMS

namespace spiralcore {

class search_params {
public:
search_params(float ratio, float n_ratio, int s1, int e1, int s2, int e2) :
    m_ratio(ratio),
        m_n_ratio(n_ratio),
        m_fft1_start(s1),
        m_fft1_end(e1),
        m_fft2_start(s2),
        m_fft2_end(e2) {}

    float m_ratio;
    float m_n_ratio;
    int m_fft1_start;
    int m_fft1_end;
    int m_fft2_start;
    int m_fft2_end;

};

}

#endif