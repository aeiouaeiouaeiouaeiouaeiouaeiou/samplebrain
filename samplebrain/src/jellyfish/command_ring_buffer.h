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

#include "ring_buffer.h"

#ifndef COMMAND_RING_BUFFER
#define COMMAND_RING_BUFFER

static const unsigned int COMMAND_DATA_SIZE = 128;

class command_ring_buffer : public ring_buffer
{
public:
	command_ring_buffer(unsigned int size);
	~command_ring_buffer();

	class command
	{
	public:
		command() {}
		command(const char *name, const char *types, const char *data, unsigned int datasize);
		~command() {}

		int get_int(unsigned int index);
		float get_float(unsigned int index);
		char *get_string(unsigned int index);
		// unlike the string - ownership of the blob is yours
		// you must delete it when you're done...
		char *get_blob(unsigned int index);
		unsigned int size() { return m_num_args; }
		char m_name[256];
		char m_types[64];

	private:
		char m_data[COMMAND_DATA_SIZE];
		int m_offsets[64];
		unsigned int m_num_args;

	};

	bool send(const command& command);
	bool get(command& command);

private:
	command m_current;
};

#endif
