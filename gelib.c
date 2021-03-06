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

#include "kd_def.h"

#define BIO_BUFFER_LEN	(512)



////////////////////////////////////////////////////////////////////////////
//
// FreeShape()
//
void FreeShape(struct Shape *shape)
{
	if (shape->Data)
		MM_FreePtr(&shape->Data);
}

////////////////////////////////////////////////////////////////////////////
//
// UnpackEGAShapeToScreen()
//
int UnpackEGAShapeToScreen(struct Shape *SHP,int startx,int starty)
{
#if GRMODE == VGAGR
	int currenty;
	signed char n, Rep, *Src, *Dst, loop, Plane;
	uint16_t BPR, Height;
	int NotWordAligned;
	int j;

	NotWordAligned = SHP->BPR & 1;
	startx>>=3;
	Src = SHP->Data;
	currenty = starty;
	Plane = 0;
	Height = SHP->bmHdr.h;

	while (Height--)
	{
		extern uint8_t vga_emu_mem[];
		for (Plane=0; Plane<SHP->bmHdr.d; Plane++)
		{
			Dst = vga_emu_mem;
			Dst += ylookup[currenty];
			Dst += startx*8;
			//printf("dst %i\n", Dst - (signed char *)vga_emu_mem);

			//outport(0x3c4,((1<<Plane)<<8)|2);

			BPR = ((SHP->BPR+1) >> 1) << 1;               // IGNORE WORD ALIGN
			while (BPR)
			{
				if (SHP->bmHdr.comp)
					n = *(Src++);
				else
					n = BPR-1;

				if (n < 0)
				{
					if (n != -128)
					{
						n = (-n)+1;
						BPR -= n;
						Rep = *(Src++);
						if ((!BPR) && (NotWordAligned))   // IGNORE WORD ALIGN
							n--;

						while (n--)
							for(j = 0; j < 8; j++)
							{
								if((Rep & (128>>j)) == 0)
									*Dst &= ~(1<<Plane);
								else
									*Dst |= (1<<Plane);
								Dst++;
							}
					}
					else
						BPR--;
				}
				else
				{
					n++;
					BPR -= n;
					if ((!BPR) && (NotWordAligned))     // IGNORE WORD ALIGN
						n--;

					while (n--)
					{
						for(j = 0; j < 8; j++)
						{
							if((*Src & (128>>j)) == 0)
								*Dst &= ~(1<<Plane);
							else
								*Dst |= (1<<Plane);
							Dst++;
						}
						Src++;
					}

					if ((!BPR) && (NotWordAligned))     // IGNORE WORD ALIGN
						Src++;
				}
			}
		}
		currenty++;
	}
#endif

#if GRMODE == EGAGR
	int currenty;
	signed char n, Rep, *Src, *Dst[8], loop, Plane;
	unsigned int BPR, Height;
	int NotWordAligned;

	NotWordAligned = SHP->BPR & 1;
	startx>>=3;
	Src = SHP->Data;
	currenty = starty;
	Plane = 0;
	Height = SHP->bmHdr.h;

	while (Height--)
	{
		//Dst[0] = (MK_FP(0xA000,displayofs));
		extern uint8_t vga_emu_mem[];
		Dst[0] = vga_emu_mem;
		Dst[0] += ylookup[currenty];
		Dst[0] += startx;
		for (loop=1; loop<SHP->bmHdr.d; loop++)
			Dst[loop] = Dst[0];

		for (Plane=0; Plane<SHP->bmHdr.d; Plane++)
		{
			//outport(0x3c4,((1<<Plane)<<8)|2);

			BPR = ((SHP->BPR+1) >> 1) << 1;               // IGNORE WORD ALIGN
			while (BPR)
			{
				if (SHP->bmHdr.comp)
					n = *Src++;
				else
					n = BPR-1;

				if (n < 0)
				{
					if (n != -128)
					{
						n = (-n)+1;
						BPR -= n;
						Rep = *Src++;
						if ((!BPR) && (NotWordAligned))   // IGNORE WORD ALIGN
							n--;

						while (n--)
							*Dst[Plane]++ = Rep;
					}
					else
						BPR--;
				}
				else
				{
					n++;
					BPR -= n;
					if ((!BPR) && (NotWordAligned))     // IGNORE WORD ALIGN
						n--;

					while (n--)
						*Dst[Plane]++ = *Src++;

					if ((!BPR) && (NotWordAligned))     // IGNORE WORD ALIGN
						Src++;
				}
			}
		}
		currenty++;
	}
#endif

	return(0);
}

////////////////////////////////////////////////////////////////////////////
//
// Verify()
//
long Verify(char *filename)
{
	int handle;
	long size;

	if ((handle=open(filename,O_BINARY))==-1)
		return (0);
	size=filelength(handle);
	close(handle);
	return(size);
}

//--------------------------------------------------------------------------
// InitBufferedIO()
//--------------------------------------------------------------------------
memptr InitBufferedIO(int handle, BufferedIO *bio)
{
	bio->handle = handle;
	bio->offset = BIO_BUFFER_LEN;
	bio->status = 0;
	MM_GetPtr(&bio->buffer,BIO_BUFFER_LEN);

	return(bio->buffer);
}

//--------------------------------------------------------------------------
// FreeBufferedIO()
//--------------------------------------------------------------------------
void FreeBufferedIO(BufferedIO *bio)
{
	if (bio->buffer)
		MM_FreePtr(&bio->buffer);
}

//--------------------------------------------------------------------------
// bio_readch()
//--------------------------------------------------------------------------
byte bio_readch(BufferedIO *bio)
{
	byte *buffer;

	if (bio->offset == BIO_BUFFER_LEN)
	{
		bio->offset = 0;
		bio_fillbuffer(bio);
	}

	buffer = bio->buffer + (bio->offset++);

	return(*buffer);
}

//--------------------------------------------------------------------------
// bio_fillbuffer()
//
// BUGS (Not really bugs... More like RULES!)
//
//    1) This code assumes BIO_BUFFER_LEN is no smaller than
//       NEAR_BUFFER_LEN!!
//
//    2) BufferedIO.status should be altered by this code to report
//       read errors, end of file, etc... If you know how big the file
//       is you're reading, determining EOF should be no problem.
//
//--------------------------------------------------------------------------
void bio_fillbuffer(BufferedIO *bio)
{
	#define NEAR_BUFFER_LEN	(64)
	byte near_buffer[NEAR_BUFFER_LEN];
	short bio_length,bytes_read,bytes_requested;

	bytes_read = 0;
	bio_length = BIO_BUFFER_LEN;
	while (bio_length)
	{
		if (bio_length > NEAR_BUFFER_LEN-1)
			bytes_requested = NEAR_BUFFER_LEN;
		else
			bytes_requested = bio_length;

		read(bio->handle,near_buffer,bytes_requested);
		//_fmemcpy(MK_FP(bio->buffer,bytes_read),near_buffer,bytes_requested);
		memcpy(bio->buffer + bytes_read, near_buffer, bytes_requested);

		bio_length -= bytes_requested;
		bytes_read += bytes_requested;
	}
}

///////////////////////////////////////////////////////////////////////////
//
// SwapLong()
//
void SwapLong(long *Var)
{
	// use an int pointer so we don't break 64-bit builds
	unsigned int *vv = (unsigned int *)Var;

	unsigned int h, l;
	h = ((*vv)>>16) & 0xFFFF;
	l = ((*vv)    ) & 0xFFFF;
	SwapWord((word *)&h);
	SwapWord((word *)&l);

	*vv = (l<<16) | h;
}

///////////////////////////////////////////////////////////////////////////
//
// SwapWord()
//
void SwapWord(unsigned int far *Var)
{
	// now use unsigned short
	unsigned short *vv = (unsigned short *)Var;

	word h, l;
	h = ((*vv)>>8) & 0xFF;
	l = ((*vv)   ) & 0xFF;
	*vv = (l<<8) | h;
}

////////////////////////////////////////////////////////////////////////////
//
// MoveGfxDst()
//
void MoveGfxDst(short x, short y)
{
	unsigned address;

	address = (y*linewidth)+(x/8);
	bufferofs = displayofs = address;
}

