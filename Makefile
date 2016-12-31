# 
#
#
GCC = gcc
CFLAGS = -fhosted 

LD = ld
LDFLAGS = -Ttext 0x1000 --oformat binary

AS = nasm
ASFLAGS = -f bin -g

SRCS := boot_sect.asm

MAIN = boot_sect.bin

all : $(MAIN)

$(MAIN): $(SRCS)
	$(AS) $(ASFLAGS) $^ -o $@

run: $(MAIN) kernel.bin
	cat $^ > os.img
	qemu-system-i386 -drive format=raw,file=os.img -display curses -s -S -monitor stdio

kernel.bin: kernel.o
	$(LD) $(LDFLAGS) $< -o $@

print_string.o: print_string.asm
	$(AS) -f elf -F dwarf $^ -o $@

print_string: print_string.o
	ld -m elf_i386 $^ -o $@

gdb: print_string
	gdb -x gdbsrc $^

debug: 
	gdb -x script.gdb
	
*.o:*.c
	$(GCC) $(CFLAGS) -c $< -o $@	

.PHONY: clean

clean:
	$(RM) *.o *.bin os.img $(MAIN)

