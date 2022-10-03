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

long unsigned int portaudio_client::m_buffer_size = 0;
bool              portaudio_client::m_initialised = false;
int               portaudio_client::m_attached_device = -1;
void            (*portaudio_client::run_callback)(void*, unsigned int buf_size)=NULL;
void             *portaudio_client::run_context   = NULL;
const float *portaudio_client::m_right_data=NULL;
const float *portaudio_client::m_left_data=NULL;
float *portaudio_client::m_right_in_data=NULL;
float *portaudio_client::m_left_in_data=NULL;
PaStream *portaudio_client::m_stream=NULL;

///////////////////////////////////////////////////////

portaudio_client::portaudio_client() {
}

/////////////////////////////////////////////////////////////////////////////////////////////

portaudio_client::~portaudio_client() {
  detach();  
}

bool portaudio_client::init() {
  m_initialised=false;
  if (!m_initialised) {
    PaError err;
    err = Pa_Initialize();
    if( err != paNoError ) {      
      Pa_Terminate();
      m_status="error initialising portaudio: "+string(Pa_GetErrorText(err))+"\n";
      return false;
    }

    // load all the devices we have
    PaDeviceIndex default_output_num = Pa_GetDefaultOutputDevice(); 
    PaDeviceIndex default_input_num = Pa_GetDefaultInputDevice(); 

    m_devices.clear();
    // get all devices we have available
    int numDevices = Pa_GetDeviceCount();
    if(numDevices <= 0) {
      m_status="portaudio error: no audio devices found";
      return false;
    } 

    const PaDeviceInfo *deviceInfo;

    for(int i=0; i<numDevices; i++) {
      deviceInfo = Pa_GetDeviceInfo(i);
      if (deviceInfo->maxOutputChannels>=2) {
        device_desc desc;
        desc.name = deviceInfo->name;
        desc.id = i;
        desc.default_input = i==default_input_num; 
        desc.default_output = i==default_output_num; 
        m_devices.push_back(desc);
      }
    }
    
    m_initialised=true;
    return true;
  }
  return true;
}

int portaudio_client::device_name_to_id(const string &name) {
  for (auto &d:m_devices) {
    if (d.name==name) return d.id;
  }
  return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////

bool portaudio_client::attach(const string &requested_output_device, const string &client_name, const device_options &dopt) {
  if (!init()) return false;  
  detach();

  int requested_output_id = device_name_to_id(requested_output_device);
  
  PaStreamParameters output_parameters;
  if (requested_output_device=="" || requested_output_id==-1) {
    // start up by connecting to the default one
    PaDeviceIndex default_output_num = Pa_GetDefaultOutputDevice(); 
    if (default_output_num == paNoDevice) {
      m_status="error: no default output device.";
      return false;
    } else {
      output_parameters.device = default_output_num;
    }
  } else {
      output_parameters.device = requested_output_id;
  }

  output_parameters.channelCount = 2;       /* stereo output */
  output_parameters.sampleFormat = paFloat32; /* 32 bit floating point output */
  output_parameters.suggestedLatency = Pa_GetDeviceInfo( output_parameters.device )->defaultLowOutputLatency;
  output_parameters.hostApiSpecificStreamInfo = NULL;
  m_status="connecting to "+string(Pa_GetDeviceInfo(output_parameters.device)->name)+" for output\n";

  // turn off input for the moment, it's causing
  // too many cross platform security issues

  /*PaStreamParameters input_parameters;
  PaStreamParameters *input_p=&input_parameters;
  input_parameters.device = input_device_num;
  if (true || input_parameters.device == paNoDevice) {
    cerr<<"error: no default input device."<<endl;
    input_p=0;
  } else {
     input_parameters.channelCount = 2;    
     input_parameters.sampleFormat = paFloat32;
     input_parameters.suggestedLatency = Pa_GetDeviceInfo( input_parameters.device )->defaultLowInputLatency;
     input_parameters.hostApiSpecificStreamInfo = NULL;
     cerr<<"Connecting to "<<Pa_GetDeviceInfo( input_parameters.device )->name<<" for input"<<endl;
  }	*/	  

  PaError err = Pa_OpenStream(&m_stream,
		      NULL,
		      &output_parameters,
		      dopt.samplerate,
		      dopt.buffer_size,
		      paClipOff,
		      process,
		      NULL);

  m_attached_device=output_parameters.device;

  if(err != paNoError) {
    m_status+="could not attach: "+string(Pa_GetErrorText(err))+"\n";
    detach();
    return false;
  }

  err = Pa_StartStream(m_stream);

  if(err != paNoError) {
    m_status+="could not start stream: "+string(Pa_GetErrorText(err))+"\n";
    detach();
    return false;
  }

  m_status+="we are connected to portaudio!\n";
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void portaudio_client::detach() {
  if (m_attached_device!=-1) {
    if (m_stream!=NULL) {
      Pa_CloseStream(m_stream);
    }
    m_stream=NULL;    
    m_status+="detaching from portaudio\n";
    Pa_Terminate();
    m_attached_device=-1;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

int portaudio_client::process(const void *input_buffer, void *output_buffer,
			      unsigned long frames_per_buffer,
			      const PaStreamCallbackTimeInfo* time_info,
			      PaStreamCallbackFlags status_flags,
			      void *user_data) {
  m_buffer_size=frames_per_buffer;

  if(run_callback&&run_context) {
    // do the work
    run_callback(run_context, frames_per_buffer);
  }

  if (m_right_data && m_left_data) {
    float *out = (float*)output_buffer;
    for (unsigned int n=0; n<m_buffer_size; n++) {
      *out=m_left_data[n];
      out++;
      *out=m_right_data[n];
      out++;
    }
  }

  if (input_buffer && m_right_in_data && m_left_in_data) {  
    float *in = (float*)input_buffer;
    for (unsigned int n=0; n<m_buffer_size; n++) {
      m_left_in_data[n]=*in;
      in++;
      m_right_in_data[n]=*in;
      in++;
    }
  }

  return 0;
}
