# drivers
#
#

CC = gcc
CFLAGS = -Wall -Wextra -ffreestanding -g

SRCS = screen.c common.c

OBJS = $(SRCS:.c=.o)

all: $(OBJS)


*.o: *.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) *.o
