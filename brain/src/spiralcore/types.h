// Copyright (C) 2011 Dave Griffiths
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

#include "fixed.h"
//#include "ac_config.h"

#ifndef FLX_TYPES
#define FLX_TYPES

#include <math.h>

// autoconf can tell us if we are on Pi
// only support Pi and linux for the moment
#ifdef HAVE_LIBBCM_HOST
#define FLX_RPI
#endif

#ifndef FLX_RPI
#define FLX_LINUX
#endif

#ifndef _EE
typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long int u64;
typedef long long int s64;
typedef float f32;
typedef spiralcore::Fixed x32;
#endif

// get namespace bb everywhere, for differentiating from
// std::list where both are needed :/
//#include "list.h"
//using namespace bb;

typedef f32 audio_type;

#ifdef FLX_LINUX
//-Linux/RPI---------------------------
// use the fixed point version here
//#define flx_real x32
#define flx_real float

#else
#ifdef _EE
//-PS2----------------------------------
#define flx_real float
#define sqrt sqrtf
#define isascii( c ) (!((c) & 0x80))

#else
//-Android------------------------------
#define flx_real x32
#endif
#endif

#endif // FLX_TYPES
