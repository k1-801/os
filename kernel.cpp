//OS365 main kernel file.
\
#define __os365__
#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include "vgaterm.h" //VGA text driver
#include "panic.h" //kernel panic
#include "decls.h"
#include "io.h" //I/O ports
#include "os365.h"
#include "scrio.h"
#include "paging.h"
#include "klog.h"
#include "ahci.h"
#if defined(__cplusplus)
extern "C" {
#endif
#include "idt.h"
#include "fonts.h"
#include "unixstd.h"
#if defined(__linux__)
#error "Compiling is not allowed without the cross-compiler"
#endif
void kernel_main()
{
	//	addr = (int*) kernel_main;
	//
	log("OS365 kernel is started. Disabling interrupts...");
	asm("cli");
	log("done.");
	//idt_install();
	//isrs_install();
	//asm("sti");
	log("Setting up fonts...");
	setupFonts();
	log("done.");
	//kprint("OS365 Kernel 1.0 is loaded.\nInitializing PIC...",0,0);
	init_pics(0x20,0x28);
	//setupPaging();
	//asm("int $8");
	//kprint("\nAll pre-start processes are finished. Preparing to load shell...\n",0,8);
	setGraphicsMode();
	//abort();
	//asm("int $50");
	while(true)
	{
		shellStart();
		log("Error in program: Not returned to Z");
		log("Getting back to Z...");
	}
}
#ifdef __cplusplus
}
#endif
