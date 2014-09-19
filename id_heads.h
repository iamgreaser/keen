/* Keen Dreams Source Code
 * Copyright (C) 2014 Javier M. Chavez
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

// ID_GLOB.H


//include <alloc.h>
#include <ctype.h>
//include <dos.h>
#include <errno.h>
#include <fcntl.h>
//include <io.h>
//include <mem.h>
//include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

// work around a few DOS-isms
#define _seg
#define far
#define huge
#define O_BINARY 0
#define interrupt
#define EINVFMT 120

// a few more DOSisms
#define MK_FP(seg,ofs) ((void *)((((long)(seg))<<4)+(ofs)))
#define FP_SEG(v) 0
#define FP_OFF(v) (long)v

// yet more DOSisms, actually these are IBM BIOSisms now
#define inportb(a) 0
#define outportb(a, v)
#define __ID_GLOB__

// now for some MS-isms
#define stricmp strcasecmp

#define	EXTENSION	"kdr"

#include "graphkdr.h"
#include "audiokdr.h"

#define	TEXTGR	0
#define	CGAGR	1
#define	EGAGR	2
#define	VGAGR	3

#define GRMODE	VGAGR

#if GRMODE == VGAGR
#define GREXT	"VGA"
#endif
#if GRMODE == EGAGR
#define GREXT	"EGA"
#endif
#if GRMODE == CGAGR
#define GREXT	"CGA"
#endif

//#define PROFILE

//
//	ID Engine
//	Types.h - Generic types, #defines, etc.
//	v1.0d1
//

#ifndef	__TYPES__
#define	__TYPES__

typedef	enum	{false,true}	boolean;
typedef	unsigned	char		byte;
typedef	unsigned	int			word;
typedef	unsigned	long		longword;
typedef	byte *					Ptr;

typedef	struct
		{
			int	x,y;
		} Point;
typedef	struct
		{
			Point	ul,lr;
		} Rect;

#define	nil	((void *)0)

#endif

// extra functions not really in a proper place right now
// mostly for compat
int filelength(int handle);

#include "id_mm.h"
#include "id_ca.h"
#include "id_vw.h"
#include "id_rf.h"
#include "id_in.h"
#include "id_sd.h"
#include "id_us.h"



