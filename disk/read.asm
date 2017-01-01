[bits 16]
[org 0x7c00]

    mov [BOOT_DRIVER], dl

    mov ah, 0x02
    mov al, 20
    mov ch, 0x0
    mov cl, 0x02
    mov dh, 0x0
    mov dl, [BOOT_DRIVER]
    mov bx, stage2

    int 0x13

    jc error

    jmp stage2

    BOOT_DRIVER db 0

    ; Majic bytes
    times 510 -($-$$) db 0x00
    dw 0xaa55

stage2:
    mov ax, 0x0e61
    int 0x10

    cli
    hlt

    times ((0x400) - ($-$$)) db 0x00

error:
    jmp $
