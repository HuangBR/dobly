#
# interrupt
#

CC = gcc
#CFLAGS = -ffreestanding -m32  -g -O -fomit-frame-pointer -nostdinc \
		 -fno-stack-protector -W -Wall
INCLUDE = -I../include

AS = nasm
#ASFLAGS = -f elf32 -g 

SRCS = idt.c pic.c

OBJS = $(SRCS:.c=.o) 

all: $(OBJS)
	@echo compile finished

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

.PHONY: all clean

pic.c: ../mm/mm.h

clean:
	$(RM) *.o .*.swp
