
CC:=
TOPDIR:=
OBJDIR:=

SRCS=$(wildcard *.cxx)

CFLAGS:=


SEP:=


all:
	@echo "$(SEP)"
	@$(foreach file, $(SRCS), echo "$(CC): $(file)";)
	@echo "$(SEP)"
	@$(CC) -c $(SRCS) $(CFLAGS) 
	@mv *.o $(OBJDIR)/




.PHONE: clean



clean:
	rm -rf *.o
	rm -rf *.gch
