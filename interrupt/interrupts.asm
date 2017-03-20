; interrupts.asm
; contains all system exception
; and other system interface interrupts
; 0  #DE    Divide Error DIV and IDIV instructions.
; 1  #DB    Debug Any code or data reference.
; 2         NMI Interrupt Non-maskable external interrupt.
; 3  #BP    Breakpoint INT 3 instruction.
; 4  #OF    Overflow INTO instruction.
; 5  #BR    BOUND Range Exceeded BOUND instruction.
; 6  #UD    Invalid Opcode (UnDefined Opcode) UD2 instruction or reserved opcode.1
; 7  #NM    Device Not Available (No Math Coprocessor) Floating-point or WAIT/FWAIT instruction.
; 8  #DF    Double Fault Any instruction that can generate an exception, an NMI, or an INTR.
; 9  #MF    CoProcessor Segment Overrun (reserved) Floating-point instruction.2
; 10 #TS    Invalid TSS Task switch or TSS access.
; 11 #NP    Segment Not Present Loading segment registers or accessing system segments.
; 12 #SS    Stack Segment Fault Stack operations and SS register loads.
; 13 #GP    General Protection Any memory reference and other protection checks.
; 14 #PF    Page Fault Any memory reference.
; 15 Reserved
; 16 #MF    Floating-Point Error (Math Fault) Floating-point or WAIT/FWAIT instruction.
; 17 #AC    Alignment Check Any data reference in memory.3
; 18 #MC    Machine Check Error codes (if any) and source are model dependent.4
; 19 #XM    SIMD Floating-Point Exception SIMD Floating-Point Instruction5
; 20 #VE    Virtualization Exception EPT violations6
; 21-31 Reserved
; 32-255    Maskable Interrupts External interrupt from INTR pin or INT n instruction.

[extern int_%1]
[extern DATA_SEG]
[global int%1]
    pusha
    push ds
    push es
    push fs
    push gs
    mov eax, 0x10   ; Data seg
    mov ds, eax
    mov es, eax
    cld
    call int_%1     ; divide by zero
    pop gs
    pop fs
    pop es
    pop ds
    popa
    iret

