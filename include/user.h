#ifndef __USER_H
#define __USER_H
#include "kbd.h"
#include "zbase.h"
#include "scrio.h"
#include "panic.h"
#include "io.h"
#include "graphics.h"
#include "mem.h"
#include "strfcn.h"
#include "locale.h"
#include "fs.h"
#include "cmos.h"
#include "assert.h"
#include "klog.h"
//#include "sprites.h"
#define MAX_COMMANDS 100
#define paste(front,back) front ## back
//Semigraphics table.
bool fRun=true;
							char *logo = "\
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
void drawWallpaper(){
	fillRect(768,759,-1,8,BLACK);
		drawGradient(768,7,1024,759,0x000000,0xFF0000);
	//for(uint32_t i=LIGHT_BROWN; i < 0xFF8000 && 768+i < 1024; i++)
	//hLine(768,7,752,i);
}
int charToScancode(char c)
{	
	int i = 0;
	while(scancode[i+1] != c)
	{
		i++;
	}
	return i;
}
char scancodetochar(int scan)
{
	return scancode[scan+1];
}
char OS365Logo[] = "4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444444444444444444444444\
4444444444444422244444422244444444444444\
4444444444444244424444244444444444444444\
4444444444444244424444422244444444444444\
4444444444444244424444444424444444444444\
4444444444444422244444422244444444444444\
4444444444444444444444444444444444444444\
4441111111144444111111114444411111111444\
4411444444114441144444441144411444444444\
4114444444411411444444444411411444444444\
1144444444411114444444444444411444444444\
4444444444411144441111111144441111144444\
4444444111141141111444441144444444114444\
4444444444411111444444444114444444411444\
1144444444411444444444444114444444411444\
4114444444411444444444441144444444114444\
4411444444111144444444411444114441144444\
4441111111144111111111144444411111444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444444444444444444444444444444444\
4444444444434444444444444444444444444444\
4444444444333444444444444444444444444444\
4444444443333344444344444444444444444444\
4444444433333334443334444444444444444444\
4444444333333333433333444444444444444444\
4444444333333333333333344444444444444444\
4444443333333333333333334444444444444444\
4444433333333333333333333444444444444444\
";
class icon
{
	public:
	const char* icon = "0000000000000000\
1111111111111111\
1000000000000001\
1001111111000001\
1011000001100001\
1110000000110001\
1000000000011001\
1000000000110001\
1000000001100001\
1000000001100001\
1000000001100001\
1000000000000001\
1000000001100001\
1000000001100001\
1000000000000001\
1111111111111111\
";
	const char* label = "Unnamed";
	word x, y;
	char key;
	void draw();
};
void icon::draw()
{
	//icon is 16x16
	drawBitmap(icon,x+15,y,16,16,BGCOLOR,LIGHT_GREY,LIGHT_GREEN,LIGHT_BLUE,LIGHT_RED,true);
	vgaWriteStr(x+3,y+16+3,label/* + "(" + key + ")"*/,WHITE,BGCOLOR,true);
	vLine(x+3,y+16+3+8+2,6,WHITE);
}
icon iconList[256];
void setIconVars(int iconNum, const char* icon, const char* label, word x, word y)
{
	iconList[iconNum].icon = icon;
	iconList[iconNum].label = label;
	iconList[iconNum].x = x;
	iconList[iconNum].y = y;
	iconList[iconNum].key = label[0]+7;
	iconList[iconNum].draw();
}
/*void setIconVars(int iconNum, char* label, word x, word y) //without icon setting
{
	iconList[iconNum].label = label;
	iconList[iconNum].x = x;
	iconList[iconNum].y = y;
	iconList[iconNum].key = label[0]+7;
	iconList[iconNum].icon = "0000000000000000\
1111111111111111\
1000000000000001\
1001111111000001\
1011000001100001\
1110000000110001\
1000000000011001\
1000000000110001\
1000000001100001\
1000000001100001\
1000000001100001\
1000000000000001\
1000000001100001\
1000000001100001\
1000000000000001\
1111111111111111\
";
	iconList[iconNum].draw();
}*/
void drawDesktop()
{
	const char *authorsicon = "0000000000000000\
0444400044404444\
0011140422204000\
0100010244024000\
0100410200424444\
0100010200420004\
0011100422200004\
0411100022204440\
0101010202020000\
0101010202020000\
1001001002002000\
0001000002000000\
0010100020200000\
0100010200020000\
0100010200020000\
1000001000002000\
";
	const char *langicon = "0000003330000000\
0000222233200000\
0002222332220000\
0003223322220000\
0023333222222000\
0222333222222200\
0222233222222200\
0222223322222200\
0222223332222200\
0222223333233300\
0032223333333000\
0003323330220000\
0003333332220000\
0000333322200000\
0000003320000000\
0000000000000000\
";
	const char *editicon = "0000000000000000\
0000000000000000\
0011100000000000\
0100010000000000\
0100001000000000\
0010001000000000\
0001000111111111\
0000100010000010\
0000010011111100\
0000101331001000\
0001111131110000\
0010000030100000\
0111111111000000\
0000000000000000\
0000000000000000\
0000000000000000\
";
	const char *graphicon = "0000000000000000\
0000000000022000\
0000000000222200\
0000000002222220\
0000000022222222\
0000000022222222\
0000000111110222\
0000001111100022\
0000001111100000\
0000011111000020\
0000011111000020\
0000111110000000\
0001111100200020\
0001111100000000\
0000111000002002\
0000000000000020\
";
	const char *infoicon = "0000000000000000\
0000000000000000\
0000111111110000\
0001333333331000\
0013333333333100\
0133333113333310\
0133333333333310\
0133333113333310\
0133333113333310\
0133333113333310\
0133333113333310\
0133333113333310\
0013333333333100\
0001333333331000\
0000111111110000\
0000000000000000\
";
const char *clockicon="0000000000000000\
0000001111100000\
0000011313110000\
0000111113111000\
0001311113113100\
0011111131111110\
0011111131111110\
0131111131111131\
0111111141111111\
0131111131111131\
0011111131111110\
0011111311111100\
0001311311131000\
0000111311111000\
0000011313110000\
0000001111100000\
";
	logo=langicon;
	//icon declarations started, type there
	setIconVars(0,authorsicon,"                  ",10,10);
	setIconVars(1,infoicon,"                  ",10,70);
	setIconVars(2,editicon,"                  ",10,100);
	setIconVars(3,graphicon,"                  ",10,40);
	setIconVars(4,langicon,"                  ",10,132);
	setIconVars(0,authorsicon,tNames[LANG_RUS][LC_NAME_AUTHORS],10,10);
	setIconVars(1,infoicon,tNames[LANG_RUS][LC_NAME_OSINFO],10,70);
	setIconVars(2,editicon,tNames[LANG_RUS][LC_NAME_EDITOR],10,100);
	setIconVars(3,graphicon,tNames[LANG_RUS][LC_NAME_GREDIT],10,40);
	setIconVars(4,langicon,tNames[LANG_RUS][LC_NAME_LANG],10,132);
	setIconVars(5,clockicon,tNames[LANG_RUS][LC_NAME_CLOCK],10,162);
	//vgaPutchar('ф',100,100,LIGHT_RED, BLACK);
//	setIconVars(2,consoleicon,"Console",10,70);
	
}
void startZ(bool startwin);
void reboot()
{
	uint8_t good=0x02;
	while(good & 0x02)
		good=inb(0x64);
	outb(0x64,0xFE); //pull the reset cpu pin
	for(;;)
	{
		asm("hlt"); //if it not worked, halt forever
	}
}
void fsinit();
void clock()
{
	log("[USER] Started program: Clock");
	drawmain();
	//drawWallpaper();
	bool endofmin=false;
	int minNum=0;
	window clock(75,35,20,25,tNames[LANG_RUS][LC_NAME_CLOCK],"");
	drawObj(clock);
	char c;
	drawLine(0,50,230,450,LIGHT_BROWN);
	int oldMin;
	do
	{
		read_rtc(); //update the time...
		//and print new time.
		;
		//hour-=20;
		if(second>59)
		{
			second-=(second-10);
			
		}
		if(!get_update_in_progress_flag())
		{
		vgaWriteStr(clock.x+5,clock.y+21,itoa(hour+3),MAGENTA,LIGHT_GREY);
		vgaWriteStr(clock.x+21,clock.y+21,":",MAGENTA,LIGHT_GREY);
		vgaWriteStr(clock.x+29,clock.y+21,itoa(minute),MAGENTA,LIGHT_GREY);
		vgaWriteStr(clock.x+45,clock.y+21,":",MAGENTA,LIGHT_GREY);
		vgaWriteStr(clock.x+53,clock.y+21,itoa(second),MAGENTA,LIGHT_GREY);
		}
		
		//vgaWriteStr(clock.x+5,clock.y+21,__TIME__,MAGENTA,LIGHT_GREY);
		if(inb(0x60)!=c)
		{                       
			c = inb(0x60);
			if(c>0)
			{
				if(c==1)
				{
					delWin(clock);
					startZ(true);
				}
			}
		}
	}
	while(c!=1);
}
void showLogs()
{
	setupFonts();
	int i=0;
	//int 
	log("[USER] Started program: Log Viewer");
	fillRect(1024,768,0,0,BLACK);
	vgaWriteStr(0,0,"System logs of " QUOTATE(DISTNAME) ". Press X to exit.",WHITE,BLACK);
	char c=0;
	do
	{
		c=inb(0x60);
		i=0;
		for(int j=0;i<2048&&i<lnum;i++,j++)
		{
			vgaWriteStr(0,8+j*8,logs[i],WHITE,BLACK);
		}
	}while(c!=charToScancode('x'));
	if(currLang==LANG_RUS)
	setRusFonts();
	fRun=true;
	startZ(true);
}
void textEdit()
{
	log("[USER] Started program: Text Editor");
	drawmain();
	//drawWallpaper();
	int curposX = 0;
	int curposY = 1;
	int charNum = 0;
	int tfNum = 0;
	bool caps = false;
	char c;
	window editor(1000,600,10,10,tNames[LANG_RUS][LC_EDITORTITLE],"");
	drawObj(editor);
	//drawBitmap(fatalerror,15,16,16,16,BLACK,LIGHT_GREY,LIGHT_GREEN,LIGHT_BLUE,RED);
	vgaWriteStr(editor.x+5,editor.y+21,tNames[LANG_RUS][LC_EDITORTIPS],MAGENTA,LIGHT_GREY);
	//showLogs();
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
/*			if(c == 0x3D)
			{
				int i = 0;
				char * fn;
				do
				{
					if(inb(0x60)!=c)
					{	
						c = inb(0x60);
						if(c>0)
						{
							if(caps == false)
							{
							terminal_putchar(scancode[c+1]);
							fn[i] = scancode[c+1];
							}
							else
							{
							terminal_putchar(scancode[c+1+90]);
							fn[i] = scancode[c+1+90];
							}
						}
					}
					nop();
					i++;
				} while(c!=28);
				textFiles[tfNum].filename = fn;
				tfNum++;
				kprint("YEEES");
			}*/
			if(c == 0x0E)
			{
				
				if(curposX != 0)
				{
					if(curposY != 0)
					{
						curposX = curposX - 8;
						goToPos(terminal_column-1,terminal_row);
						vgaPutchar(' ',curposX+editor.x+5,curposY+editor.y+29,MAGENTA,LIGHT_GREY);
												//vgaPutchar(' ',curposX+editor.x+5+8,curposY+editor.y+29,MAGENTA,LIGHT_GREY);
						goToPos(terminal_column-1,terminal_row);
						charNum--;
					}
				}
				else
				{
					curposY-=8;
					curposX = 990;
					goToPos(editor.x+1+curposX,editor.y+3+curposY);
															//hLine(editor.x+5+curposX+10,editor.y+21+curposY+7,8,BLACK);
				}
																				//hLine(editor.x+5+curposX+10,editor.y+21+curposY+7,8,BLACK);
				goto skip2;
			}
			if(c == 0x3A)
			{
				if(caps == false)
				caps = true;
				else
				caps = false;
				goto skip2;
			}
			if(c == 0xAA)
			{
				caps = false;
				continue;
			}
			if(c == 0x2A)
			{
				caps = true;
				continue;
			}
			if(c == 28)
			{
								//hLine(editor.x+5+curposX+10,editor.y+21+curposY+7,8,BLACK);
				curposY = curposY+8;
				curposX = 0;
				goToPos(editor.x+1+curposX,editor.x+2+curposY);
				goto skip2;
			}
			if(c>0)
			{
								//hLine(editor.x+5+curposX+10,editor.y+21+curposY+7,8,BLACK);
				if(caps == false)
				vgaPutchar(scancode[c+1],curposX+editor.x+5,curposY+editor.y+29,MAGENTA,LIGHT_GREY);
				else
				vgaPutchar(scancode[c+1+90],curposX+editor.x+5,curposY+editor.y+29,MAGENTA,LIGHT_GREY);
				curposX = curposX + 8;
			}
		}
		skip2:
		nop();
		
	} while(c!=0x3F);
	delWin(editor);
	startZ(true);
}
void displayColorSet(word x, word y)
{
	for(int i = 0; i < 16; i++)
	{
		fillRect(1,16,x+(i*9),y,i);
	}
}
void about()
{
	log("[USER] Started program: OS Info");
	drawmain();
	//drawWallpaper();
	window info(540,80,40,30,tNames[LANG_RUS][LC_NAME_OSINFO],"");
	drawObj(info);
	//displayColorSet(info.x+5+2, info.y+21+35);
	//assert(0==1);
	vgaWriteStr(info.x+5,info.y+21,tNames[LANG_RUS][LC_ABOUTTIPS],MAGENTA,LIGHT_GREY);
		//read_rtc(); //update the time...
		//and print new time.
		
		//vgaWriteStr(info.x+5,info.y+21,itoa(hour-1),MAGENTA,LIGHT_GREY);
		//vgaWriteStr(info.x+21,info.y+21,":",MAGENTA,LIGHT_GREY);
		//vgaWriteStr(info.x+29,info.y+21,itoa(minute),MAGENTA,LIGHT_GREY);
		//vgaWriteStr(info.x+45,info.y+21,":",MAGENTA,LIGHT_GREY);
		//vgaWriteStr(info.x+53,info.y+21,itoa(second),MAGENTA,LIGHT_GREY);
	drawBitmap(OS365Logo,40+150+5,30+32,40,40,BLACK,LIGHT_BROWN,LIGHT_GREY,BROWN,0);
	drawBitmap(OS365Logo,40+150+40+5,30+32,40,40,BLACK,LIGHT_BROWN,LIGHT_GREY,BROWN,BLACK);
	waitForKey(0x2D);
	//clock();
	delWin(info);
	startZ(true);
}
void authors()
{
	log("[USER] Started program: Authors");
	drawmain();
	//drawWallpaper();
	window authors(500,120,40,30,tNames[LANG_RUS][LC_NAME_AUTHORS],"");
	drawObj(authors);
	vgaWriteStr(authors.x+5,authors.y+21,tNames[LANG_RUS][LC_AUTHORSTIPS1],MAGENTA,LIGHT_GREY);
	vgaWriteStr(authors.x+5,authors.y+29,tNames[LANG_RUS][LC_AUTHORSTIPS2],MAGENTA,LIGHT_GREY);
	vgaWriteStr(authors.x+5,authors.y+37,tNames[LANG_RUS][LC_AUTHORSTIPS3],MAGENTA,LIGHT_GREY);
	vgaWriteStr(authors.x+5,authors.y+45,tNames[LANG_RUS][LC_AUTHORSTIPS4],MAGENTA,LIGHT_GREY);
	//char *test="";
	//sprintf(test,"TEst of %s testest %d","sprintf",12345678976);
	//vgaWriteStr(authors.x+5,authors.y+45,test,MAGENTA,LIGHT_GREY);
	drawBitmap(OS365Logo,40+150+5,30+32+45,40,40,BLACK,LIGHT_BROWN,LIGHT_GREY,BROWN,0);
	drawBitmap(OS365Logo,40+150+40+5,30+32+45,40,40,BLACK,LIGHT_BROWN,LIGHT_GREY,BROWN,BLACK);
	waitForKey(0x2D);
	delWin(authors);
	startZ(true);
}
void calc()
{
/*		drawmain();
		window calc(180,320,50,50,tNames[LANG_RUS][LC_NAME_CALC],"");
		drawObj(calc);
		vgaWriteStr(calc.x+5,calc.y+21,"Enter the expression: ",MAGENTA,LIGHT_GREY);
		char c=0, *op1,*op2,op=0;
		int iop1,iop2,result;
		char *input;
		int i=0;
		do
		{
			if(inb(0x60)!=c)
			{
				c = inb(0x60);
				if(c>0)
				{
					if(c==21)
					{
						int j;
						//now sort the numbers and do the actions
						for(j=0; input[j]>='0'&&input[j]<='9'; j++)
						{
							op1[j]=input[j];
						}
						op=input[j];
						for(; input[j]>='0'&&input[j]<='9'; j++)
						{
							op2[j]=input[j];
						}
						iop1=atoi(op1);
						iop2=atoi(op2);
						switch(op)
						{
							case '+': result=iop1+iop2; break;
							case '-': result=iop1-iop2; break;
							case 'x': result=iop1*iop2; break;
							case '/': if(iop2!=0)result=iop1+iop2; else result=0; break;

						}
						vgaWriteStr(calc.x+5,calc.y+370,itoa(result),MAGENTA,LIGHT_GREY);
					}
					else {
						//if(c>=charToScancode('0')&&c<=charToScancode('9')||c==charToScancode('+')||c==charToScancode('-')||c==charToScancode('x')||c==charToScancode('/'))
						//{
							input[i]=scancodetochar(c);
							vgaPutchar(input[i],calc.x+5+i*8,calc.y+29,MAGENTA,LIGHT_GREY);
							i++;
						//}
					}
				}
			}
		}
		while(c!=1);*/
}
/* The stub for kbd input.
	char c;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c>0)
			{
				
			}
		}
	}
	while(c!=1);
*/
//10 is the first non-num char
/*void presentation()
{
	drawmain();
	window presentation(366,300,50,50,"365 Present. OS365 Office 1.0.0. Esc to exit.","");
	drawObj(presentation);
	word x = 0;
	word y = 0;
	char c;
	char slides[20][180*160];
	int slideN = 1;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			switch(c)
			{
			case 0x48: if(y > 0) y--; break;
			case 0x50: if(y <= 160) y++; break;
			case 0x4D: if(x <= 180) x++; break;
			case 0x4B: if(x >= 0) x--; break;
			case 0x49: if(slides > 1){ slideN--; drawObj(presentation); drawBitmap(slides[slideN], presentation.x+5,presentation.y+21,180,160,LIGHT_GREY,BLACK,0,0,0); }
			case 0x51: if(slides < 20){ slideN++; drawObj(presentation); drawBitmap(slides[slideN], presentation.x+5,presentation.y+21,180,160,LIGHT_GREY,BLACK,0,0,0); }
			case 0x39: VGAPix16(presentation.x+5+x,presentation.y+21+y,BLACK,640,480); slides[slideN][y*180+x] = '1'; break;
			}
		}
	}
	while(c!=1);
	delWin(presentation);
	startZ(true);
}
*/
//pgup 0xc9\
pgdn 0xd1
void wallColor()
{
	log("[USER] Started program: Wallpaper Changing");
	drawmain();
	//drawWallpaper();
	window wcolor(430,40,20,20,tNames[LANG_RUS][LC_NAME_WPCOLOR],"");
	drawObj(wcolor);
	vgaWriteStr(wcolor.x+5,wcolor.y+21,tNames[LANG_RUS][LC_NAME_WPTIP],MAGENTA,LIGHT_GREY);
	calc();
	char c;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c>0)
			{
				switch(scancodetochar(c))
				{
				case '0': BGCOLOR=0; log("[USER] Wallpaper changed to Black"); fRun=true; delWin(wcolor); startZ(true);
				case '1': BGCOLOR=BLUE; log("[USER] Wallpaper changed to Blue"); fRun=true; delWin(wcolor); startZ(true);
				case '2': BGCOLOR=GREEN; log("[USER] Wallpaper changed to Green"); fRun=true; delWin(wcolor); startZ(true);
				case '3': BGCOLOR=CYAN; log("[USER] Wallpaper changed to Cyan"); fRun=true; delWin(wcolor); startZ(true);
				case '4': BGCOLOR=RED; log("[USER] Wallpaper changed to Red"); fRun=true; delWin(wcolor); startZ(true);
				case '5': BGCOLOR=MAGENTA; log("[USER] Wallpaper changed to Magenta"); fRun=true; delWin(wcolor); startZ(true);
				case '6': BGCOLOR=BROWN; log("[USER] Wallpaper changed to Brown"); fRun=true; delWin(wcolor); startZ(true);
				case '7': BGCOLOR=LIGHT_GREY; log("[USER] Wallpaper changed to Light Grey"); fRun=true; delWin(wcolor); startZ(true);
				case '8': BGCOLOR=DARK_GREY; log("[USER] Wallpaper changed to Dark Grey"); fRun=true; delWin(wcolor); startZ(true);
				case '9': BGCOLOR=LIGHT_BLUE; log("[USER] Wallpaper changed to Light Blue"); fRun=true; delWin(wcolor); startZ(true);
				case 'a': BGCOLOR=LIGHT_GREEN; log("[USER] Wallpaper changed to Light Green"); fRun=true; delWin(wcolor); startZ(true);
				case 'b': BGCOLOR=LIGHT_CYAN; log("[USER] Wallpaper changed to Light Cyan"); fRun=true; delWin(wcolor); startZ(true);
				case 'c': BGCOLOR=LIGHT_RED; log("[USER] Wallpaper changed to Light Red"); fRun=true; delWin(wcolor); startZ(true);
				case 'd': BGCOLOR=LIGHT_MAGENTA; log("[USER] Wallpaper changed to Light Magenta"); fRun=true; delWin(wcolor); startZ(true);
				case 'e': BGCOLOR=LIGHT_BROWN; log("[USER] Wallpaper changed to Yellow"); fRun=true; delWin(wcolor); startZ(true);
				case 'f': BGCOLOR=WHITE; log("[USER] Wallpaper changed to White"); fRun=true; delWin(wcolor); startZ(true);
				}
			}
		}
	}
	while(c!=1);
}
void graphicsEdit()
{
	log("[USER] Started program: Graphics Editor");
	drawmain();
	//drawWallpaper();
	window os365brush(1000,600,20,50,tNames[LANG_RUS][LC_GREDITTITLE],"");
	drawObj(os365brush);
	word x = 0;
	word y = 0;
	uint8_t color=0;
	char c;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			switch(c)
			{
			case 0x48: if(y > 0) y--; break;
			case 0x50: if(y <= 571) y++; break;
			case 0x4D: if(x <= 990) x++; break;
			case 0x4B: if(x >= 0) x--; break;
			case 0x39: VGAPix16(os365brush.x+5+x,os365brush.y+21+y,color,640,480); break;
			case 0x2E: 			
			do{
				if(inb(0x60)!=c){
					c=inb(0x60);
					switch(scancodetochar(c))
					{
						case '0': color=0; break;
						case '1': color=1; break;
						case '2': color=2; break;
						case '3': color=3; break;
						case '4': color=4; break;
						case '5': color=5; break;
						case '6': color=6; break;
						case '7': color=7; break;
						case '8': color=8; break;
						case '9': color=9; break;
						case 'A': color=10; break;
						case 'B': color=11; break;
						case 'C': color=12; break;
						case 'D': color=13; break;
						case 'E': color=14; break;
						case 'F': color=15; break;
					}
				}
			}while(c!=1);
			}
		}
	}
	while(c!=1);
	delWin(os365brush);
	startZ(true);
}
void gomenu()
{
	log("[USER] Started program: Go! Menu");
	window goMenu(148,200,0,768-208,tNames[LANG_RUS][LC_NAME_GOMENU],"");
	drawObj(goMenu,false);
	//drawWallpaper();
	int selection = 1;
	//assert(0==1);
	vgaWriteStr(goMenu.x+5,goMenu.y+21,tNames[LANG_RUS][LC_NAME_OSINFO],MAGENTA,LIGHT_GREY);
	vgaWriteStr(goMenu.x+5,goMenu.y+29,tNames[LANG_RUS][LC_NAME_AUTHORS],MAGENTA,LIGHT_GREY);
	vgaWriteStr(goMenu.x+5,goMenu.y+37,tNames[LANG_RUS][LC_NAME_PANIC],MAGENTA,LIGHT_GREY);
	vgaWriteStr(goMenu.x+5,goMenu.y+45,tNames[LANG_RUS][LC_NAME_REBOOT],MAGENTA,LIGHT_GREY);
	vgaWriteStr(goMenu.x+5,goMenu.y+53,tNames[LANG_RUS][LC_NAME_EDITOR],MAGENTA,LIGHT_GREY);
	vgaWriteStr(goMenu.x+5,goMenu.y+61,tNames[LANG_RUS][LC_NAME_GREDIT],MAGENTA,LIGHT_GREY);
	vgaWriteStr(goMenu.x+5,goMenu.y+69,tNames[LANG_RUS][LC_NAME_CLOCK],MAGENTA,LIGHT_GREY);
	vgaWriteStr(goMenu.x+5,goMenu.y+77,tNames[LANG_RUS][LC_NAME_LVIEW],MAGENTA,LIGHT_GREY);
	//vgaWriteStr(goMenu.x+5,goMenu.y+77,"CLOCK",MAGENTA,LIGHT_GREY);
	vgaWriteStr(goMenu.x+5,goMenu.y+21,tNames[LANG_RUS][LC_NAME_OSINFO],LIGHT_GREY,MAGENTA);
	//printw("test\ntewlines\nmasrkovka\nkostya puknum",goMenu);
	char c;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c==0x48)
			{
				if(selection!=1)
				{
					selection--;
					vgaWriteStr(goMenu.x+5,goMenu.y+21,tNames[LANG_RUS][LC_NAME_OSINFO],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+29,tNames[LANG_RUS][LC_NAME_AUTHORS],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+37,tNames[LANG_RUS][LC_NAME_PANIC],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+45,tNames[LANG_RUS][LC_NAME_REBOOT],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+53,tNames[LANG_RUS][LC_NAME_EDITOR],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+61,tNames[LANG_RUS][LC_NAME_GREDIT],MAGENTA,LIGHT_GREY);
					//vgaWriteStr(goMenu.x+5,goMenu.y+69,tNames[LANG_RUS][LC_NAME_WPCOLOR],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+69,tNames[LANG_RUS][LC_NAME_CLOCK],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+77,tNames[LANG_RUS][LC_NAME_LVIEW],MAGENTA,LIGHT_GREY);
					switch(selection)
					{
					case 1: vgaWriteStr(goMenu.x+5,goMenu.y+21,tNames[LANG_RUS][LC_NAME_OSINFO],LIGHT_GREY,MAGENTA); break;
					case 2: vgaWriteStr(goMenu.x+5,goMenu.y+29,tNames[LANG_RUS][LC_NAME_AUTHORS],LIGHT_GREY,MAGENTA); break;
					case 3: vgaWriteStr(goMenu.x+5,goMenu.y+37,tNames[LANG_RUS][LC_NAME_PANIC],LIGHT_GREY,MAGENTA); break;
					case 4: vgaWriteStr(goMenu.x+5,goMenu.y+45,tNames[LANG_RUS][LC_NAME_REBOOT],LIGHT_GREY,MAGENTA); break;
					case 5: vgaWriteStr(goMenu.x+5,goMenu.y+53,tNames[LANG_RUS][LC_NAME_EDITOR],LIGHT_GREY,MAGENTA); break;
					case 6: vgaWriteStr(goMenu.x+5,goMenu.y+61,tNames[LANG_RUS][LC_NAME_GREDIT],LIGHT_GREY,MAGENTA); break;
					//case 7: vgaWriteStr(goMenu.x+5,goMenu.y+69,tNames[LANG_RUS][LC_NAME_WPCOLOR],LIGHT_GREY,MAGENTA);break;
					case 7: vgaWriteStr(goMenu.x+5,goMenu.y+69,tNames[LANG_RUS][LC_NAME_CLOCK],LIGHT_GREY,MAGENTA);break;
					case 8: vgaWriteStr(goMenu.x+5,goMenu.y+77,tNames[LANG_RUS][LC_NAME_LVIEW],LIGHT_GREY,MAGENTA);

					}
				}
			}
			if(c==0x50)
			{
				if(selection<8)
				{
					selection++;
					vgaWriteStr(goMenu.x+5,goMenu.y+21,tNames[LANG_RUS][LC_NAME_OSINFO],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+29,tNames[LANG_RUS][LC_NAME_AUTHORS],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+37,tNames[LANG_RUS][LC_NAME_PANIC],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+45,tNames[LANG_RUS][LC_NAME_REBOOT],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+53,tNames[LANG_RUS][LC_NAME_EDITOR],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+61,tNames[LANG_RUS][LC_NAME_GREDIT],MAGENTA,LIGHT_GREY);
					//vgaWriteStr(goMenu.x+5,goMenu.y+69,tNames[LANG_RUS][LC_NAME_WPCOLOR],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+69,tNames[LANG_RUS][LC_NAME_CLOCK],MAGENTA,LIGHT_GREY);
					vgaWriteStr(goMenu.x+5,goMenu.y+77,tNames[LANG_RUS][LC_NAME_LVIEW],MAGENTA,LIGHT_GREY);
					switch(selection)
					{
					case 1: vgaWriteStr(goMenu.x+5,goMenu.y+21,tNames[LANG_RUS][LC_NAME_OSINFO],LIGHT_GREY,MAGENTA); break;
					case 2: vgaWriteStr(goMenu.x+5,goMenu.y+29,tNames[LANG_RUS][LC_NAME_AUTHORS],LIGHT_GREY,MAGENTA); break;
					case 3: vgaWriteStr(goMenu.x+5,goMenu.y+37,tNames[LANG_RUS][LC_NAME_PANIC],LIGHT_GREY,MAGENTA); break;
					case 4: vgaWriteStr(goMenu.x+5,goMenu.y+45,tNames[LANG_RUS][LC_NAME_REBOOT],LIGHT_GREY,MAGENTA); break;
					case 5: vgaWriteStr(goMenu.x+5,goMenu.y+53,tNames[LANG_RUS][LC_NAME_EDITOR],LIGHT_GREY,MAGENTA); break;
					case 6: vgaWriteStr(goMenu.x+5,goMenu.y+61,tNames[LANG_RUS][LC_NAME_GREDIT],LIGHT_GREY,MAGENTA); break;
					//case 7: vgaWriteStr(goMenu.x+5,goMenu.y+69,tNames[LANG_RUS][LC_NAME_WPCOLOR],LIGHT_GREY,MAGENTA);break;
					case 7: vgaWriteStr(goMenu.x+5,goMenu.y+69,tNames[LANG_RUS][LC_NAME_CLOCK],LIGHT_GREY,MAGENTA);break;
					case 8: vgaWriteStr(goMenu.x+5,goMenu.y+77,tNames[LANG_RUS][LC_NAME_LVIEW],LIGHT_GREY,MAGENTA);

					}
				}
			}
		}
	}
	while(c!=28);
	delWin(goMenu);
	drawWallpaper();
	drawDesktop();
	switch(selection)
	{
	case 1:
	{
	about(); break;
	}
	case 2:
	{
	authors(); break;
	}
	case 3:
	{
	panic("Test panic");
	}
	case 4:
	{
	reboot(); break;
	}
	case 5:
	{
	textEdit(); break;
	}
	case 6:
	{
	graphicsEdit(); break;
	}
	case 7:
	{
	clock(); break;
	}
	case 8:
	{
	showLogs(); break;
	}
	case 9:
	{
	showLogs(); break;
	}
	}
}
void help()
{
	log("[USER] Started program: Help");
	drawmain();
	window help(639,460,10,30,tNames[LANG_RUS][LC_NAME_HELP],"");
	drawObj(help);
	int i;
	//vgaWriteStr(help.x+5,help.y+21,"Welcome to OS365 1.0.4\nThe OS nW",MAGENTA,LIGHT_GREY);
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP1],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP2],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP3],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP4],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP5],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP6],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP7],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP8],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP9],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP10],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP11],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP12],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP13],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP14],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP15],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP16],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP17],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP18],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP19],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP20],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP21],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP22],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP23],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP24],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP25],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP26],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP27],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP28],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP29],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP30],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP31],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP32],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP33],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP34],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP35],MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,tNames[LANG_RUS][LC_NAME_HELP36],MAGENTA,LIGHT_GREY);
	//vgaWriteStr(help.x+5,help.y+i*8+21,"V razrabotke. Budet v 1.0.5 ili v 1.0.6. Naymite Wnter dlx vwhoda.",MAGENTA,LIGHT_GREY);
/*	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Thanks for getting OS365 1.0.4. It's a global update.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Changelog",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Rounded windows borders.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"For new users:",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Control buttons:",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"CTRL - main menu.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"ESC - exit program.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Wallpaper changing.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Wallpaper changing.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Wallpaper changing.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Wallpaper changing.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Wallpaper changing.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Wallpaper changing.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Wallpaper changing.",MAGENTA,LIGHT_GREY);
	i++;
	vgaWriteStr(help.x+5,help.y+i*8+21,"Wallpaper changing.",MAGENTA,LIGHT_GREY);
	i++;
	*/
	char c=0;
	do
	{
		if(inb(0x60)!=c)
		{
			c=inb(0x60);
			if(c==28)
			break;
			if(c==0x3E)
			{
				fillRect(1024,768,0,0,BLACK);
				setupFonts();
				int oldlang=currLang;
				currLang=LANG_ENG;
				int j=0;
				vgaWriteStr(0,j*8,QUOTATE(DISTNAME)" Authors and Developers Team",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"Main OS Developer                                                Nikita Ivanov      (catnikita255)",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"Helped with big problems                                         Roman Zhikharevich (rzhikharevich)",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"Helped                                                           Artem Klimov       (xom4a2003)",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"Helped a lot with low-level services                             glauxosdever",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"Some ideas                                                       Mitrofan Iskra     (Monolit_Rex)",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"Old graphics mode code and text displaying                       Unsigned",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"Helped with VBE mode by giving link to Multiboot Specification   SapphireOS",LIGHT_CYAN,BLACK);
				j++;
				
				vgaWriteStr(0,j*8,"Thanks to a lot of OSDev users for helping when i am got stuck.",LIGHT_CYAN,BLACK);
				j++;
				
				vgaWriteStr(0,j*8,"I can't list their names, because it will be so big.",LIGHT_CYAN,BLACK);
				j++;
				
				vgaWriteStr(0,j*8, QUOTATE(DISTNAME) " " QUOTATE(DISTVERSION),LIGHT_CYAN,BLACK);
				j++;

				vgaWriteStr(0,j*8,"By Byte PowerSoft.",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"Made in 2015. Press Enter.",LIGHT_CYAN,BLACK);
				j++;

				/*vgaWriteStr(0,j*8,"",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"OS365 Authors and Developers Team",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"OS365 Authors and Developers Team",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"OS365 Authors and Developers Team",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"OS365 Authors and Developers Team",LIGHT_CYAN,BLACK);
				j++;
				vgaWriteStr(0,j*8,"OS365 Authors and Developers Team",LIGHT_CYAN,BLACK);
				j++;*/

				if(oldlang==LANG_RUS)
				{
					currLang=LANG_RUS;
					setRusFonts();
				}
				waitForKey(28);
				fRun=true;
				startZ(true);
			}
		}
	} while(c!=1);
	delWin(help);
	startZ(true);
}
char *translateTable[2][128];
char desktopTranslate(char c)
{
	return translateTable[currLang][c];
}
void setupDeskTranslations()
{
	translateTable[LANG_ENG]['a']='a';
	translateTable[LANG_ENG]['o']='o';
	translateTable[LANG_ENG]['t']='t';
	translateTable[LANG_ENG]['g']='g';
	translateTable[LANG_ENG]['l']='l';
	translateTable[LANG_ENG]['c']='c';
	translateTable[LANG_RUS]['a']='f';
	translateTable[LANG_RUS]['o']='b';
	translateTable[LANG_RUS]['t']='3';
	translateTable[LANG_RUS]['g']='r';
	translateTable[LANG_RUS]['l']='z';
	translateTable[LANG_RUS]['c']='x';

}
void startZ(bool startwin)
{
	BGCOLOR=0;
		drawWallpaper();
	setupDeskTranslations();
	if(fRun)
	log("[INFO] Z Window System is started or reloaded.");
	setupLocale();
	terminal_setcolor(COLOR_LIGHT_GREY + COLOR_BLACK);
	z_init();
	if(fRun)drawmain();//fillRect(1024,751,-1,8,BGCOLOR);
	fRun=false;
			drawmain();
		drawDesktop();
	char c;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c == 29)
			{
				gomenu();
			}
			if(c == charToScancode(desktopTranslate('a')))
			{
				authors();
			}
			if(c == charToScancode(desktopTranslate('o')))
			{
				about();
			}
			if(c == charToScancode(desktopTranslate('t')))
			{
				textEdit();
			}
			if(c == charToScancode(desktopTranslate('g')))
			{
				graphicsEdit();
			}
			if(c == charToScancode(desktopTranslate('l')))
			{
				if(currLang==LANG_RUS)
				{
				setupFonts();
				currLang=LANG_ENG;
				scancode="   1234567890-=^^qwertyuiop[]\n^asdfghjkl;'`  zxcvbnm,./^*^   ^^^^^^^^^^^^^^789-456+1230.^^   !@#$%^&*()_+^^QWERTYUIOP{}\n^ASDFGHJKL:'^  ZXCVBNM<>?^*^   ^^^^^^^^^^^^^^&*(_$%^+!@#)>^^";
				startZ(true);
				}
				else {
				setRusFonts();
				currLang=LANG_RUS;
				//scancode="  1234567890-=^jcukeng#\\zhq\n^fwvaproldyW'`  x$smitQbY/^*^   ^^^^^^^^^^^^^^789-456+1230.^^   !@#$%^&*()_+^^JCUKENG#\\ZHQ\n^FWVAPROLDYW:'^    X$SMITQBY?^*^   ^^^^^^^^^^^^^^&*(_$%^+!@#)>^^";
				startZ(true);
				}
			}
			if(c==0x3B)
			{
				help();
			}
			if(c==charToScancode(desktopTranslate('c')))
			{
				clock();
			}
		}
	}    
	while(true);
//	waitForKey(29);
}
/*void zwin_start()
{
	window test(70,20,5,4,"OS365 ",""); //creating window
	window test2(20,10,50,1,"Multi-windows","");
	z_init();
	terminal_setcolor(0x85);
	goToPos(0,0);
	//kprint("   OS365 Kernel 0.1, Z Window System 0.1.                     Pre-alpha 0.1     ");
	drawObj(test);
	terminal_setcolor(46);
	drawObj(test2);
	terminal_setcolor(30);
	
	//printw("OS365 Z Window System is working.\nNewlines is also working.\nTODO:\n    1. Write keyboard driver\n2. Write mouse driver.\n3. Add graphic mode changing.\nOS365 is a small OS in pre-alpha stage, written almost fully in C++,\nusing ASM only for 2 functions and the kernel loader. The bootloader\nis GRUB. ", test);
	terminal_setcolor(46);
	printw("Second window\n      Multiwindowing is\nfully working.\nCool!", test2);
	goToPos(0,24);
	//kprint(" OS365 0.1                                                                      ");
}*/
#endif
