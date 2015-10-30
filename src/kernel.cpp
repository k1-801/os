//OS365 main kernel file.

#include "../include/stdinclude.h"

#define __os365__
#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include "../include/mboot.h"
#include "../include/vgaterm.h" //VGA text driver
#include "../include/panic.h" //kernel panic
#include "../include/decls.h"
#include "../include/io.h" //I/O ports
#include "../include/os365.h"
#include "../include/mouse.h"
#include "../include/scrio.h"
#include "../include/paging.h"
#include "../include/klog.h"
#include "../include/ahci.h"
#if defined(__cplusplus)
extern "C" {
#endif
#include "../include/idt.h"
#include "../include/gdt.h"
#include "../include/fonts.h"
#include "../include/unixstd.h"

void kernel_main(struct mboot_info_struct *mbinfo)
{
	//	addr = (int*) kernel_main;
	//
	log("[LOAD] " QUOTATE(DISTNAME) " kernel is started. Disabling interrupts...");
	log("[DISCLAIMER] " QUOTATE(DISTNAME) " is totally free. If you have bought it, please report us seller's contact information to prevent further project law violation.");
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
	vbe_info_t* vbeInfo=mbinfo->vbe_mode;
	framebuffer        =mbinfo->framebuffer_addr;
	fbpitch            =mbinfo->framebuffer_pitch;
	fbbpp              =mbinfo->framebuffer_bpp;

	//memset((void*)framebuffer,0x004DFF,1024*768*3);
	initKbd();
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
