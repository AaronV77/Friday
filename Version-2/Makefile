SOURCES  = $(shell find cpu drivers include kernel libc -name '*.c')
KERN_ASM = $(shell find cpu drivers include kernel libc -name '*.asm')
HEADERS  = $(shell find cpu drivers include kernel libc -name '*.h')
OBJ      = ${SOURCES:.c=.o} ${KERN_ASM:.asm=.o}

ASM = nasm
CC = gcc
LD = ld -m elf_i386
OBJCOPY = objcopy

CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32 -std=c11 -fno-pic \
         -fno-asynchronous-unwind-tables

ifeq ($(shell uname -s),Darwin)
    CC = i386-elf-gcc
    LD = i386-elf-ld
    OBJCOPY = i386-elf-objcopy
endif

all: os-image.bin

run: all
	qemu-system-i386 os-image.bin

clean:
	rm -rf *.dis *.o *.elf
	rm -rf *.bin os-image.bin boot/*.bin kernel/*.bin
	rm -rf boot/*.o cpu/*.o drivers/*.o kernel/*.o libc/*.o

# Make a 1.44MiB disk image. Can work for HDA and FDA booting
os-image.bin: kernel/kernel.bin boot/boot.bin
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(word 2,$^) of=$@ conv=notrunc

boot/boot.bin: boot/boot.asm
	${ASM} $< -f bin -o $@

kernel/kernel.bin: kernel/kernel.elf
	${OBJCOPY} -O binary $^ $@

kernel/kernel.elf: ${OBJ}
	${LD} -o $@ -Tlinker.ld $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	${ASM} $< -f elf -o $@

%.bin: %.asm
	${ASM} $< -f bin -o $@