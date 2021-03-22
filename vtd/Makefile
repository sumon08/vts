

TOPDIR := ${shell pwd | sed -e 's/ /\\ /g'}

.PHONY: board help build_clean

NUTTX_PATH = Nuttx/nuttx-7.25

HEXFILE = $(TOPDIR)/$(NUTTX_PATH)/nuttx.hex
SIZE = arm-none-eabi-size 

GREEN=\033[0;32m
NC=\033[0;0m
YELLOW=\033[1;33m
LIGHT_BLUE=\033[1;34m

all:
	@make -C $(NUTTX_PATH) all	
	@mv $(TOPDIR)/$(NUTTX_PATH)/nuttx $(TOPDIR)
	@if [ -f $(HEXFILE) ]; then	mv $(HEXFILE) $(TOPDIR); fi;
	@echo "SIZE: nuttx"
	@ $(SIZE) nuttx

clean: build_clean
	@make -C $(NUTTX_PATH) clean

distclean: build_clean
	@make -C $(NUTTX_PATH) distclean

menuconfig: 
	@make -C $(NUTTX_PATH) menuconfig

vts_config: 
	@make -C $(NUTTX_PATH) vts_config

board: 
	@./$(NUTTX_PATH)/tools/configure.sh vts-v2f401rc/vts

download:
	@make -C $(NUTTX_PATH) download

help:
	@echo ""
	@echo  "${GREEN}Board Selection: ${LIGHT_BLUE}First Configure the board by typing <make board> "
	@echo ""
	@echo "${GREEN}VTS Configuration: ${LIGHT_BLUE}Configure VTS app by typing <make vts_config> "
	@echo ""
	@echo "${GREEN}Nuttx Configuration: ${LIGHT_BLUE}Configure Nuttx by typing <make menuconfig> "
	@echo ""
	@echo "${GREEN}Build Project: ${LIGHT_BLUE}Compile and Build by typing <make>"
	@echo ""
	@echo "${GREEN}Clean Project: ${LIGHT_BLUE}Clear previous build by typing <make clean>"
	@echo ""
	@echo "${GREEN}Clean Configuration: ${LIGHT_BLUE}Clear previous configuration by typing <make distclean> "
	@echo "${NC}"


build_clean: 
	@rm -rf nuttx
	@rm -rf nuttx.hex