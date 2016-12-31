print_hex:
    mov cl, 16
ph_loop:
    push dx
    mov bx, 0x000f
    sub cl, 4
    shl bx, cl
    and dx, bx
    shr dx, cl
    mov al, dl
    cmp al, 9
    jg  gt_9
    add al, '0'
    jmp ph_out
    gt_9:
        sub al, 10
        add al, 'a'
    ph_out:
        mov ah, 0x0e
        int 0x10
        pop dx
        test cl, cl
        jnz ph_loop
    ret
    

