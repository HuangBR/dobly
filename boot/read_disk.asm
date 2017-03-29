[bits 16]
disk_load:
    mov  [SECTORS], dh
    mov  ch, 0x00      ; Cylinder = 0
    mov  dh, 0x00      ; Header   = 0
    mov  cl, 0x02      ; Sector   = 2
next_group:
    mov  di, 5         ; Max 5 tries
again: 
    mov  ah, 0x02      ; Read sectors from Drive
    mov  al, [SECTORS] ; Sectors To Read Count
    int  0x13
    jc   maybe_retry
    sub  [SECTORS], al ; Remaining sectors
    jz  ready
    mov  cl, 0x01      ; Always sector 1
    xor  dh, 1         ; Next head on diskette!
    jnz  next_group
    inc  ch            ; Next cylinder
    jmp  next_group
maybe_retry:
    mov  ah, 0x00      ; Reset diskdrive
    int  0x13
    dec  di
    jnz  again
    jmp  disk_error
ready:
    ret

disk_error:
    mov  bx, DISK_ERROR_MSG 
    call print_string 
    jmp  $

SECTORS db 0
DISK_ERROR_MSG db "Disk read error!", 0
