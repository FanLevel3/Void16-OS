ENTRY(loader)
SECTIONS {
	. = 1M;
	.text : { *(multiboot) *(.text) }
	.data : { *(.data) }
	.bss : { *(.bss) }
}
