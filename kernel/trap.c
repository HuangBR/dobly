/*
 * init IDT
 * trap, interrupt and call gate 
 */
#include <types.h>
#include <io.h>
#include <idt.h>
#include <interrupts.h>
#include <pic.h>
#include <drivers/screen.h>
#include "traps.h"


void trap_init(void)
{

    set_gate(0, int00, STS_IG32, 0);
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

void do_breakpoint(void)
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

