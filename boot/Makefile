# compile asm files for boot 
# and system init
#

AS := nasm
MAIN_ASFLAGS ?= -f bin -g

SRCS := boot.asm read_disk.asm print.asm \
		gdt.asm switch_to_pm.asm

BOOT_BIN := boot.bin

all: $(SRCS)
	$(AS) $(MAIN_ASFLAGS) $< -o $(BOOT_BIN) 

.PHONY:
	all clean

clean:
	$(RM) *.o $(BOOT_BIN)
