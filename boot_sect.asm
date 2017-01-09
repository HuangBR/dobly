; a boot sector entering 32-bit protected mode
[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

mov ax, 0x2402
int 0x15
mov ah, 0x0e
add al, '0'
int 0x10

call load_kernel

call switch_to_pm

jmp $

%include "print/print_string_16.asm"
%include "print/print_hex.asm"
%include "disk/disk_load_so.asm"
%include "pm/gdt.asm"
%include "pm/print_string_pm.asm"
%include "pm/switch_to_pm.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET ; set kernel load position in memory
    mov dh, 1            ; set number of sectors read
    mov dl, [BOOT_DRIVE]  ; set read driver
    call disk_load
    ret

[bits 32]
BEGIN_PM:
;    mov ebx, MSG_PROT_MODE
;    call print_string_pm
    
    call KERNEL_OFFSET

    jmp $

; gloable vars
BOOT_DRIVE    db 0
MSG_REAL_MODE db "Started in 16-bits real mode", 0
MSG_PROT_MODE db "Successfully landed in 32-bits Protected mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

times 510-($-$$) db 0
dw 0xaa55
