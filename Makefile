# 
#
#
GCC = gcc
#CFLAGS = -ffreestanding -O2 -m32 -g -W -Wall -nostdinc -fno-builtin -fno-stack-protector -fomit-frame-pointer
CFLAGS = -ffreestanding -O2 -g -W -Wall -m32 -std=c99
export CFLAGS

LD = ld
#LDFLAGS = -Ttext 0x1000 --oformat binary -m elf_i386 -nostdlib 
LDFLAGS = -Ttext 0x1000 --oformat binary -m elf_i386
# LDFLAGS = -m elf_i386 -nostdlib

AS = nasm
MAIN_ASFLAGS = -f bin -g
ASFLAGS = -f elf32 -g
export ASFLAGS


SRCS_ASM := boot_sect.asm

SRCS_KERNEL    := $(addprefix kernel/, kernel.c trap.c) 
SRCS_DRIVERS   := $(addprefix drivers/, io.c screen.c)
SRCS_INTERRUPT := $(addprefix interrupt/, idt.c pic.c)
SRCS_MM		   := $(addprefix mm/, mem.c)

SRCS_C := $(SRCS_KERNEL) $(SRCS_DRIVERS) $(SRCS_INTERRUPT) \
		$(SRCS_MM)


OBJS_KERNEL    := $(SRCS_KERNEL:.c=.o) $(addprefix kernel/, traps.o)
OBJS_DRIVERS   := $(SRCS_DRIVERS:.c=.o)
OBJS_INTERRUPT := $(SRCS_INTERRUPT:.c=.o) 
OBJS_MM		   := $(SRCS_MM:.c=.o)

OBJS := $(OBJS_KERNEL) $(OBJS_DRIVERS) $(OBJS_INTERRUPT) $(OBJS_MM)

MAIN = boot_sect.bin

all : os.img

$(MAIN): $(SRCS_ASM)
	$(AS) $(MAIN_ASFLAGS) $^ -o $@

os.img : $(MAIN) kernel.bin
	cat $^ > $@
	truncate -s 12K $@

$(OBJS_DRIVERS):
	@make -C drivers

$(OBJS_KERNEL):
	@make -C kernel

$(OBJS_INTERRUPT):
	@make -C interrupt

$(OBJS_MM):
	@make -C mm

compile: $(OBJS_DRIVERS) $(OBJS_KERNEL) $(OBJS_INTERRUPT)
	@echo compile finished

run: os.img
	qemu-system-i386 -drive format=raw,file=$< -display sdl -monitor stdio

qemu: os.img
	qemu-system-i386 -drive format=raw,file=$< -display sdl -s -S -monitor stdio

bochs: os.img
	bochs -f bochsrc

kernel.bin: $(OBJS)
	# $(LD) $(LDFLAGS) -T kernel.ld $^ -o $@
	$(LD) $(LDFLAGS) $^ -o $@

disasm: kernel.bin
	objdump -m i386 -M i386,intel -b binary -D $<
	ndisasm -b 32 -o1000h -a $<

print_string.o: print_string.asm
	$(AS) -f elf -F dwarf $^ -o $@

print_string: print_string.o
	ld -m elf_i386 $^ -o $@

gdb: print_string
	gdb -x gdbsrc $^

debug: 
	gdb -nx -x .gdbinit
	
*.o:*.c
	$(GCC) $(CFLAGS) -c $< -o $@	

.PHONY: all clean 

clean:
	$(RM) *.o *.bin os.img $(MAIN) .*.swp *.log
	@make -C drivers   clean
	@make -C kernel    clean
	@make -C interrupt clean
	@make -C mm		   clean
