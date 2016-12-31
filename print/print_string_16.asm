print_string:
    mov ah, 0x0e
    loop:
        mov al, [bx]
        test al, al
        jz out
        int 0x10
        inc bx
        jmp loop
    out:
        xor bx, bx
        ret

