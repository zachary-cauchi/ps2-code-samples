EE_LIBS += -Xlinker --start-group $(EE_LIBS_EXTRA)

ifneq ($(jpeg),)
LIBJPEG = $(PORTS)/libjpeg
endif

ifneq ($(tiff),)
LIBJPEG = $(PORTS)/libjpeg
LIBTIFF = $(PORTS)/libtiff
endif

ifneq ($(zlib),)
ZLIB = $(PORTS)/zlib
endif

ifneq ($(png),)
ZLIB = $(PORTS)/zlib
LIBPNG = $(PORTS)/libpng
endif

ifdef LIBJPEG
	EE_INCS += -I$(LIBJPEG)/include
	EE_CFLAGS += -DHAVE_LIBJPEG
	EE_LIB_DIRS += -L$(LIBJPEG)/lib
	EE_LIBS += -ljpeg -lfileXio -ldebug
endif

ifdef LIBTIFF
        EE_INCS += -I$(LIBTIFF)/include
        EE_CFLAGS += -DHAVE_LIBTIFF
        EE_LIB_DIRS += -L$(LIBTIFF)/lib
        EE_LIBS += -ltiff
endif

ifdef LIBPNG
ifdef ZLIB
	EE_INCS += -I$(ZLIB) -I$(LIBPNG)
	EE_CFLAGS += -DHAVE_LIBPNG -DHAVE_ZLIB
	EE_LIB_DIRS += -L$(ZLIB)/build -L$(LIBPNG)/build
	EE_LIBS += -lzlib -lpng
endif
endif

EE_LIBS += -lgskit_toolkit -lgskit -ldmakit -Xlinker --end-group

# include dir
EE_INCS += -I$(GSKIT)/ee/gs/include -I$(GSKIT)/ee/dma/include
EE_INCS += -I$(GSKIT)/ee/toolkit/include

# linker flags
EE_LIB_DIRS += -L$(GSKIT)/lib
EE_LIB_DIRS += -L$(PS2SDK)/ee/lib
EE_LDFLAGS += $(EE_LIB_DIRS)

all: $(EE_BIN)

include $(MAKERS)/sharedDefs.make
include $(MAKERS)/compileRules.make
