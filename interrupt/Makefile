#
# interrupt
#

CC = gcc
CFLAGS = -ffreestanding -m32  -g -O -fomit-frame-pointer -nostdinc \
		 -fno-stack-protector -W -Wall
INCLUDE = -I../include

AS = nasm
ASFLAGS = -f elf32 -g 

SRCS = idt.c

OBJS = $(SRCS:.c=.o) interrupts.o

all: $(OBJS)
	@echo compile finished

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	$(RM) *.o .*.swp
