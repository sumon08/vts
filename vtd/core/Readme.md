# Core Readme
VTS version 2 business logic codes are located here. Directories are based on features and modules.
Such as Event Management related codes are located in core/event, command manager related codes are located in core/command

# VTS main program
VTS starts from the main function in vts_main.cxx

# Compilation and Build
GNU make has been used to compile and link full vts

Compilation process start from call to core/Makefile

Each of the directories has its own Makefile and relevent rules.

All the object files are stored in core/objdir befor linking

Objdir has linker script core.ld and Makefile to link and generate final binary and hex file

