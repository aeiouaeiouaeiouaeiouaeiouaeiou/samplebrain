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

#include <fft.h>
#include <jellyfish/core/types.h>

using namespace spiralcore;

static const int MAX_FFT_LENGTH = 4096;

FFT::FFT(int length) :
    m_length(length),
    m_in(new double[length]),
    m_spectrum(new fftw_complex[length])
{
	m_plan = fftw_plan_dft_r2c_1d(m_length, m_in, m_spectrum, FFTW_ESTIMATE);
}

FFT::~FFT()
{
	delete[] m_in;
	fftw_destroy_plan(m_plan);
}

void FFT::impulse2freq(const float *imp)
{
    unsigned int i;

    for (i=0; i<m_length; i++)
    {
        m_in[i] = imp[i];
    }

    fftw_execute(m_plan);
}
