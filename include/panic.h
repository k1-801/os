#ifndef PANIC_HPP
#define PANIC_HPP

#include "FbGraphics.hpp"
#include "Static.hpp"

#include "strfcn.h"
#include "mem.h"
#include "fonts.h"

void nop(){}

uint32_t eax,ebx,ecx,edx,esi,edi;

void panic(const char* msg)
{
    asm("mov %eax, eax; mov %ebx, ebx; mov %ecx, ecx; mov %edx, edx; mov %esi, esi; mov %edi, esi; ");
	setupFonts();
	//make beautiful screen filter
    uint32_t fill=0x222222;
	memset((void*)framebuffer,fill,(1024*768*3)/1);
	//write in the system log
	log("[FATAL] Kernel panic, reason: ");
	log(msg);
	log("[INFO] Writing message to the screen...");
	//write the message
	fillRect(500,200,1024/2-250,768/2-100,0x444444);
	drawRect(500,200,1024/2-250,768/2-100,LIGHT_GREY);
	drawBitmap(roundLT_1,1024/2-250,768/2-100,16,16,fill,0x444444,LIGHT_GREY,0,0);
	drawBitmap(roundRT_1,1024/2-250+500-15,768/2-100,16,16,fill,0x444444,LIGHT_GREY,0,0);
	drawBitmap(roundLB_1,1024/2-250,768/2-100+200-15,16,16,fill,0x444444,LIGHT_GREY,0,0);
	drawBitmap(roundRB_1,1024/2-250+500-15,768/2-100+200-15,16,16,fill,0x444444,LIGHT_GREY,0,0);
	vgaWriteStr(0,0,"Kernel panic: ",LIGHT_GREY,fill);
	vgaWriteStr(14*8,0,msg,0xDFDFDF,fill);
	vgaWriteStr(0,8,"Please restart your computer and contact os365dev.tk or write to kras.ivanova AT yandex.ru",LIGHT_RED,fill);
	log("[INFO] Writing last 50 log strings...");
	log("[HALT] Halting.");
	vgaWriteStr(0,16,"Last 50 system log messages:",LIGHT_GREY,BLACK);
	int i=lnum-((lnum<50) ? lnum : 50);
	for(int j=0;i<lnum;i++,j++)
	{
		vgaWriteStr(0,24+j*8, logs[i], LIGHT_GREY, fill);
	}
//vgaWriteStr(240,24,itoa(eax),LIGHT_RED,BLACK);

	//displaying the regs
	for(;;)
	{
		asm("hlt");
	}
}
#endif
