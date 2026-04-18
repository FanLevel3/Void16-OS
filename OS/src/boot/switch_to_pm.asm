[bits 16]
switch_to_pm:
	cli ; close Interrupt
	lgdt [gdt_descriptor]

	mov eax, cr0 ; Read Control Register 0
	or eax, 0x1 ; First Bit to 1
	mov cr0, eax ; Write Back
	
	;Far Jump
	;Change CS
	jmp CODE_SEG:init_pm

[bits 32]
init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	;Stack Update
	mov ebp, 0x90000
	mov esp, ebp

	jmp BEGIN_PM ;Call Directly to Kernel
