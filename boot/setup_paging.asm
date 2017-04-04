PDT equ 0x5000
PTE equ 0x6000

[bits 32]
setup_paging:
    mov ecx, 2048 ; set PDT and PTE to 0
    xor eax, eax
    mov edi, PDT
    cld
    rep stosd
    mov dword [PDT], PTE + 7  ; set present bit/ use r/w
    mov edi, PTE + 4092
    mov eax, 0x03ff007
    std
go: stosw 
    sub eax, 0x1000
    jge go
    mov eax, PDT
    mov cr3, eax
    mov eax, cr0
    or  eax, 0x8000000
    mov cr0, eax
    ret




