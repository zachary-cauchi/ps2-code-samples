EE_BIN  = filename.elf
EE_OBJS = filename.o

LIBGSKIT = $(GSKIT)/lib/libgskit.a
LIBDMAKIT = $(GSKIT)/lib/libdmakit.a
LIBGSKIT_TOOLKIT = $(GSKIT)/lib/libgskit_toolkit.a
# GSKIT_DEBUG = 1

include ../../../../makers/gskit.make
