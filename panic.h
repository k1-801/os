#ifndef __PANIC_H
#define __PANIC_H
#include "graphics.h"
#include "strfcn.h"
#include "mem.h"
#include "fonts.h"
#include "klog.h"
void nop(){}
uint16_t eax asm("eaxreg");
uint16_t ebx asm("ebxreg");
uint16_t esp asm("espreg");
uint16_t eip asm("eipreg");
void panic(const char* msg)
{
	setupFonts();
	//make beautiful screen filter
	memcpy((void*)0xA0000,(void*)0xB800,(640*480)/4);
	memcpy((void*)0xA3000,(void*)0xBB00,(640*480)/4);
	memcpy((void*)0xA6000,(void*)0xBE00,(640*480)/4);
	memcpy((void*)0xA9000,(void*)0xBF10,(640*480)/4);
	//write in the system log
	log("[FATAL] Kernel panic, reason: ");
	log(msg);
	log("[INFO] Writing message to the screen...");
	//write the message
	vgaWriteStr(0,0,"Kernel panic: ",LIGHT_RED,BLACK);
	vgaWriteStr(14*8,0,msg,LIGHT_RED,BLACK);
	vgaWriteStr(0,8,"Please restart your computer.",LIGHT_RED,BLACK);
	log("[INFO] Writing last 50 log strings...");
	log("[HALT] Halting.");
	vgaWriteStr(0,16,"Last 50 system log messages:",LIGHT_RED,BLACK);
	int i=0;
	for(int j=0;i<50&&i<lnum;i++,j++)
	{
		vgaWriteStr(0,24+j*8,logs[i],LIGHT_RED,BLACK);
	}
//vgaWriteStr(240,24,itoa(eip),LIGHT_RED,BLACK);

	//displaying the regs
	for(;;)
	{
		asm("hlt");
	}
}
#endif
