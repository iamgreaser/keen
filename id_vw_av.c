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
uint8_t vga_emu_mem[VGA_RAM];

void VW_MaskBlock(memptr segm,unsigned ofs,unsigned dest,
	unsigned wide,unsigned height,unsigned planesize)
{
	// TODO (this could do with some SERIOUS research)
}

void VW_MemToScreen(memptr source,unsigned dest,unsigned width,unsigned height)
{
	int x, y, i;
	int s = 0;
	uint8_t *src[4];

	// Get plane sources
	for(i = 0; i < 4; i++)
		src[i] = (width*height)*i + (uint8_t *)source;

	for(y = 0; y < height; y++)
	for(x = 0; x < width; x++)
	{
		int pidx = (dest + x*8 + y*linewidth) & (VGA_RAM-1);
		int v0, v1, v2, v3;
		v0 = src[0][s];
		v1 = src[1][s]<<1;
		v2 = src[2][s]<<2;
		v3 = src[3][s]<<3;

		for(i = 0; i < 8; i++)
		{
			vga_emu_mem[pidx+7-i] = (v0&1)|(v1&2)|(v2&4)|(v3&8);
			v0 >>= 1;
			v1 >>= 1;
			v2 >>= 1;
			v3 >>= 1;
		}

		s++;
	}

	//if(width == 0) abort();
	//

}

void VW_ScreenToMem(unsigned source,memptr dest,unsigned width,unsigned height)
{
	// AAAAAAAAARGH
	int x, y, i, s;

	uint8_t *si = vga_emu_mem;
	uint8_t *di = (uint8_t *)dest;

	for(s = 0; s < 4; s++)
	for(y = 0; y < height; y++)
	for(x = 0; x < width; x++)
	{
		int v = 0;

		for(i = 0; i < 8; i++)
			if((si[(source + x*8 + i + y*linewidth) & (VGA_RAM-1)] & (1<<s)) != 0)
				v |= (0x80>>i);

		*(di++) = v;
	}
}

void VW_ScreenToScreen(unsigned source,unsigned dest,unsigned width,unsigned height)
{
	int x, y;
	for(y = 0; y < height; y++)
	for(x = 0; x < width*8; x++)
		vga_emu_mem[(dest + x + y*linewidth) & (VGA_RAM-1)]
		= vga_emu_mem[(source + x + y*linewidth) & (VGA_RAM-1)];

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

	vga_emu_mem[(ylookup[y]+x) & (VGA_RAM-1)] = color;
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

