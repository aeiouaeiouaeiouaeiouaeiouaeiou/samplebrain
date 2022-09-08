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

#include <fft.h>
#include <string.h>

#include <iostream>

using namespace spiralcore;
using namespace std;

static const int MAX_FFT_LENGTH = 4096;

FFT::FFT(u32 length, u32 bins) :
  m_length(length),
  m_num_bins(bins),
  m_in(new double[length]),
  m_spectrum(new fftw_complex[length]),
  m_bin(new float[bins])
{
  memset(m_spectrum,0,sizeof(fftw_complex)*length);
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

static const float SRATE = 44100;

float FFT::calculate_dominant_freq() {
  double highest = 0;
  u32 index = 0;
  for (u32 i=0; i<m_length/2; ++i) {
    double t = m_spectrum[i][0]*m_spectrum[i][0];
    if (t>highest) {
      index=i;
      highest=t;
    }
  }
  float freq = index * (SRATE/(float)m_length);
  if (freq<0.01) freq=0.01;
  return freq;
}

void FFT::calculate_bins() {
  float useful_area = m_length/2;

  for (unsigned int n=0; n<m_num_bins; n++) {
    float value = 0;

    float f = n/(float)m_num_bins;
    float t = (n+1)/(float)m_num_bins;
    //f*=f;
    //t*=t;
    u32 from = f*useful_area;
    u32 to = t*useful_area;

    //cerr<<"fft bin:"<<from<<" "<<to<<" - "<<m_length<<endl;

    for (u32 i=from; i<=to; i++) {
      if (i<m_length) {
        value += m_spectrum[i][0]*m_spectrum[i][0];
      }
    }

    if (value<0) value=-value;
    m_bin[n]=value;
  }


}
