// Copyright (C) 2004 David Griffiths <dave@pawfal.org>
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

#ifndef ALLOCATOR
#define ALLOCATOR

using namespace std;

class base_allocator
{
public:
	virtual ~base_allocator() {}
	virtual void reset() {}
	virtual char *anew(unsigned int size)=0;
	virtual void adelete(char *mem)=0;
};

///////////////////////////////////////////////////

class malloc_allocator : public base_allocator
{
public:
	malloc_allocator() {}
	virtual ~malloc_allocator() {}

	virtual char *anew(unsigned int size);
	virtual void adelete(char *mem);

protected:
};

/////////////////////////////////////////////////////

class realtime_allocator : public base_allocator
{
public:
	realtime_allocator(unsigned int size);
	virtual ~realtime_allocator() {}

	virtual void reset();
	virtual char *anew(unsigned int size);
	virtual void adelete(char *mem);

protected:

	char *m_buffer;
	unsigned int m_position;
	unsigned int m_size;
};

#endif
