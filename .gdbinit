# add-symbol-file stage0.elf 0x7c00
# add-symbol-file stage1.elf 0x7e00
target remote localhost:1234
set disassembly-flavor intel
layout split
layout regs
break *0x7c00
  commands
    set architecture i8086
  end
break *0x7c18
break *0x7cd7
break *0x7cfc
break *0x7d02
break *0x7d18
break *0x1000
  commands
    set architecture i386:intel
  end
break *0x7c0f
break *0x7d0c
break *0x7d12
break *0x7d1e
