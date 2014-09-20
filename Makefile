BINNAME_VGA = kdreams_vga
BINNAME_EGA = kdreams_ega
BINNAME_CGA = kdreams_cga

OBJDIR_CGA_C = build_cga_c
OBJDIR_CGA_A = build_cga_a
OBJDIR_EGA_C = build_ega_c
OBJDIR_EGA_A = build_ega_a
OBJDIR_VGA_C = build_vga_c
SRCDIR = .

CFLAGS = -g -Wall -Wextra -Wno-pointer-sign -Wno-unused-variable -Wno-unused-parameter -Wno-unknown-pragmas -Wno-unused-label -Wno-missing-braces -Wno-missing-field-initializers `sdl-config --cflags`
LDFLAGS = -g `sdl-config --libs`

INCLUDES = \
	audiokdr.h \
	gelib.h \
	graphkdr.h \
	id_ca.h \
	id_heads.h \
	id_in.h \
	id_mm.h \
	id_rf.h \
	id_sd.h \
	id_us.h \
	id_vw.h \
	jam_io.h \
	kd_def.h \
	lzhuff.h \
	lzw.h \
	sl_file.h \
	soft.h \
	#

OBJS_VGA_C = \
	$(OBJDIR_VGA_C)/gelib.o \
	$(OBJDIR_VGA_C)/id_ca.o \
	$(OBJDIR_VGA_C)/id_in.o \
	$(OBJDIR_VGA_C)/id_mm.o \
	$(OBJDIR_VGA_C)/id_rf.o \
	$(OBJDIR_VGA_C)/id_sd.o \
	$(OBJDIR_VGA_C)/id_us.o \
	$(OBJDIR_VGA_C)/id_vw.o \
	$(OBJDIR_VGA_C)/jam_io.o \
	$(OBJDIR_VGA_C)/kd_act1.o \
	$(OBJDIR_VGA_C)/kd_act2.o \
	$(OBJDIR_VGA_C)/kd_demo.o \
	$(OBJDIR_VGA_C)/kd_keen.o \
	$(OBJDIR_VGA_C)/kd_main.o \
	$(OBJDIR_VGA_C)/kd_play.o \
	$(OBJDIR_VGA_C)/lzhuf.o \
	$(OBJDIR_VGA_C)/soft.o \
	\
	$(OBJDIR_VGA_C)/id_rf_a.o \
	$(OBJDIR_VGA_C)/id_us_a.o \
	$(OBJDIR_VGA_C)/id_vw_a.o \
	$(OBJDIR_VGA_C)/id_vw_av.o \
	#

OBJS_EGA_AX = \
	$(OBJDIR_EGA_A)/id_rf_a.o \
	$(OBJDIR_EGA_A)/id_us_a.o \
	$(OBJDIR_EGA_A)/id_vw_a.o \
	#

OBJS_EGA_AE = \
	$(OBJDIR_EGA_A)/id_vw_ae.o \
	#

OBJS_CGA_AC = \
	$(OBJDIR_CGA_A)/id_vw_ac.o \
	#

#OBJS_CGA = $(OBJS_CGA_C) $(OBJS_CGA_AX) $(OBJS_CGA_AC)
#OBJS_EGA = $(OBJS_EGA_C) $(OBJS_EGA_AX) $(OBJS_EGA_AE)
OBJS_VGA = $(OBJS_VGA_C)

all: $(BINNAME_VGA) $(TOOLS)

clean:
	rm -f $(OBJS_VGA)

$(OBJDIR_VGA_C):
	mkdir -p $(OBJDIR_VGA_C)

$(OBJDIR_VGA_A):
	mkdir -p $(OBJDIR_VGA_A)

$(BINNAME_VGA): $(OBJDIR_VGA_C) $(OBJS_VGA)
	$(CC) -o $(BINNAME_VGA) $(OBJS_VGA) $(LIBS) $(LDFLAGS)

$(OBJDIR_VGA_C)/%.o: $(SRCDIR)/%.c $(INCLUDES)
	$(CC) -c -o $@ $(CFLAGS) $<

