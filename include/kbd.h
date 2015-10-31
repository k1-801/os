#ifndef __KBD_H
#define __KBD_H
#include "io.h"
#include "FbGraphics.hpp"
void waitForKey(int key)
{
	char c;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
		}
		skip:
		int noop=0;
	}
	while(c!=key);
	return;
}
char* gets(word x,word y)
{
    char c;
    char* ret;
    int i = 0;
    bool caps = false, shift = false;
    do
    {
        if(inb(0x60)!=c)
        {
            c = inb(0x60);
            if(c == 0x0E)
            {
                if(x != 0)
                {
                    if(y != 0)
                    {
                        x = x - 8;
                        vgaPutchar(' ',x,y,MAGENTA,LIGHT_GREY);
                    }
                }
                else
                {
                    y = y - 8;
                    x = 639;
                }
                i--;
                continue;
            }
            if(c == 0x3A)
            {
                if(caps == false)
                    caps = true;
                else
                    caps = false;
                continue;
            }
            if(c == 0x2A)
            {
                shift=true;
                continue;
            }
            if(c == 0xAA)
            {
                shift=false;
                continue;
            }
            if(c>0)
            {
                if(caps == false)
                {
                    ret[i] = scancode[c+1];
                    vgaPutchar(scancode[c+1],x,y,MAGENTA,LIGHT_GREY);
                }
                else
                {
                    ret[i] = scancode[c+1+90];
                    vgaPutchar(scancode[c+1+90],x,y,MAGENTA,LIGHT_GREY);
                }
                if(shift == false)
                {
                    ret[i] = scancode[c+1];
                    vgaPutchar(scancode[c+1],x,y,MAGENTA,LIGHT_GREY);
                }
                else
                {
                   ret[i] = scancode[c+1+90];
                   vgaPutchar(scancode[c+1+90],x,y,MAGENTA,LIGHT_GREY);
                }
                i++; x += 8;
        }
    }
    }
    while(c!=28);
    return ret;
}
#endif
