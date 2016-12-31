# add-symbol-file stage0.elf 0x7c00
# add-symbol-file stage1.elf 0x7e00
target remote localhost:1234
set architecture i8086
br *0x7c00
layout split
layout regs
