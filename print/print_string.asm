section .text
print_string:
    mov ah, 0x0e
    loop:
        mov al, [ebx]
        test al, al
        jz out
;    int 0x10
        inc ebx
        jmp loop
out:
    xor ebx, ebx
    ret


section .text 
global _start
    _start:
        mov ebx, msg
        call print_string

section .data
msg:
    db "hello c", '0'


