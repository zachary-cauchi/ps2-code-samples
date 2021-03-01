# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2005, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.

EE_BIN = playwav2.elf
EE_OBJS = playwav2.o
EE_LIBS = -laudsrv -lc
ISO = playwav2.iso
RES_FILES = song_22k.wav

all: $(EE_BIN) audsrv.irx
	genisoimage -o $(ISO) -V PLAYWAV2 -R -J $(EE_BIN) $(RES_FILES)

audsrv.irx:
	cp $(PS2SDK)/iop/irx/audsrv.irx $@

clean:
	rm -f $(EE_BIN) $(EE_OBJS) audsrv.irx playwav2.iso

run: $(EE_BIN)
	ps2client execee host:$(EE_BIN)

reset:
	ps2client reset

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
