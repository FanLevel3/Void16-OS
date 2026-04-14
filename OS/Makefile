CC = i686-linux-gnu-gcc
AS = nasm
LD = i686-linux-gnu-ld

CFLAGS = -m32 -ffreestanding -O2 -Wall -Isrc/kernel
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

OBJ = build/loader.o build/kernel.o build/screen.o build/keyboard.o
TARGET = build/Void16OS.bin

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJ)

build/loader.o: src/boot/loader.s
	@mkdir -p build
	$(AS) $(ASFLAGS) src/boot/loader.s -o build/loader.o

build/kernel.o: src/kernel/kernel.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c src/kernel/kernel.c -o build/kernel.o

build/screen.o: src/drivers/screen.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c src/drivers/screen.c -o build/screen.o

build/keyboard.o: src/drivers/keyboard.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c src/drivers/keyboard.c -o build/keyboard.o

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)

clean:
	rm -rf build/*.o build/*.bin
