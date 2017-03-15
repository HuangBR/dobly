#
# kernel
#

GCC = gcc
CFLAGS = -ffreestanding -O2 -m32 -g -W -Wall -nostdinc -fno-builtin -fno-stack-protector 
INCLUDE = -I../include


SRCS := mem.c 

OBJS = $(SRCS:.c=.o)

all: $(OBJS)

%.o: %.c
	$(GCC) $(INCLUDE) $(CFLAGS) -c $< -o $@	

.PHONY: all clean

clean:
	$(RM) *.o .*swp $(MAIN)
