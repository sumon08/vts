
ARCHWARNINGS = -Wall  -Wshadow -Wundef
ARCHOPTIMIZATION = -Os -fno-strict-aliasing -fno-strength-reduce -fomit-frame-pointer -fno-exceptions -nostdlib
ARCHINCLUDES = -I. -isystem

CROSSDEV = arm-none-eabi-
CC = $(CROSSDEV)g++
LD = $(CROSSDEV)ld
AR = $(CROSSDEV)ar
STRIP = $(CROSSDEV)strip --strip-unneeded
OBJCPY = $(CROSSDEV)objcopy
OBJDUMP = $(CROSSDEV)objdump
NM = $(CROSSDEV)nm
TOPDIR?=

RELEASEDIR = vts_release

SEP:=

# Setup up linker command line options
LDRELFLAGS = -r
LIB:=
LIBINCLUDES:=
LDELFFLAGS = -T core.ld
#LDELFFLAGS += -T defines.ld

# This might change in a different environment
OBJEXT ?= .o

# This is the generated ELF program
ARCHIVE = libvts.a
BIN = vts.bin
REL = vts.r
HEX = vts.hex
RELOUT = test_relocatable.out

FILE = "$(wildcard *.o)" "$(wildcard *.hex)" "$(wildcard *.bin)" "$(wildcard *.r)"

all:
.PHONY: clean link

clean:
	@echo "$(SEP)"
	@echo "RM: $(FILE)" | fold -s -w 66
	@echo "$(SEP)"
	@rm -rf *.o
	@rm -rf *.hex
	@rm -rf *.bin
	@rm -rf *.r
	@rm -rf symbol_list.ld
	@echo "Object directory cleanup finished"

link:
#generate relocatable list and write to temporary file
	@echo "$(SEP)";
	@printf '%s\n' "$(AR): $(wildcard *.o)" | fold -s -w 66
	@echo "$(SEP)";
#	@$(LD) -r *.o -o $(REL)
#	@$(NM) $(REL) | grep 'U'> $(RELOUT)
#extract undefined symbols and find references from System.map
#	@python3 extract_symbols.py $(RELOUT) $(TOPDIR)/nuttx-export/System.map
#reomve relotable list temporary files
#	@rm -f $(RELOUT)
#	@rm -f $(REL)
#finally link application
	@rm -rf libvts.o
	@$(LD) -r -o libvts.r $(wildcard *.o)
	@$(AR) -r $(ARCHIVE) libvts.r
	@rm -rf libvts.o
	@echo "$(AR): $(ARCHIVE)"
	@echo "$(SEP)";
	@mv $(ARCHIVE) ../../Nuttx/nuttx-7.25/staging/
#@$(OBJCPY) -I elf32-littlearm  -O ihex $(BIN) $(HEX)

vts_main:
	$(CC) -c *.o -o vts.o
