#include "mem.h"
#include "panic.h"
/* Defines an IDT entry */
struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed));
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
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
extern void idt_load();

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags)
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
	idt_set_gate(0,(unsigned)isr0, 0x08, 0x8E);
	idt_set_gate(1,(unsigned)isr1, 0x08, 0x8E);
	idt_set_gate(2,(unsigned)isr2, 0x08, 0x8E);
	idt_set_gate(3,(unsigned)isr3, 0x08, 0x8E);
	idt_set_gate(4,(unsigned)isr4, 0x08, 0x8E);
	idt_set_gate(5,(unsigned)isr5, 0x08, 0x8E);
	idt_set_gate(6,(unsigned)isr6, 0x08, 0x8E);
	idt_set_gate(7,(unsigned)isr7, 0x08, 0x8E);
	idt_set_gate(8,(unsigned)isr8, 0x08, 0x8E);
	idt_set_gate(9,(unsigned)isr9, 0x08, 0x8E);
	idt_set_gate(10,(unsigned)isr10, 0x08, 0x8E);
	idt_set_gate(11,(unsigned)isr11, 0x08, 0x8E);
	idt_set_gate(12,(unsigned)isr12, 0x08, 0x8E);
	idt_set_gate(13,(unsigned)isr13, 0x08, 0x8E);
	idt_set_gate(14,(unsigned)isr14, 0x08, 0x8E);
	idt_set_gate(15,(unsigned)isr15, 0x08, 0x8E);
	idt_set_gate(16,(unsigned)isr16, 0x08, 0x8E);
	idt_set_gate(17,(unsigned)isr17, 0x08, 0x8E);
	idt_set_gate(18,(unsigned)isr18, 0x08, 0x8E);
	idt_set_gate(19,(unsigned)isr19, 0x08, 0x8E);
	idt_set_gate(20,(unsigned)isr20, 0x08, 0x8E);
	idt_set_gate(21,(unsigned)isr21, 0x08, 0x8E);
	idt_set_gate(22,(unsigned)isr22, 0x08, 0x8E);
	idt_set_gate(23,(unsigned)isr23, 0x08, 0x8E);
	idt_set_gate(24,(unsigned)isr24, 0x08, 0x8E);
	idt_set_gate(25,(unsigned)isr25, 0x08, 0x8E);
	idt_set_gate(26,(unsigned)isr26, 0x08, 0x8E);
	idt_set_gate(27,(unsigned)isr27, 0x08, 0x8E);
	idt_set_gate(28,(unsigned)isr28, 0x08, 0x8E);
	idt_set_gate(29,(unsigned)isr29, 0x08, 0x8E);
	idt_set_gate(30,(unsigned)isr30, 0x08, 0x8E);
	idt_set_gate(31,(unsigned)isr31, 0x08, 0x8E);

}
struct regs {
uint32_t gs,fs,es,ds;
uint32_t edi,esi,ebp,esp,ebx,edx,ecx,eax;
uint32_t int_no,err_code;
uint32_t eip,cs,eflags,useresp,ss;
};
void fault_handler(struct regs *r)
{
	/*switch(r->int_no)
	{
	case 8: panic("Double fault."); break;
	case 13: ; break; //nothing to do.
	}*/
	panic("Int is ocurred");
}
/* Installs the IDT */
void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;
    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);
	isrs_install();
	
    /* Add any new ISRs to the IDT here using idt_set_gate */



    /* Points the processor's internal register to the new IDT */
    idt_load();
}
