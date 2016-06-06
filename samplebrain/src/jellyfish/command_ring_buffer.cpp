// copyright (C) 2004 david griffiths <dave@pawfal.org>
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

#include "command_ring_buffer.h"
#include <string.h>
#include <iostream>

using namespace std;

command_ring_buffer::command::command(const char *name, const char *types, const char *data, unsigned int datasize)
{
	strcpy(m_name,name);
	strcpy(m_types,types);
	// already checking datasize fits in OSCserver.cpp
    memcpy(m_data,data,datasize);

	m_num_args=strlen(types);

	// figure out the offsets into the data to use later
	int pos=0;
	for(unsigned int i=0; i<m_num_args; i++)
	{
		m_offsets[i]=pos;
		switch(types[i])
		{
			case 'i': pos+=4; break;
			case 'f': pos+=4; break;
			case 's': pos+=strlen(m_data+pos)+1; break;
			case 'b': pos+=sizeof(char*); break;

			default:
				// invalidate the command
				for(unsigned int n=0; n<strlen(types); n++) m_offsets[n]=-1;
				cerr<<"command_ring_buffer::command::command: erk! unknown type: "<<types[i]<<endl;
				return;
			break;
		}
	}
}

int command_ring_buffer::command::get_int(unsigned int index)
{
	if (m_offsets[index]!=-1 && m_types[index]=='i') return *((int*)(m_data+m_offsets[index]));
	return 0;
}

float command_ring_buffer::command::get_float(unsigned int index)
{
	if (m_offsets[index]!=-1 && m_types[index]=='f') return *((float*)(m_data+m_offsets[index]));
	return 0;
}

char *command_ring_buffer::command::get_string(unsigned int index)
{
	if (m_offsets[index]!=-1 && m_types[index]=='s') return ((char*)(m_data+m_offsets[index]));
	return 0;
}

////////////////////////////////////////////////////////////////

command_ring_buffer::command_ring_buffer(unsigned int size):
ring_buffer(size)
{
}

command_ring_buffer::~command_ring_buffer()
{
}

bool command_ring_buffer::send(const command& command)
{
	return write((char*)&command,sizeof(command));
}

bool command_ring_buffer::get(command& command)
{
	return read((char*)&command, sizeof(command));
}
