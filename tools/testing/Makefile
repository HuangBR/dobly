# testing using cmokery
#
#

CC = gcc
CFLAGS = -m32 -fno-builtin -fomit-frame-pointer -fno-stack-protector
INCLUDES = -I/usr/local/lib 
LIBS = -lcmockery

SRCS = test_string.c

OBJS = $(SRCS:.c=.o)


.PHONY: all

all: $(OBJS)
	$(shell for obj in $(OBJS); do \
			echo $(CC) $(CFLAGS) $(INCLUDES) $$obj  $(LIBS) -o $${obj%.o}; \
			done)
.PHONY: test

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	$(RM) $(OBJS)
