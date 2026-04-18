[org 0x7c00]
    jmp start
    nop

KERNEL_OFFSET equ 0x2000

start:
    mov [BOOT_DRIVE], dl

    mov bp, 0x9000
    mov sp, bp

    call load_kernel
    call switch_to_pm
    jmp $

print_string:
    pusha
.loop:
    mov al, [bx]
    cmp al, 0
    je .done
    mov ah, 0x0e
    int 0x10
    add bx, 1
    jmp .loop
.done:
    popa
    ret

[bits 16]
load_kernel:
    xor ax, ax
    mov es, ax
    mov bx, KERNEL_OFFSET
    mov dh, 45
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    call KERNEL_OFFSET
    jmp $

%include "src/boot/disk.asm"
%include "src/boot/gdt.asm"
%include "src/boot/switch_to_pm.asm"

BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xaa55
