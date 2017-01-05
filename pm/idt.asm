; IDT
itd_start:

;interrupt 0
dw 0x0000
dw 0x10
dw 0x8E00
dw 0x20

;interrupt 1
dw 0x0000
dw 0x10
dw 0x8E00
dw 0x20

;interrupt 2, intel reserved, we set the 'present' bit to 0 on this one
dw 0x0000
dw 0x10
dw 0xE00
dw 0x20

;interrupts 3-14 now, since we are making the descriptors
;identical, we are going to loop to get them all(12 total)
%rep 0xC
  dw 0x0000
  dw 0x10
  dw 0x8E00
  dw 0x20
%endrep

;interrupt 15, intel reserved, we set the 'present' bit to 0 on this one
dw 0x0000
dw 0x10
dw 0xE00
dw 0x20

;interrupt 16
dw 0x0000
dw 0x10
dw 0x8E00
dw 0x20

idt_end:

; idt descriptor
idt_descriptor:
    dw idt_end - idt_start -1
    dd idt_start
