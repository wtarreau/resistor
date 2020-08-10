TOPDIR     := $(PWD)
DESTDIR    :=
PREFIX     := /usr/local
LIBDIR     := $(PREFIX)/lib

CROSS_COMPILE :=

CC         := $(CROSS_COMPILE)gcc
OPT_CFLAGS := -O2
CPU_CFLAGS := -fomit-frame-pointer
DEB_CFLAGS := -Wall -g
DEF_CFLAGS :=
USR_CFLAGS :=
INC_CFLAGS :=
THR_CFLAGS :=
CFLAGS     := $(OPT_CFLAGS) $(CPU_CFLAGS) $(DEB_CFLAGS) $(DEF_CFLAGS) $(USR_CFLAGS) $(INC_CFLAGS) $(THR_CFLAGS)

LD         := $(CC)
DEB_LFLAGS := -g
USR_LFLAGS :=
LIB_LFLAGS := -lm
THR_LFLAGS :=
LDFLAGS    := $(DEB_LFLAGS) $(USR_LFLAGS) $(LIB_LFLAGS) $(THR_LFLAGS)

AR         := $(CROSS_COMPILE)ar
STRIP      := $(CROSS_COMPILE)strip
INSTALL    := install
BINS       := src/resistor
OBJS       :=
OBJS       += $(patsubst %.c,%.o,$(wildcard src/*.c))
OBJS       += $(patsubst %.S,%.o,$(wildcard src/*.S))

all: static shared tools

static: $(STATIC)

shared: $(SHARED)

tools: $(BINS)

%: %.o
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

install: install-tools

install-tools: tools
	$(STRIP) $(BINS)
	[ -d "$(DESTDIR)$(PREFIX)/bin/." ] || mkdir -p -m 0755 $(DESTDIR)$(PREFIX)/bin
	$(INSTALL) -m 0755 -t $(DESTDIR)$(PREFIX)/bin $(BINS)

clean:
	-rm -f $(BINS) $(OBJS) *.o *~
