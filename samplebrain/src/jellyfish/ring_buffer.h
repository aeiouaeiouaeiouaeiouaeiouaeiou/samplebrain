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

// ringbuffer for processing commands between asycronous threads, either may be
// realtime and non blocking, so all code should be realtime capable

#ifndef RING_BUFFER
#define RING_BUFFER

class ring_buffer
{
public:
	ring_buffer(unsigned int size);
	~ring_buffer();

	//bool lock();
	//bool unlock();
	bool write(char *src, unsigned int size);
	bool read(char *dest, unsigned int size);
	void dump();

private:
	unsigned int write_space();
	unsigned int read_space();

	unsigned int m_read_pos;
	unsigned int m_write_pos;
	unsigned int m_size;
	unsigned int m_size_mask;
	char *m_buffer;
};

#endif
