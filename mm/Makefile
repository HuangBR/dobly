#
# kernel
#

GCC = gcc
CFLAGS = -ffreestanding -O2 -m32 -g -W -Wall -nostdinc -fno-builtin -fno-stack-protector 
INCLUDE = -I../include


SRCS := mem.c 

OBJS = $(SRCS:.c=.o)

DEPS = $(OBJS:.o=.d)

all: $(OBJS)

-include $(DEPS)

%.o: %.c
	$(GCC) $(INCLUDE) $(CFLAGS) -MMD -c $< -o $@	


.PHONY: all clean

clean:
	$(RM) *.o *.d .*swp $(MAIN)
