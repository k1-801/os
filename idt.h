#include "mem.h"
#include "panic.h"
#include "graphics.h"
#include "user.h"
#include "zbase.h"
#include "cmos.h"
#include "klog.h"
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
	outb(0x20,0x20);
	/*switch(r->int_no)
	{
	case 8: panic("Double fault."); break;
	case 13: ; break; //nothing to do.
	}*/
	panic("Int is ocurred");
}

/* These are own ISRs that point to our special IRQ handler
*  instead of the regular 'fault_handler' function */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void irq_install()
{
    irq_remap();

    idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq1, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq2, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq3, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq4, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq5, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq6, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq7, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq8, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq9, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq10, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq11, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq12, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq13, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)irq14, 0x08, 0x8E);

    idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

/* Each of the IRQ ISRs point to this function, rather than
*  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
void irq_handler(struct regs *r)
{
    /* This is a blank function pointer */
    void (*handler)(struct regs *r);

    /* Find out if we have a custom handler to run for this
    *  IRQ, and then finally, run it */
    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_no >= 40)
    {
        outb(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    outb(0x20, 0x20);
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
unsigned char mouse_cycle=0;     //unsigned char
signed char mouse_byte[3];    //signed char
signed char mouse_x=0,oldx=0;         //signed char
signed char mouse_y=0,oldy=0;         //signed char

//Mouse functions
void mouse_handler(struct regs *a_r) //struct regs *a_r (not used but just there)
{
  switch(mouse_cycle)
  {
    case 0:
      mouse_byte[0]=inb(0x60);
      mouse_cycle++;
      break;
    case 1:
      mouse_byte[1]=inb(0x60);
      mouse_cycle++;
      break;
    case 2:
      mouse_byte[2]=inb(0x60);
      mouse_x=mouse_byte[1];
      mouse_y=mouse_byte[2];
      mouse_cycle=0;
      break;
  }
  fillRect(20,20,oldx,oldy,BGCOLOR);
  fillRect(20,20,mouse_x,mouse_y,WHITE);
  oldx=mouse_x;
  oldy=mouse_y;
}
void timer_phase(int hz)
{


    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outb(0x43, 0x36);             /* Set our command byte 0x36 */
    outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}
bool _sleepCurrently=false;
unsigned long msLeft;
volatile unsigned int timer_ticks;
void timer_handler(struct regs *r)
{
	/*
	ticks++;
	if(_sleepCurrently)
	{
		msLeft--;
	}
	if(!msLeft) _sleepCurrently=false;*/
	if(timer_ticks%18==0)
	log("PIT fired");
}
void sleep(unsigned long ms)
{
	_sleepCurrently=true;
	msLeft=ms;
	while(_sleepCurrently);
}
void kbdHandler(struct regs *r)
{
	if(inb(0x60)==29)
	{
		gomenu();
	}
}
void initKbd()
{
	irq_install_handler(1,kbdHandler);
}
void setupPIT()
{
	timer_phase(18);
	irq_install_handler(0,timer_handler);
}
inline void mouse_wait(byte a_type) //unsigned char
{
  dword _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

inline void mouse_write(byte a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  outb(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  outb(0x60, a_write);
}

byte mouse_read()
{
  //Get's response from mouse
  mouse_wait(0);
  return inb(0x60);
}

void mouse_install()
{
  byte _status;  //unsigned char

  //Enable the auxiliary mouse device
  mouse_wait(1);
  outb(0x64, 0xA8);
 
  //Enable the interrupts
  mouse_wait(1);
  outb(0x64, 0x20);
  mouse_wait(0);
  _status=(inb(0x60) | 2);
  mouse_wait(1);
  outb(0x64, 0x60);
  mouse_wait(1);
  outb(0x60, _status);
 
  //Tell the mouse to use default settings
  mouse_write(0xF6);
  mouse_read();  //Acknowledge
 
  //Enable the mouse
  mouse_write(0xF4);
  mouse_read();  //Acknowledge

  //Setup the mouse handler
  irq_install_handler(12, mouse_handler);
}
