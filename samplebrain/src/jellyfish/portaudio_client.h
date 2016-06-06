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

	class device_options
	{
		public:
		enum type {READ,WRITE,READWRITE};
		unsigned int buffer_size;
		unsigned int num_buffers;
		unsigned int samplerate;
		unsigned int in_channels;
		unsigned int out_channels;
	};

	bool   attach(const string &client_name, const device_options &dopt);
	void   detach();
	bool   is_attached()                   { return m_attached; }
	void   set_callback(void(*run)(void*, unsigned int),void *context) { run_callback=run; run_context=context; }
	void   set_outputs(const float *l, const float *r) { m_left_data=l; m_right_data=r; }
	void   set_inputs(float *l, float *r) { m_left_in_data=l; m_right_in_data=r; }

protected:

	static int  process(const void *input_buffer, void *output_buffer,
                        unsigned long frames_per_buffer,
                        const PaStreamCallbackTimeInfo* time_info,
                        PaStreamCallbackFlags status_flags,
                        void *user_data);

private:

	static long unsigned int  m_buffer_size;
	static long unsigned int  m_sample_rate;
	static bool               m_attached;

	static const float *m_right_data;
	static const float *m_left_data;
	static float *m_right_in_data;
	static float *m_left_in_data;

	static void(*run_callback)(void *, unsigned int);
	static void *run_context;
};

#endif
