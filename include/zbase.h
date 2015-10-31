#ifndef __ZBASE_H
#define __ZBASE_H

#include "FbGraphics.hpp"
#include "Window.hpp"
#include "scrio.h"
#include "locale.h"

#include "../include/Static.hpp"

uint32_t BGCOLOR=CYAN;

void printw(const char * msg, Window wnd);
void z_init();

void drawmain()
{
	//"OS365 Kernel 1.0.3, Z Window System 1.1.0.                                              "
	//"Press left CTRL to display main menu, or F1 to show help.                               "
	
	vgaWriteStr(0,0,tNames[LANG_RUS][LC_NAME_MAINTOP],WHITE,LIGHT_BLUE);
	vgaWriteStr(0,759,tNames[LANG_RUS][LC_NAME_MAINBOTTOM],WHITE,LIGHT_BLUE);

}
void printw(const char * msg, Window wnd)
{
	int line_n = 0;
	int oldx=wnd.x+5;
	int x_=wnd.x+5;
	for(int i; i != strlen(msg)*8; i+=8)
	{
		x_= x+5+i;
		if(msg[i] != '\n')
		{
			vgaPutchar(msg[i],x_,wnd.y+21+line_n*8,MAGENTA,LIGHT_GREY);
		}
		else
		{
			line_n+=8;
			x_=x;
		}
	}
}
void z_init()
{
	
}
#endif
