//OS365 main kernel file.
\
#define __os365__
#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include "mboot.h"
#include "vgaterm.h" //VGA text driver
#include "panic.h" //kernel panic
#include "decls.h"
#include "io.h" //I/O ports
#include "os365.h"
#include "mouse.h"
#include "scrio.h"
#include "paging.h"
#include "klog.h"
#include "ahci.h"
#if defined(__cplusplus)
extern "C" {
#endif
#include "idt.h"
#include "gdt.h"
#include "fonts.h"
#include "unixstd.h"
#if defined(__linux__)
#error "Compiling is not allowed without the cross-compiler"
#endif
void kernel_main(struct multiboot *mbinfo)
{
	//	addr = (int*) kernel_main;
	//
	log("[LOAD] OS365 kernel is started. Disabling interrupts...");
	log("[DISCLAIMER] OS365 is fully free. If you buyed it, it's a law violation.");
	asm("cli");
	log("done.");
	log("[INFO] Setting up GDT...");
	gdt_install();
	log("done.");
	log("[INFO] Setting up IDT...");
	idt_install();
	log("done.");
	log("[INFO] Setting up ISRs...");
	isrs_install();
	log("done.");
	log("[INFO] Setting up IRQ handlers...");
	irq_install();
	log("done.");
	asm("sti");
	log("[INFO] Setting up fonts...");
	setupFonts();
	log("done.");
	log("[INFO] Initializing PIC...");
	//kprint("OS365 Kernel 1.0 is loaded.\nInitializing PIC...",0,0);
	init_pics(0x20,0x28);
	log("done.");
	//setupPaging();
	//asm("int $8");
	//kprint("\nAll pre-start processes are finished. Preparing to load shell...\n",0,8);
	log("[INFO] Setting VBE graphics mode...");
	//sleep(18);
	//setGraphicsMode();
	vbe_info_t* vbeInfo=(vbe_info_t*)(*mbinfo).vbe_mode;
	framebuffer=(uint32_t*)(*vbeInfo).physbase;
	vbeMode=*vbeInfo;
	log("done.");
	//mouse_install();
	log("[INFO] Setting up the timer...");
	setupPIT();
	log("done.");
	log("[INFO] Loading Z Window System...");
	//abort();
	while(true)
	{
		shellStart();
		fRun=true;
		log("[WARNING] Error in program: Not returned to Z");
		log("[INFO] Getting back to Z...");
	}
}
#ifdef __cplusplus
}
#endif
