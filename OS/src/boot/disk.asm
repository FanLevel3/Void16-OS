[bits 16]
disk_load:
    pusha
    push dx

    push ax
    xor ax, ax
    int 0x13
    pop ax

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    
    int 0x13
    jc disk_error

    pop dx
    cmp al, dh
    jne disk_error

    popa
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp disk_loop

disk_loop:
    jmp $

DISK_ERROR_MSG: db "Disk read error!", 0
