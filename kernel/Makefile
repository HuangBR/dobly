#
# kernel
#

GCC = gcc
CFLAGS = -ffreestanding -O2 -m32 -g -W -Wall -nostdinc -fno-builtin -fno-stack-protector -fomit-frame-pointer
INCLUDE = -I../include

LD = ld
LDFLAGS = -Ttext 0x1000 --oformat binary -m elf_i386 -nostdlib 
# LDFLAGS = -m elf_i386 -nostdlib

AS = nasm
ASFLAGS = -f bin -g

SRCS := kernel.c panic.c

OBJS = $(SRCS:.c=.o)

MAIN = kernel.bin

all: $(OBJS)

%.o: %.c
	$(GCC) $(INCLUDE) $(CFLAGS) -c $< -o $@	

.PHONY: all clean

clean:
	$(RM) *.o .*swp $(MAIN)
