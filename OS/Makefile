C_SOURCES = $(wildcard src/kernel/*.c src/drivers/*.c)
HEADERS = $(wildcard src/kernel/*.h src/drivers/*.h)
OBJ = src/kernel/kernel.o src/kernel/util.o src/drivers/keyboard.o src/drivers/screen.o

CC = gcc
LD = ld
NASM = nasm

CFLAGS = -g -m32 -ffreestanding -Wall -Wextra -fno-exceptions -fno-stack-protector -fno-pic -Isrc/kernel -Isrc/drivers

build/Void16OS.img: build/boot.bin build/kernel.bin
	cat build/boot.bin build/kernel.bin > build/Void16OS.img
	truncate -s 1440k build/Void16OS.img

build/kernel.bin: build/kernel_entry.o ${OBJ}
	$(LD) -m elf_i386 -o $@ -Ttext 0x2000 $^ --oformat binary

build/kernel_entry.o: src/boot/kernel_entry.asm
	$(NASM) $< -f elf32 -o $@

build/boot.bin: src/boot/boot.asm
	$(NASM) $< -f bin -o $@

%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.bin build/*.o build/*.img src/kernel/*.o src/drivers/*.o

GENISO = genisoimage
QEMU = qemu-system-i386

iso: build/Void16OS.img
	@mkdir -p build/iso_root
	cp build/Void16OS.img build/iso_root/
	genisoimage -quiet -V "VOID16OS" \
		-b Void16OS.img \
		-c boot.catalog \
		-o build/Void16OS.iso build/iso_root

run: build/Void16OS.iso
	$(QEMU) -drive format=raw,file=build/Void16OS.img

run-img: build/Void16OS.img
	$(QEMU) -drive format=raw,file=build/Void16OS.img,if=floppy



