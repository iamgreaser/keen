// Keen Dreams Source Code - SDL port
// Copyright (C) 2014 Javier M. Chavez
// Copyright (C) 2014 Ben Russell
//
// This program is free software// you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation// either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY// without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program// if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "id_heads.h"

unsigned bufferwidth;
unsigned bufferheight;
uint8_t vga_emu_mem[256<<10];

void VW_MaskBlock(memptr segm,unsigned ofs,unsigned dest,
	unsigned wide,unsigned height,unsigned planesize)
{
	// TODO (this could do with some SERIOUS research)
}

void VW_MemToScreen(memptr source,unsigned dest,unsigned width,unsigned height)
{
	// TODO
	uint8_t *src = (uint8_t *)source;

	printf("\nmem2scr %p %04X %i %i\n", source, dest, width, height);
	//if(width == 0) abort();
	//

}

void VW_ScreenToMem(unsigned source,memptr dest,unsigned width,unsigned height)
{
	// TODO
}

void VW_ScreenToScreen(unsigned source,unsigned dest,unsigned width,unsigned height)
{
	// TODO
}

void VW_SetScreen (unsigned CRTC, unsigned pelpan)
{
	// TODO: factor out HW-specific crap such as this VGA CRTC setting code
}

void VW_Plot(unsigned x, unsigned y, unsigned color)
{
	// WARNING: Relies on x, y being unsigned!
	if(x >= VIRTUALWIDTH || y >= VIRTUALHEIGHT)
		return;

	vga_emu_mem[ylookup[y]+x] = color;
}

void VW_Hlin(unsigned xl, unsigned xh, unsigned y, unsigned color)
{
	unsigned x;

	for(x = xl; x <= xh; x++)
		VW_Plot(x, y, color);
}

void VW_Vlin(unsigned yl, unsigned yh, unsigned x, unsigned color)
{
	unsigned y;

	for(y = yl; y <= yh; y++)
		VW_Plot(x, y, color);
}

void VW_Bar (unsigned x, unsigned y, unsigned width, unsigned height, unsigned color)
{
	unsigned by;

	for(by = 0; by < height; by++)
		VW_Hlin(x, x+width-1, y + by, color);
}

void VW_DrawTile8(unsigned x, unsigned y, unsigned tile)
{
	// TODO!
}

void VW_DrawPropString (char far *string)
{
	// TODO!
}

