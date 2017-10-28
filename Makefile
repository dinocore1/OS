.PHONY: all clean run

CC := gcc
CFLAGS := -m32 -Iinclude

all: kernel.bin

clean:
	rm -f kernel.bin *.o

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

OBJ := \
	boot.o \
	kernel.o \
	string.o \
	drivers/screen.o

kernel.bin: $(OBJ)
	ld -m elf_i386 -T link.ld -o kernel.bin  $(OBJ)

%.o : %.asm
	nasm -felf32 -o $@ $<

%.o : %.c
	$(CC) -c $< $(CFLAGS) -o $@
