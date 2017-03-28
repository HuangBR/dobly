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

OS_BIN := DoblyOS.bin

SRCS_BOOT := $(addprefix boot/, boot.asm, read_disk.asm, print.asm \
		gdt.asm switch_to_pm.asm )

SRCS_KERNEL := $(addprefix kernel/, kernel.c trap.c pic.c idt.c \
		vsprintf.c printk.c) 

SRCS_DEV := $(addprefix dev/, io.c screen.c)

SRCS_MM  := $(addprefix mm/, mem.c)

SRCS_C := $(SRCS_KERNEL) $(SRCS_DEV) $(SRCS_INTERRUPT) \
		$(SRCS_MM)

# object files 
OBJS_KERNEL    := $(SRCS_KERNEL:.c=.o) $(addprefix kernel/, traps.o)

OBJS_DEV   := $(SRCS_DEV:.c=.o)

OBJS_INTERRUPT := $(SRCS_INTERRUPT:.c=.o) 

OBJS_MM		   := $(SRCS_MM:.c=.o)

OBJS := $(OBJS_KERNEL) $(OBJS_DEV) $(OBJS_INTERRUPT) $(OBJS_MM)

# main 
BOOT_BIN = boot/boot.bin

KERNEL_BIN = kernel.bin

all : $(OS_BIN)


$(OS_BIN): $(BOOT_BIN) $(KERNEL_BIN) 
	cat $^ > $@
	truncate -s 12K $@

$(BOOT_BIN):
	cd boot && $(MAKE) $(MAKEFLAGS)
	

$(KERNEL_BIN): $(OBJS_DEV) $(OBJS_KERNEL) $(OBJS_MM)
	# $(LD) $(LDFLAGS) -T kernel.ld $^ -o $@
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJS_DEV):
	cd dev && $(MAKE) $(MAKEFLAGS)

$(OBJS_KERNEL):
	cd kernel && $(MAKE) $(MAKEFLAGS)

$(OBJS_MM):
	cd mm && $(MAKE) $(MAKEFLAGS)
	
# running in qemu or bochs 
run: $(OS_BIN)
	qemu-system-i386 -drive format=raw,file=$< -display sdl -monitor stdio

qemu: $(OS_BIN)
	qemu-system-i386 -drive format=raw,file=$< -display sdl -s -S -monitor stdio

bochs: $(OS_BIN)
	bochs -f bochsrc

disasm: $(KERNEL_BIN)
	objdump -m i386 -M i386,intel -b binary -D $<
	ndisasm -b 32 -o1000h -a $<

#$(AS) -f elf -F dwarf $^ -o $@

debug: 
	gdb -nx -x .gdbinit
	
%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@	

.PHONY: all clean 

clean:
	$(RM) *.o *.d *.bin .*.swp *.log
	(cd dev && $(MAKE) clean)
	(cd kernel && $(MAKE) clean)
	(cd mm && $(MAKE) clean)
