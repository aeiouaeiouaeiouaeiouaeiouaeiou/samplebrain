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
#include "audio.h"
#include <sndfile.h>

using namespace std;
using namespace spiralcore;

audio_device::audio_device(const string &clientname, u32 samplerate, u32 buffer_size) :
    m_recording(false),
    m_record_filename(""),
    m_samplerate(samplerate) {
  // connect to default device
  m_client.init();
  connect("", clientname, samplerate, buffer_size);
}

void audio_device::connect(const string &output_device_name, const string &clientname, u32 samplerate, u32 buffer_size) {
  m_client.detach();
  
  left_out.allocate(buffer_size);
  right_out.allocate(buffer_size);
  left_in.allocate(buffer_size);
  right_in.allocate(buffer_size);
  m_samplerate = samplerate;

  portaudio_client::device_options opt;
  opt.buffer_size = buffer_size;
  opt.num_buffers = 2;
  opt.samplerate = samplerate;
  opt.in_channels = 2;
  opt.out_channels = 2;

  m_client.set_outputs(left_out.get_buffer(), right_out.get_buffer());
  m_client.set_inputs(left_in.get_non_const_buffer(), right_in.get_non_const_buffer());
  m_client.attach(output_device_name,clientname,opt);
}

void audio_device::save_sample(const string &filename, unsigned int channels, const sample s) {
    SF_INFO sfinfo;
    sfinfo.format=SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    sfinfo.frames=s.get_length();
    sfinfo.samplerate=m_samplerate;
    sfinfo.channels=channels;
    sfinfo.sections=1;
    sfinfo.seekable=0;
    SNDFILE* f=sf_open(filename.c_str(), SFM_WRITE, &sfinfo);
    if (!f) cerr<<"couldn't open "<<filename<<endl;
    u32 written = sf_writef_float(f, s.get_buffer(), s.get_length());
    if (written!=s.get_length()) cerr<<"error: wrote "<<written<<endl;
    sf_close(f);
}

void audio_device::start_recording(std::string filename) {
    m_record_filename=filename;
    m_recording=true;
    m_record_buffer.clear();
    m_record_counter=0;
}

void audio_device::stop_recording() {
    m_recording=false;
}


void audio_device::maybe_record() {
    if (m_recording) {
      sample news(left_out.get_length()*2);
      for (unsigned int i=0; i<left_out.get_length(); i++) {
        news[i*2]=left_out[i];
        news[i*2+1]=right_out[i];
      }
      
      m_record_buffer.add(news);
      m_record_counter++;

      // save "every now and again"
      if (m_record_counter%10==0) {
        save_sample(m_record_filename+".wav",2,m_record_buffer);
      }
    }
}


