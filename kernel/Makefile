#
# kernel
#

GCC ?= gcc
CFLAGS ?= -ffreestanding -O2 -m32 -g -Wall -Wextra -fno-builtin -fno-stack-protector 
INCLUDE ?= -I../include

#LD = ld
#LDFLAGS = -Ttext 0x1000 --oformat binary -m elf_i386 -nostdlib 
# LDFLAGS = -m elf_i386 -nostdlib

AS = nasm
ASFLAGS = -f elf32 -g

SRCS := kernel.c trap.c pic.c idt.c printk.c vsprintf.c

OBJS = $(SRCS:.c=.o) traps.o

DEPS = $(OBJS:.o=.d)

all: $(OBJS)

-include $(DEPS)

%.o: %.c
	$(GCC) $(INCLUDE) $(CFLAGS) -MMD -c $< -o $@	

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

.PHONY: all clean

clean:
	$(RM) *.o *.d .*swp $(MAIN)
