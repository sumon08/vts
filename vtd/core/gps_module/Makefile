
CC:=
TOPDIR:=
OBJDIR:=

SRCS=$(wildcard *.cxx)

CFLAGS:=

SEP:=

all:
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
