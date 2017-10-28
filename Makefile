.PHONY: all clean run


all: kernel.bin

clean:
	rm -f kernel.bin *.o

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

boot.o: boot.asm
	nasm -felf32 boot.asm -o boot.o

kc.o: kernel.c
	gcc -m32 -c kernel.c -o kc.o

kernel.bin: boot.o kc.o
	ld -m elf_i386 -T link.ld -o kernel.bin  kc.o boot.o
