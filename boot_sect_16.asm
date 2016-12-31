;
;   simple boot sector
;
[bits 16]
[org 0x7c00]

mov [BOOT_DRIVE], dl

mov bp, 0x8000
mov sp, bp

; mov dx, 0x9000
; call print_hex

mov bx, 0x9000
mov dh, 5
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]
call print_hex

mov dx, [0x9000 + 512]
call print_hex

hlt
jmp $



mov ah, 0x0e

mov al, [the_secret]
int 0x10

mov bx, 0x7c00
mov ds, bx
mov al, [the_secret]
int 0x10

mov al, [es:the_secret]
int 0x10

jmp $




[org 0x7c00]

mov bx, HELLO_MSG
call print_string
; 
mov bx, GOODBYE_MSG
call print_string
; 
jmp $ 
; 
mov ah, 0x0e

mov al, 'H'
int 0x10

mov al, [the_secret]
int 0x10

mov bx, the_secret
add bx, 0x7c00
mov al, [bx]
int 0x10

mov al, [0x7c1e]
int 0x10

the_secret:
    db 'X'

halt:
    hlt


%include "print_string_16.asm"
%include "print_hex.asm"
%include "disk_load.asm"

HELLO_MSG:   db 'Hello, World!', 0
GOODBYE_MSG: db 'Goodbye!', 0
BOOT_DRIVE:  db 0

times 510-($-$$) db 0
dw 0xaa55


times 256 dw 0xdada
times 256 dw 0xfafc

