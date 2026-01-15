# Makefile for Kara OS
CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -m elf_i386 -T linker.ld
ASFLAGS = -f elf32

OBJS = bin/boot.o bin/kernel.o bin/keyboard.o

# The primary binary name
KARA_BIN = bin/kara.bin

all: bin_dir $(KARA_BIN) run

bin_dir:
	mkdir -p bin

bin/boot.o: src/boot.s
	$(AS) $(ASFLAGS) src/boot.s -o bin/boot.o

bin/kernel.o: src/kernel.c
	$(CC) $(CFLAGS) src/kernel.c -o bin/kernel.o

bin/keyboard.o: src/keyboard.c
	$(CC) $(CFLAGS) src/keyboard.c -o bin/keyboard.o

$(KARA_BIN): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(KARA_BIN)

run: $(KARA_BIN)
	qemu-system-i386 -kernel $(KARA_BIN)

clean:
	rm -rf bin/*.o $(KARA_BIN)
