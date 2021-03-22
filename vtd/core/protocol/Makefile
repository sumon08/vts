
CC:=
TOPDIR:=
OBJDIR:=

SRCS=$(wildcard *.cxx)

CFLAGS:=

SEP:=

all:
	@make -C engine TOPDIR="$(TOPDIR)"  OBJDIR="$(OBJDIR)"  CFLAGS="$(CFLAGS)" CROSSDEV="$(CROSSDEV)" CC="$(CC)" SEP="$(SEP)"
	@echo "$(SEP)"
	@$(foreach file, $(SRCS), echo "$(CC): $(file)";)
	@echo "$(SEP)";
ifneq ($(SRCS),)
	@$(CC) -c $(SRCS) $(CFLAGS)
	@mv *.o $(OBJDIR)/
else
	@echo "No file to compile. Skipping....."
endif





.PHONE: clean



clean:
	rm -rf *.o
	rm -rf *.gch
