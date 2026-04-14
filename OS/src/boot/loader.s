MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

section .multiboot
	align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text
extern kmain
global loader

loader:
	mov esp, kernel_stack + 4096
	call kmain
	hlt

section .bss
kernel_stack:
	resb 4096
