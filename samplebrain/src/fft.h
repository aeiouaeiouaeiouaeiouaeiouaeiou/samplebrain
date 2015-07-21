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

#include <fftw3.h>

#ifndef SPIRALCORE_FFT
#define SPIRALCORE_FFT

//#define __FFTWFLOAT__

namespace spiralcore {

class FFT
{
public:
    FFT(int length);
    ~FFT();
	void impulse2freq(const float *imp);

	fftw_plan m_plan;
	unsigned int m_length;
	double *m_in;
	fftw_complex *m_spectrum;
};

}

#endif
