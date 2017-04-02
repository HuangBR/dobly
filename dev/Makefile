# drivers
#
#

CC ?= gcc
CFLAGS ?= -Wall -Wextra -ffreestanding -g -fno-stack-protector -nostdinc -O2 -m32
INCLUDES ?= -I../include/

SRCS = screen.c 

OBJS = $(SRCS:.c=.o)

all: $(OBJS)

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

.PHONY: clean all

clean:
	$(RM) *.o
