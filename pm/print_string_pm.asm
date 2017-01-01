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
    ; mov al, 0x0d        ; 0x0d == '\r'
    ; mov [edx], ax
    ; add edx, 2
    ; mov al, 0x0a        ; 0x0a == '\n'
    ; mov [edx], ax
    popa
    ret
