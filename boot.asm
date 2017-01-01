[bits 16]
[org 0x7c00]

mov bp, 9000
mov sp, bp

; GDT
gdt_start:

gtd_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start -1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

[bits 16]
switch_to_pm:
    cli

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm

[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_PM

[bits 32]
; Define some constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
; prints a null-terminated string pointed to by EDX
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY ; Set edx to the start of vid mem.
print_string_pm_loop:
    mov al, [ebx] ; Store the char at EBX in AL
    mov ah, WHITE_ON_BLACK ; Store the attributes in AH
    cmp al, 0 ; if (al == 0), at end of string , so
    je print_string_pm_done; jump to done
    mov [edx], ax ; Store char and attributes at current
    ; character cell.
    add ebx, 1 ; Increment EBX to the next char in string.
    add edx, 2 ; Move to next character cell in vid mem.
jmp print_string_pm_loop ; loop around to print the next char.

print_string_pm_done :
    popa
    ret ; Return from the function

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm



    jmp $

HELLOC db "hello c world!", 0
MSG_PROT_MODE db "Successfully landed in 32-bit Protected Mode", 0

times 510 - ($ - $$) db 0
dw 0xaa55
