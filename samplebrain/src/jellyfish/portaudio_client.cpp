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

#include <stdio.h>
#include <limits.h>

#include "portaudio_client.h"

bool              portaudio_client::m_attached   = false;
long unsigned int portaudio_client::m_buffer_size = 0;
long unsigned int portaudio_client::m_sample_rate = 44100;
void            (*portaudio_client::run_callback)(void*, unsigned int buf_size)=NULL;
void             *portaudio_client::run_context   = NULL;
const float *portaudio_client::m_right_data=NULL;
const float *portaudio_client::m_left_data=NULL;
float *portaudio_client::m_right_in_data=NULL;
float *portaudio_client::m_left_in_data=NULL;

///////////////////////////////////////////////////////

portaudio_client::portaudio_client()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////

portaudio_client::~portaudio_client()
{
	detach();
}

/////////////////////////////////////////////////////////////////////////////////////////////

bool portaudio_client::attach(const string &client_name, const device_options &dopt)
{
	if (m_attached) return true;

    PaError err;
	err = Pa_Initialize();
    if( err != paNoError )
 	{
		cerr<<"could not init portaudio_client"<<endl;
        Pa_Terminate();
        fprintf( stderr, "an error occured while using the portaudio stream\n" );
        fprintf( stderr, "error number: %d\n", err );
        fprintf( stderr, "error message: %s\n", Pa_GetErrorText( err ) );
	}

    PaStreamParameters output_parameters;
    output_parameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (output_parameters.device == paNoDevice) {
		cerr<<"error: no default output device."<<endl;
    }
    output_parameters.channelCount = 2;       /* stereo output */
    output_parameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    output_parameters.suggestedLatency = Pa_GetDeviceInfo( output_parameters.device )->defaultLowOutputLatency;
    output_parameters.hostApiSpecificStreamInfo = NULL;

    PaStreamParameters input_parameters;
    input_parameters.device = Pa_GetDefaultInputDevice(); /* default output device */
    if (input_parameters.device == paNoDevice) {
		cerr<<"error: no default input device."<<endl;
    }
    input_parameters.channelCount = 2;       /* stereo output */
    input_parameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    input_parameters.suggestedLatency = Pa_GetDeviceInfo( input_parameters.device )->defaultLowInputLatency;
    input_parameters.hostApiSpecificStreamInfo = NULL;

    PaStream *stream;

    err = Pa_OpenStream(
              &stream,
              NULL, //&input_parameters,
              &output_parameters,
              dopt.samplerate,
              dopt.buffer_size,
              paClipOff,
              process,
              NULL);

    if( err != paNoError )
	{
		cerr<<"could not attach portaudio_client: "<<Pa_GetErrorText( err )<<endl;
		Pa_Terminate();
		return false;
	}

	err = Pa_StartStream(stream);

	if( err != paNoError )
	{
		cerr<<"could not start stream: "<<Pa_GetErrorText( err )<<endl;
		Pa_Terminate();
		return false;
	}

	m_attached=true;
	cerr<<"connected to portaudio..."<<endl;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void portaudio_client::detach()
{
    cerr<<"detaching from portaudio"<<endl;
    Pa_Terminate();
    m_attached=false;
}

/////////////////////////////////////////////////////////////////////////////////////////////

int portaudio_client::process(const void *input_buffer, void *output_buffer,
                             unsigned long frames_per_buffer,
                             const PaStreamCallbackTimeInfo* time_info,
                             PaStreamCallbackFlags status_flags,
                             void *user_data)
{
	m_buffer_size=frames_per_buffer;

	if(run_callback&&run_context)
	{
		// do the work
		run_callback(run_context, frames_per_buffer);
	}

	if (m_right_data && m_left_data)
	{
		float *out = (float*)output_buffer;
		for (unsigned int n=0; n<m_buffer_size; n++)
		{
			*out=m_left_data[n];
			out++;
			*out=m_right_data[n];
			out++;
		}
	}

	/*	if (m_right_in_data && m_left_in_data)
	{
		float *in = (float*)input_buffer;
		for (unsigned int n=0; n<m_buffer_size; n++)
		{
			m_left_in_data[n]=*in;
			in++;
			m_right_in_data[n]=*in;
			in++;
		}
		}*/
	return 0;
}
