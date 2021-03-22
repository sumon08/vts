


MEMORY
{
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 256K
    sram (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

OUTPUT_ARCH(arm)
ENTRY(_stext)
SECTIONS
{
	.text : {
		_stext = ABSOLUTE(.);
		*(.vectors)		
		*(.text .text.*)
		*(.fixup)
		*(.gnu.warning)
		*(.rodata .rodata.*)
		*(.gnu.linkonce.t.*)
		*(.glue_7)
		*(.glue_7t)
		*(.got)
		*(.gcc_except_table)
		*(.gnu.linkonce.r.*)
		_etext = ABSOLUTE(.);
	} > flash

	.registry : {		
		_scmd_registry = ABSOLUTE(.);
		KEEP(*(.cmd_registry))
		_ecmd_registry = ABSOLUTE(.);
		_sevent_registry = ABSOLUTE(.);
		KEEP(*(.event_registry))
		_eevent_registry = ABSOLUTE(.);
		. = ALIGN(8);
		_sparser_registry = ABSOLUTE(.);
		*(.parser_registry)
		_eparser_registry = ABSOLUTE(.);
		. = ALIGN(8);
		_srparser_registry = ABSOLUTE(.);
		*(.rparser_registry)
		_erparser_registry = ABSOLUTE(.);
	} > flash

	.init_section : {
		_sinit = ABSOLUTE(.);
		*(.init_array .init_array.*)
		_einit = ABSOLUTE(.);
	} > flash

	.ARM.extab : {
		*(.ARM.extab*)
	} > flash

	__exidx_start = ABSOLUTE(.);
	.ARM.exidx : {
		*(.ARM.exidx*)
	} > flash
	__exidx_end = ABSOLUTE(.);

	_eronly = ABSOLUTE(.);


	.data : {
		_sdata = ABSOLUTE(.);
		*(.data .data.*)
		*(.gnu.linkonce.d.*)
		CONSTRUCTORS
		_edata = ABSOLUTE(.);
	} > sram AT > flash

	.bss : {
		_sbss = ABSOLUTE(.);
		*(.bss .bss.*)
		*(.gnu.linkonce.b.*)
		*(COMMON)
		_ebss = ABSOLUTE(.);
	} > sram

	/* Stabs debugging sections. */
	.stab 0 : { *(.stab) }
	.stabstr 0 : { *(.stabstr) }
	.stab.excl 0 : { *(.stab.excl) }
	.stab.exclstr 0 : { *(.stab.exclstr) }
	.stab.index 0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment 0 : { *(.comment) }
	.debug_abbrev 0 : { *(.debug_abbrev) }
	.debug_info 0 : { *(.debug_info) }
	.debug_line 0 : { *(.debug_line) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_aranges 0 : { *(.debug_aranges) }
}
