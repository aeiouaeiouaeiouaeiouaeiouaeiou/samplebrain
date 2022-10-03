// copyright (C) 2003 david griffiths <dave@pawfal.org>
//
// this program is free software; you can redistribute it and/or modify
// it under the terms of the GNU general public license as published by
// the free software foundation; either version 2 of the license, or
// (at your option) any later version.
//
// this program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  see the
// GNU general public license for more details.
//
// you should have received a copy of the GNU general public license
// along with this program; if not, write to the free software
// foundation, inc., 59 temple place - suite 330, boston, MA 02111-1307, USA.

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <portaudio.h>

using namespace std;

#ifndef PA_CLIENT
#define PA_CLIENT

class portaudio_client
{
 public:
  portaudio_client();
  ~portaudio_client();
  bool init();

  class device_options {
  public:
    enum type {READ,WRITE,READWRITE};
    unsigned int buffer_size;
    unsigned int num_buffers;
    unsigned int samplerate;
    unsigned int in_channels;
    unsigned int out_channels;
  };

  class device_desc {
  public:
    string name;
    int id;
    bool default_input;
    bool default_output;
  };

  vector<portaudio_client::device_desc> m_devices;

  bool   attach(const string &requested_output_device, const string &client_name, const device_options &dopt);
  void   detach();
  bool   is_attached()  { return m_attached_device!=-1; }
  void   set_callback(void(*run)(void*, unsigned int),void *context) { run_callback=run; run_context=context; }
  void   set_outputs(const float *l, const float *r) { m_left_data=l; m_right_data=r; }
  void   set_inputs(float *l, float *r) { m_left_in_data=l; m_right_in_data=r; }

  string m_status;
  
 protected:

  static int  process(const void *input_buffer, void *output_buffer,
		      unsigned long frames_per_buffer,
		      const PaStreamCallbackTimeInfo* time_info,
		      PaStreamCallbackFlags status_flags,
		      void *user_data);

 private:

  int device_name_to_id(const string &name);
  
  static long unsigned int  m_buffer_size;
  static bool               m_initialised;
  static int                m_attached_device;
  
  static const float *m_right_data;
  static const float *m_left_data;
  static float *m_right_in_data;
  static float *m_left_in_data;
  
  static void(*run_callback)(void *, unsigned int);
  static void *run_context;
  static PaStream *m_stream;

};

#endif
