SECTIONS
{
	.text.boot : { *(.text.boot) }
	.text : { *(.text) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	. = ALIGN(8);
	bss_begin = .;
	.bss (NOLOAD) : {
	*(.bss*)
	. = ALIGN(8);
	}
	bss_end = .;
}
