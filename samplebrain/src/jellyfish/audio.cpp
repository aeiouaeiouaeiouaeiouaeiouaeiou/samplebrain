// Copyright (C) 2015 David Griffiths <dave@pawfal.org>
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
    left_out(buffer_size),
    right_out(buffer_size),
    left_in(buffer_size),
    right_in(buffer_size),
    m_recording(false),
    m_record_filename("")
{
    portaudio_client::device_options opt;
    opt.buffer_size = buffer_size;
    opt.num_buffers = 2;
    opt.samplerate = samplerate;
    opt.in_channels = 2;
    opt.out_channels = 2;

    m_client.attach(clientname,opt);
    m_client.set_outputs(left_out.get_buffer(), right_out.get_buffer());
    m_client.set_inputs(left_in.get_non_const_buffer(), right_in.get_non_const_buffer());

}

void audio_device::save_sample(const string &filename, const sample s) {
    SF_INFO sfinfo;
    sfinfo.format=SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    sfinfo.frames=s.get_length();
    sfinfo.samplerate=44100;
    sfinfo.channels=1;
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
    m_record_buffer_left.clear();
    m_record_buffer_right.clear();
    m_record_counter=0;
}

void audio_device::stop_recording() {
    m_recording=false;
}


void audio_device::maybe_record() {
    if (m_recording) {
        m_record_buffer_left.add(left_out);
        m_record_buffer_right.add(right_out);
        m_record_counter++;
        if (m_record_counter%10==0) {
            save_sample(m_record_filename+"-left.wav", m_record_buffer_left);
            save_sample(m_record_filename+"-right.wav", m_record_buffer_right);
        }
    }
}

#ifndef DONT_USE_FLUXA_GRAPH
void run_graph(void *c, unsigned int size) {
#ifndef DONT_USE_FLUXA_GRAPH
    audio_device *a=(audio_device *)c;
    a->left_out.zero();
    a->right_out.zero();
    a->m_graph->process(size, a->left_out, a->right_out);
    a->maybe_record();
#endif
}
#endif

void audio_device::start_graph(graph *graph) {
#ifndef DONT_USE_FLUXA_GRAPH
    m_graph = graph;
    m_client.set_callback(run_graph,this);
#endif
}
