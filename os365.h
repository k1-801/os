#ifndef __OS365_H
#define __OS365_H
#include "vgaterm.h"
#include "user.h"
#include "scrio.h"
#include "zbase.h"
#include "io.h"
#define nostartwin false
void cmd_handle(char * cmd)
{
	if(cmd == "zstart -nostartwin")
	{
		startZ(nostartwin);
		return;
	}
	else if(cmd == "zstart")
	{
		startZ(true);
	}
}
void shellStart()
{
	//kprint("OS365 1.0 is started.\nLoading shell...");
		//char *logo = "\
0000000000000000\
0000000001100000\
0000000001210000\
0000000012231000\
0000000012231000\
0000000132233100\
0000001332233100\
0000013332233310\
0000133322222310\
0000133222222210\
0000132222222310\
0001332222333310\
0001333223333310\
0001333333333100\
0001333333331000\
0000111111110000\
";
	//312
	//drawBitmap(logo,312,300,160,160,BLACK,BLUE,LIGHT_CYAN,3,0,4);
	//vgaWriteStr(312-4*8,309,"OS365 1.0.5",LIGHT_GREEN,BLACK);
	startZ(true);
	/*
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c == 28)
			{
				cmd_handle(cmd);
				kprint("\n >");
				goto skip;
			}
			if(c>0)
			{
				cmd[i] = scancode[c+1];
				terminal_putchar(scancode[c+1]);
			}
		}
		skip:
		nop();
		i++;
	}
	while(true);
	*/
}
#endif
