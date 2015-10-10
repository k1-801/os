#include "mem.h"
#include "panic.h"
/* Defines an IDT entry */
/*struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));
extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* This exists in 'start.asm', and is used to load our IDT */
extern void _idt_load();

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* The interrupt routine's base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}
void isrs_install()
{
	idt_set_gate(0,(unsigned)_isr0, 0x08, 0x8E);
	idt_set_gate(1,(unsigned)_isr1, 0x08, 0x8E);
	idt_set_gate(2,(unsigned)_isr2, 0x08, 0x8E);
	idt_set_gate(3,(unsigned)_isr3, 0x08, 0x8E);
	idt_set_gate(4,(unsigned)_isr4, 0x08, 0x8E);
	idt_set_gate(5,(unsigned)_isr5, 0x08, 0x8E);
	idt_set_gate(6,(unsigned)_isr6, 0x08, 0x8E);
	idt_set_gate(7,(unsigned)_isr7, 0x08, 0x8E);
	idt_set_gate(8,(unsigned)_isr8, 0x08, 0x8E);
	idt_set_gate(9,(unsigned)_isr9, 0x08, 0x8E);
	idt_set_gate(10,(unsigned)_isr10, 0x08, 0x8E);
	idt_set_gate(11,(unsigned)_isr11, 0x08, 0x8E);
	idt_set_gate(12,(unsigned)_isr12, 0x08, 0x8E);
	idt_set_gate(13,(unsigned)_isr13, 0x08, 0x8E);
	idt_set_gate(14,(unsigned)_isr14, 0x08, 0x8E);
	idt_set_gate(15,(unsigned)_isr15, 0x08, 0x8E);
	idt_set_gate(16,(unsigned)_isr16, 0x08, 0x8E);
	idt_set_gate(17,(unsigned)_isr17, 0x08, 0x8E);
	idt_set_gate(18,(unsigned)_isr18, 0x08, 0x8E);
	idt_set_gate(19,(unsigned)_isr19, 0x08, 0x8E);
	idt_set_gate(20,(unsigned)_isr20, 0x08, 0x8E);
	idt_set_gate(21,(unsigned)_isr21, 0x08, 0x8E);
	idt_set_gate(22,(unsigned)_isr22, 0x08, 0x8E);
	idt_set_gate(23,(unsigned)_isr23, 0x08, 0x8E);
	idt_set_gate(24,(unsigned)_isr24, 0x08, 0x8E);
	idt_set_gate(25,(unsigned)_isr25, 0x08, 0x8E);
	idt_set_gate(26,(unsigned)_isr26, 0x08, 0x8E);
	idt_set_gate(27,(unsigned)_isr27, 0x08, 0x8E);
	idt_set_gate(28,(unsigned)_isr28, 0x08, 0x8E);
	idt_set_gate(29,(unsigned)_isr29, 0x08, 0x8E);
	idt_set_gate(30,(unsigned)_isr30, 0x08, 0x8E);
	idt_set_gate(31,(unsigned)_isr31, 0x08, 0x8E);

}
struct regs {
unsigned int gs,fs,es,ds;
unsigned int edi,esi,ebp,esp,ebx,edx,ecx,eax;
unsigned int int_no,err_code;
unsigned int eip,cs,eflags,useresp,ss;
};
void fault_handler(struct regs *r)
{
	switch(r->int_no)
	{
	case 8: panic("Double fault."); break;
	case 13: ; break; //nothing to do.
	}
}
/* Installs the IDT */
void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */



    /* Points the processor's internal register to the new IDT */
    _idt_load();
}
