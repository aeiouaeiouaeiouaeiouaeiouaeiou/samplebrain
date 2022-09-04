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

#include <pitchshift.h>

using namespace spiralcore;
using namespace std;
using namespace RubberBand;

RubberBandStretcher *pitchshift::m_stretcher = NULL;

void pitchshift::init(u32 srate) {
  if (m_stretcher!=NULL) delete m_stretcher;
  m_stretcher = new RubberBandStretcher(srate,1,
                                        RubberBandStretcher::OptionProcessRealTime);
}

void pitchshift::process(const sample &in, float freq_scale, sample &out) {
  if (freq_scale<1/256) freq_scale=1;
  if (freq_scale>255) freq_scale=255;
  m_stretcher->setPitchScale(freq_scale);
  const float *in_ptr = in.get_buffer();
  m_stretcher->process(&in_ptr, in.get_length(), false);
  float *out_ptr = out.get_non_const_buffer();
  m_stretcher->retrieve(&out_ptr, out.get_length());
}
