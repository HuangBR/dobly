; GDT
gdt_start:

gdt_null:
    dd 0x0
    dd 0x0

gdt_code: ; the code segment descripter
    ; base = 0x0, limit= 0xffff
    ; 1st flags: (present)1 (privilege)00 (descriptor type)1 --> 1001b
    ; type flags: (code)1 (confirming)0 (readable)1 (accessed)0  -> 1010b
    ; 2nd flags: (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 -> 1100b
    dw 0xffff     ; Limit 0-15
    dw 0x0        ; Base 0-15
    db 0x0        ; Base 16-23
    db 10011010b  ; 1st flags, type flags
    db 11001111b  ; 2nd flags, Limits 16-19
    db 0x0        ; Base 24-31

gdt_data: ; the data segment
    ; Same as code segment except for type flags
    ; type flags: (code)0 (expand down)0 (writable)1 (accessed)0 --> 0010b
    dw 0xffff       ; limit 0-15
    dw 0x0          ; base 0-15
    db 0x0          ; base 16-23
    db 10010010b    ; 1st flags, type flags
    db 11001111b    ; 2nd flags, limit 16-19
    db 0x0          ; base 24-31

gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start -1 ; size of gdt, 1 less than real size
    dd gdt_start              ; start of gdt

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start 
