SOURCES  = $(shell find cpu drivers include kernel libc -name '*.c')
KERN_ASM = $(shell find cpu drivers include kernel libc -name '*.asm')
HEADERS  = $(shell find cpu drivers include kernel libc -name '*.h')
OBJ	= ${SOURCES:.c=.o} ${KERN_ASM:.asm=.o}

ASM = nasm
CC = gcc 
LD = ld -m elf_i386
CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32 -std=c11 -fno-pie

ifeq ($(shell uname -s),Darwin)
	CC = i386-elf-gcc
	LD = i386-elf-ld
endif

all: os-image.bin

run: all
	qemu-system-i386 os-image.bin

clean:
	rm -rf *.dis *.o *.elf
	rm -rf kernel/*.elf	
	rm -rf *.bin os-image.bin boot/*.bin kernel/*.bin
	rm -rf boot/*.o cpu/*.o drivers/*.o kernel/*.o libc/*.o

os-image.bin: boot/boot.bin kernel/kernel.bin
	cat $^ > os-image.bin

boot/boot.bin: boot/boot.asm
	${ASM} $< -f bin -o $@

kernel/kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	${ASM} $< -f elf -o $@

%.bin: %.asm
	${ASM} $< -f bin -o $@
