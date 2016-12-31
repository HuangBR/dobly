disk_load:
    push dx
    mov ah, 0x02 ; int 0x13 function, read
    mov al, dh   ; number of sectors to read
    mov ch, 0x00 ; cylinder
    mov dh, 0x00 ; header
    mov cl, 0x02 ; sector
    ; mov dl, 0x80 ;  floppy 0 floppy1 1 hdd 0x80 hdd2 0x81

    int 0x13

    jc disk_error

    pop dx
    cmp dh, al
    jne sector_error
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    mov dh, ah
    mov dl, 0x0
    call print_hex
    jmp disk_loop

sector_error:
    mov bx, SECTORS_ERROR_MSG
    call print_string

disk_loop:
    jmp $

DISK_ERROR_MSG db "Disk read error!", 0    
SECTORS_ERROR_MSG db "Read Sectors error!", 0
