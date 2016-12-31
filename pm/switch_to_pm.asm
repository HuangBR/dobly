[bits 16]
; switch to protected mode
switch_to_pm:
    
    cli         ; disable interrupt until set up interrupt vector
    lgdt [gdt_descriptor] ; load global descriptor table
    
    mov eax, cr0          ; make switch to protected mode
    or eax, 0x1           ; 1st bit of cr0, take control 
    mov cr0, eax

    jmp CODE_SEG:init_pm

[bits 32]
; initialize registers and the stack once in PM
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_PM
