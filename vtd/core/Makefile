

TOPDIR := ${shell pwd | sed -e 's/ /\\ /g'}


ARCHWARNINGS = -Wall  -Wundef
ARCHCFLAGS   = -fno-builtin -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
ARCHCXXFLAGS = -fno-builtin -fno-exceptions -fcheck-new -fno-rtti -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
ARCHOPTIMIZATION = -O0 -fno-strict-aliasing -fno-strength-reduce -fomit-frame-pointer -fno-exceptions -nostdlib -nostartfiles -nodefaultlibs -fno-rtti
ARCHINCLUDES = -I. -isystem  $(TOPDIR)/../Nuttx/nuttx-7.25/include
COREINCLUDES = -I$(TOPDIR) -I$(TOPDIR)/event -I$(TOPDIR)/protocol -I$(TOPDIR)/protocol/engine -I$(TOPDIR)/command -I$(TOPDIR)/message -I$(TOPDIR)/module -I$(TOPDIR)/../adapter -I$(TOPDIR)/source -I$(TOPDIR)/engine_module -I$(TOPDIR)/protocol/default 
COREINCLUDES += -I$(TOPDIR)/ac_module -I$(TOPDIR)/filter -I$(TOPDIR)/gps_module
CCSTD = -std=c++11

LIB =
LIBINCLUDES = -L$(TOPDIR)/nuttx-export/libs

OBJDIR=$(TOPDIR)/objdir

CFLAGS =  $(ARCHCFLAGS) $(ARCHCXXFLAGS) $(ARCHWARNINGS) $(ARCHOPTIMIZATION) $(ARCHINCLUDES) $(COREINCLUDES) $(CCSTD) -pipe


CROSSDEV = arm-none-eabi-
CC = $(CROSSDEV)g++
LD = $(CROSSDEV)ld
STRIP = $(CROSSDEV)strip --strip-unneeded
OBJCPY = $(CROSSDEV)objcopy
OBJDUMP = $(CROSSDEV)objdump
NM = $(CROSSDEV)nm

RELEASEDIR = vts_release

# Setup up linker command line options
LDRELFLAGS = -r

LDELFFLAGS = -T core.ld
#LDELFFLAGS += -T defines.ld

# This might change in a different environment
OBJEXT ?= .o

# This is the generated ELF program
BIN = vts.bin
REL = vts.r
HEX = vts.hex
RELOUT = test_relocatable.out
# These are the sources files that we use

SRCS = vts_main.cxx
OBJS = $(SRCS:.cxx=$(OBJEXT))

SEP = ==================================================================================================

# Build targets

all: config $(BIN)
.PHONY: menuconfig clean config distclean release release_clean

$(OBJS): %$(OBJEXT): %.cxx
#	@make -C source TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
#	@make -C startup TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@make -C event TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@make -C command TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@make -C module TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@make -C protocol TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@make -C engine_module TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@make -C ../adapter TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@make -C ac_module TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@make -C gps_module TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@$(CC) -c $(CFLAGS) $(CCSTD) -o $(OBJDIR)/$@ $<


$(BIN): $(OBJS)
	@make -C $(OBJDIR) link TOPDIR="$(TOPDIR)" LIB="$(LIB)" LIBINCLUDES="$(LIBINCLUDES)" SEP="$(SEP)"


clean:
	@make -C $(OBJDIR) clean SEP="$(SEP)"

menuconfig:
	@kconfig-mconf Kconfig

distclean:
	@rm -rf .config
	@rm -rf .config.*
	@rm -rf .oldconfig

config:
	@python3 mkconfig.py

release:
	@mkdir -p $(RELEASEDIR)
	@cp $(OBJDIR)/$(HEX) $(RELEASEDIR)/$(HEX)

release_clean:
	@rm -rf $(RELEASEDIR)
