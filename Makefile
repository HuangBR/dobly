# compile os
# debug os
# 

GCC = gcc
CFLAGS = -ffreestanding -O2 -g -W -Wall -m32 -std=c99 -fomit-frame-pointer
export CFLAGS

LD = ld
LDFLAGS = -Ttext 0x1000 --oformat binary -m elf_i386

AS = nasm
ASFLAGS = -f elf32 -g
export ASFLAGS

OS_BIN := DoblyOS.bin

# source files
SRCS_BOOT := $(addprefix boot/, boot.asm read_disk.asm print.asm \
		gdt.asm switch_to_pm.asm )

SRCS_KERNEL := $(addprefix kernel/, kernel.c trap.c pic.c idt.c \
		vsprintf.c printk.c) 

SRCS_DEV := $(addprefix dev/, screen.c)

#SRCS_MM  := $(addprefix mm/, mem.c)

SRCS_LIB := $(addprefix lib/, ctype.c string.c)

SRCS_C := $(SRCS_KERNEL) $(SRCS_DEV) $(SRCS_LIB) \
		$(SRCS_MM)

# object files 
OBJS_KERNEL	:= $(SRCS_KERNEL:.c=.o) $(addprefix kernel/, traps.o)

OBJS_DEV := $(SRCS_DEV:.c=.o)

OBJS_MM := $(SRCS_MM:.c=.o)

OBJS_LIB := $(SRCS_LIB:.c=.o)

OBJS := $(OBJS_KERNEL) $(OBJS_DEV) $(OBJS_INTERRUPT) $(OBJS_MM) $(OBJS_LIB)

# main 
BOOT_BIN = boot.bin

KERNEL_BIN = kernel.bin

all : $(OS_BIN)

.PHONY: all

# os image file
$(OS_BIN): $(BOOT_BIN) $(KERNEL_BIN) 
	cat $^ > $@
	truncate -s 12K $@

# bootloader image
$(BOOT_BIN): $(SRCS_BOOT)
	$(AS) -I boot/ -f bin -g $< -o $@
	
# kernel binary
$(KERNEL_BIN): $(OBJS_DEV) $(OBJS_KERNEL) $(OBJS_MM) $(OBJS_LIB)
	$(LD) $(LDFLAGS) $^ -o $@

# devices compile
$(OBJS_DEV):
	$(MAKE) -C dev $(MAKEFLAGS)

# kernel compile
$(OBJS_KERNEL):
	$(MAKE) -C kernel $(MAKEFLAGS)

# memory manage compile
$(OBJS_MM):
	$(MAKE) -C mm $(MAKEFLAGS)
	
# lib compile
$(OBJS_LIB):
	$(MAKE) -C lib $(MAKEFLAGS)

# running in qemu or bochs 
run: $(OS_BIN)
	qemu-system-i386 -drive format=raw,file=$< -display sdl -monitor stdio

bochs: $(OS_BIN)
	bochs -f bochsrc


# get assembly from binary file
disasm: $(KERNEL_BIN)
	objdump -m i386 -M i386,intel -b binary -D $<
	ndisasm -b 32 -o1000h -a $<

# debug using qemu and gdb
qemu: $(OS_BIN)
	qemu-system-i386 -drive format=raw,file=$< -display sdl -s -S -monitor stdio

debug: 
	gdb -nx -x .gdbinit
	

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@	

.PHONY: clean 

clean:
	$(RM) *.o *.d *.bin .*.swp *.log
	$(MAKE) -C boot		clean
	$(MAKE) -C dev 		clean
	$(MAKE) -C kernel 	clean
	$(MAKE) -C mm 		clean
	$(MAKE) -C lib		clean
