# add-symbol-file stage0.elf 0x7c00
# add-symbol-file stage1.elf 0x7e00
target remote localhost:1234
set architecture i8086
layout split
layout regs
break *0x7c00
break *0x7cd2
break *0x7ce2
break *0x7cfc
break *0x7cd1
break *0x1386
