# test read

AS = nasm 
ASFLAGS = -f bin -g

SRCS = read.asm

MAIN = read.bin

all: $(MAIN)

$(MAIN): $(SRCS)
		   $(AS) $(ASFLAGS) $^ -o $@

run: all
	qemu-system-i386 -s -S -curses -hda $(MAIN) -monitor stdio

debug:
	gdb -x run.gdb

clean:
	$(RM) *.o $(MAIN) 
	pkill qemu
