#
# lib
#

GCC ?= gcc
CFLAGS ?= -ffreestanding -O2 -m32 -g -Wall -Wextra -fno-builtin -fno-stack-protector 
INCLUDE ?= -I../include

AS = nasm
ASFLAGS = -f elf32 -g

SRCS := string.c ctype.c

OBJS = $(SRCS:.c=.o) 

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
