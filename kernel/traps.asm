; traps.asm contains most interrupt service handler
; including trap and interrupt handle

extern do_divide_error
extern do_nmi
extern do_int3
extern do_overflow
extern do_bounds
extern do_invalid_op
extern do_device_not_available
extern do_coprocessor_segment_overrun
extern do_reserved
extern do_coprocessor_error
extern do_double_fault
extern do_invalid_TSS
extern do_segment_not_present
extern do_stack_segment
extern do_general_protection

global divide_error, debug, nmi, int3, overflow, bounds, invalid_op
global device_not_available, double_fault, coprocessor_segment_overrun
global invalid_TSS, segment_not_present, stack_segment
global general_protection, coprocessor_error, reserved

; This is called for all exceptions which do not push an error code. 
no_error_code:
    xchg eax, [esp]
    push ebx
    push ecx
    push edx
    push edi
    push esi
    push ebp
    push ds
    push es
    push fs
    push gs
    push 0x0    ; error code
    lea edx, [esp+48]
    push edx
    mov edx, 0x10
    mov ds, dx
    mov es, dx
    mov fs, dx
    mov gs, dx
    call eax
    add esp, 8
    pop gs
    pop fs
    pop es
    pop ds
    pop ebp
    pop esi
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax
    iret

divide_error:
    push do_divide_error
    jmp no_error_code

debug:
    push do_int3     ; _do_debug
    jmp no_error_code

nmi:
    push do_nmi
    jmp no_error_code

int3:
    push do_int3
    jmp no_error_code

overflow:
    push do_overflow
    jmp no_error_code

bounds:
    push do_bounds
    jmp no_error_code

invalid_op:
    push do_invalid_op
    jmp no_error_code

device_not_available:
    push do_device_not_available
    jmp no_error_code

coprocessor_segment_overrun:
    push do_coprocessor_segment_overrun
    jmp no_error_code

reserved:
    push do_reserved
    jmp no_error_code

coprocessor_error:
    push do_coprocessor_error
    jmp no_error_code

; This is called for all exceptions which push an error code. 
error_code:
    xchg eax, [esp+4] ; error code
    xchg ebx, [esp]   ; function address
    push ecx
    push edx
    push esi
    push edi
    push ebp
    push ds
    push es
    push fs
    push gs
    push eax    ; error code
    lea eax, [esp+48]
    push eax    ; sp before interrupt
    mov eax, 0x10 ; data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call ebx
    add esp, 8
    pop gs
    pop fs
    pop es
    pop ds
    pop ebp
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    iret

double_fault:
    push do_double_fault
    jmp error_code

invalid_TSS:
    push do_invalid_TSS
    jmp error_code

segment_not_present:
    push do_segment_not_present
    jmp error_code

stack_segment:
    push do_stack_segment
    jmp error_code

general_protection:
    push do_general_protection
    jmp error_code

