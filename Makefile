.PHONY: all run


all: kernel.bin

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

kasm.o: kernel.asm
	nasm -f elf32 kernel.asm -o kasm.o

kc.o: kernel.c
	gcc -m32 -c kernel.c -o kc.o

kernel.bin: kasm.o kc.o
	ld -m elf_i386 -T link.ld -o kernel.bin kasm.o kc.o
