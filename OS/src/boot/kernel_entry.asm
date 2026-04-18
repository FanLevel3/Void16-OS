[bits 32]
section .text.kmain
global _start
[extern kmain]

_start:
    call kmain
    jmp $     
