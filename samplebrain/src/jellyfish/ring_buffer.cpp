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

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include "ring_buffer.h"

using namespace std;

ring_buffer::ring_buffer(unsigned int size):
m_read_pos(0),
m_write_pos(0),
m_size(size),
m_size_mask(size-1),
m_buffer(NULL)
{
	m_buffer = new char[m_size];
	memset(m_buffer,'Z',m_size);
}

ring_buffer::~ring_buffer()	
{
	delete[] m_buffer;
}

bool ring_buffer::write(char *src, unsigned int size)
{
	//cerr<<"write pos: "<<m_write_pos<<endl;
	unsigned int space=write_space();

	if (space<size) 
    {
        cerr<<"ringbuffer ran out of space, needed: "<<size<<" have: "<<space<<endl;
        return false;
    }
	
	if (size<m_size-m_write_pos)
	{
		//cerr<<"written to: "<<m_write_pos<<endl;
		memcpy(&(m_buffer[m_write_pos]), src, size);
		m_write_pos += size;
		m_write_pos &= m_size_mask;
	}
	else // have to split data over boundary
	{
		unsigned int first = m_size-m_write_pos;
		unsigned int second = (m_write_pos+size) & m_size_mask;
		
		memcpy(&(m_buffer[m_write_pos]), src, first);
		m_write_pos += first;
		m_write_pos &= m_size_mask;
		
		memcpy(&(m_buffer[m_write_pos]), &src[first], second);
		m_write_pos += second;
		m_write_pos &= m_size_mask;
	}
	
	return true;
}

bool ring_buffer::read(char *dest, unsigned int size)
{
	//cerr<<"read pos: "<<m_read_pos<<endl;
	unsigned int space=read_space();
	if (space==0 || size>m_size) return false;
	
	if (size<m_size-m_read_pos)
	{
		//cerr<<"reading from: "<<m_read_pos<<endl;
		memcpy(dest, &(m_buffer[m_read_pos]), size);
		m_read_pos += size;
		m_read_pos &= m_size_mask;
	}
	else // have to split data over boundary
	{
		unsigned int first = m_size-m_read_pos;
		unsigned int second = (m_read_pos+size) & m_size_mask;
		
		memcpy(dest, &(m_buffer[m_read_pos]), first);
		m_read_pos += first;
		m_read_pos &= m_size_mask;
		
		memcpy(&dest[first], &(m_buffer[m_read_pos]), second);
		m_read_pos += second;
		m_read_pos &= m_size_mask;
	}
	
	return true;
}

void ring_buffer::dump()
{
	for (unsigned int i=0; i<m_size; i++) cerr<<m_buffer[i];
	cerr<<endl;
}

unsigned int ring_buffer::write_space()
{
	unsigned int read = m_read_pos;
	unsigned int write = m_write_pos;
	
	if (write > read) return (read - write + m_size) & (m_size_mask - 1);
	if (write < read) return (read - write) - 1;
	return m_size - 1;
}

unsigned int ring_buffer::read_space()
{
	unsigned int read = m_read_pos;
	unsigned int write = m_write_pos;

	if (write > read) return write - read;
	else return (write - read + m_size) & m_size_mask;
}
