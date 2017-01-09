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

    add_interrupt(0, int00, STS_IG32, 0);

}

void panic(char *message, char *code, bool halt)
{
    clear_screen();
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
void int_00(void)
{
    panic("Divide By Zero Error","#00", false);
}

void int_01(void)
{
    panic("Debug Error","#DB", false);
}

void int_02(void)
{
    panic("NMI Interrupt","#--", false);
}

void int_03(void)
{
    panic("Breakpoint","#BP", false);
}

void int_04(void)
{
    panic("Overflow","#OF", false);
}

void int_05(void)
{
    panic("BOUND Range Exceeded","#BR", false);
}

void int_06(void)
{
    panic("Invalid Opcode","#UD", false);
}

void int_07(void)
{
    panic("Device Not Available","#NM", false);
}

void int_08(void)
{
    panic("Double Fault","#DF", true);
}

void int_09(void)
{
    panic("Coprocessor Segment Overrun", "#NA", false);
}

void int_10(void)
{
    panic("Invalid TSS","#TS", false);
}

void int_11(void)
{
    panic("Segment Not Present","#NP", false);
}

void int_12(void)
{
    panic("Stack Segment Fault","#SS", false);
}

void int_13(void)
{
    panic("Gneral Protection Fault","#GP", false);
}

void int_14(void)
{
    panic("Page Fault","#PF", false);
}

void int_16(void)
{
    panic("FPU Floating-Point Error","#MF", false);
}

void int_17(void)
{
    panic("Alignment Check","#AC", false);
}

void int_18(void)
{
    panic("Machine Check","#MC", true);
}

void int_19(void)
{
    panic("SIMD Floating-Point","#XF", false);
}

