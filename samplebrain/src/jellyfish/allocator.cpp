// Copyright (C) 2003 David Griffiths <dave@pawfal.org>
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

#include "allocator.h"

char *malloc_allocator::anew(unsigned int size)
{
	return new char[size];
}

void malloc_allocator::adelete(char *mem)
{
	delete[] mem;
}

///////////////////////////////////////////////////////////

realtime_allocator::realtime_allocator(unsigned int size) :
m_position(0),
m_size(size)
{
	m_buffer = new char[m_size];
}

void realtime_allocator::reset()
{
	m_position=0;
}

char *realtime_allocator::anew(unsigned int size)
{
	//cerr<<"new "<<size<<endl;
	char *ret = m_buffer+m_position;
	m_position+=size;


	if (m_position>m_size)
	{
//		cerr<<"out of realtime buffer mem, here we go!!! :("<<endl;
		m_position=0;
		ret = m_buffer;
	}

	return ret;
}

void realtime_allocator::adelete(char *mem)
{
	//cerr<<"delete"<<endl;
	// we don't need no stinking delete!
}
