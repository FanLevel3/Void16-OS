ENTRY(_start)
SECTIONS {
    . = 0x2000;
    .text : {
        build/kernel_entry.o(.text)
        *(.text.kmainn)
        *(.text)
    }
}
