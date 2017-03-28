[bits 16]
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
    
[bits 16]
print_string:
    push ax
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
        pop ax
        ret


[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK

    cmp al, 0
    je print_string_pm_done

    mov [edx], ax
    
    inc ebx
    add edx, 2

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret
