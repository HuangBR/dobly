/*
 * init IDT
 * trap, interrupt and call gate 
 */
#include <types.h>
#include <io.h>
#include <dev/screen.h>
#include "idt.h"
#include "pic.h"
#include "traps.h"

int do_exit(long code);

void page_exception(void);

void divide_error(void);
void debug(void);
void nmi(void);
void int3(void);
void overflow(void);
void bounds(void);
void invalid_op(void);
void device_not_available(void);
void double_fault(void);
void coprocessor_segment_overrun(void);
void invalid_TSS(void);
void segment_not_present(void);
void stack_segment(void);
void general_protection(void);
void page_fault(void);
void coprocessor_error(void);
void reserved(void);

void trap_init(void)
{
    int i = 0;

    set_trap_gate(0, &divide_error);
    set_trap_gate(1, &debug);
    set_trap_gate(2, &nmi);
    set_system_gate(3, &int3);   /* int3-5 can be called from all */
    set_system_gate(4, &overflow);
    set_system_gate(5, &bounds);
    set_trap_gate(6, &invalid_op);
    set_trap_gate(7, &device_not_available);
    set_trap_gate(8, &double_fault);
    set_trap_gate(9, &coprocessor_segment_overrun);
    set_trap_gate(10, &invalid_TSS);
    set_trap_gate(11, &segment_not_present);
    set_trap_gate(12, &stack_segment);
    set_trap_gate(13, &general_protection);
    // set_trap_gate(14, &page_fault);
    set_trap_gate(15, &reserved);
    set_trap_gate(16, &coprocessor_error);
    for (i = 17; i < 32; i++)
        set_trap_gate(i,&reserved);    
}

void panic(char *message, char *code, bool halt)
{
    print("system error\n");
    print(message);
    print("\n");
    print(code);
    print("\n");
    if(halt){
        print("A fatal\n");
        print("\n\n\n\n>>SYSTEM HALTED");
        __asm__ ("cli\n");
        __asm__ ("hlt\n");
    } else {
        print("A non fatl\n");
        print("\n\n\n\n<Press any key to continue>\n");
    }
    outb(PIC1, EOI);
}

/*
 * Exception Handlers
 */
void do_general_protection()
{
    panic("general protection", "###", true);
}

void do_divide_error(void)
{
    panic("Divide By Zero Error","#00", false);
}

void do_debug(void)
{
    panic("Debug Error","#DB", false);
}

void do_nmi(void)
{
    panic("NMI Interrupt","#--", false);
}

void do_int3(void)
{
    panic("Breakpoint","#BP", false);
}

void do_overflow(void)
{
    panic("Overflow","#OF", false);
}

void do_bounds(void)
{
    panic("BOUND Range Exceeded","#BR", false);
}

void do_invalid_op(void)
{
    panic("Invalid Opcode","#UD", false);
}

void do_device_not_available(void)
{
    panic("Device Not Available","#NM", false);
}

void do_double_fault(void)
{
    panic("Double Fault","#DF", true);
}

void do_coprocessor_segment_overrun(void)
{
    panic("Coprocessor Segment Overrun", "#NA", false);
}

void do_invalid_TSS(void)
{
    panic("Invalid TSS","#TS", false);
}

void do_segment_not_present(void)
{
    panic("Segment Not Present","#NP", false);
}

void do_stack_segment(void)
{
    panic("Stack Segment Fault","#SS", false);
}

void do_protection(void)
{
    panic("Gneral Protection Fault","#GP", false);
}

void do_coprocessor_error(void)
{
    panic("Page Fault","#PF", false);
}

void do_math_fault(void)
{
    panic("FPU Floating-Point Error","#MF", false);
}

void do_align_check(void)
{
    panic("Alignment Check","#AC", false);
}

void do_machine_check(void)
{
    panic("Machine Check","#MC", true);
}

void do_SIMD_FP(void)
{
    panic("SIMD Floating-Point","#XF", false);
}

void do_reserved(long esp, long error_code)
{
    panic("reserved (15,17-31) error", "###", false);
}

