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
//#include "cli.h"
#include "cmos.h"
#include "assert.h"
#include "klog.h"
//#include "sprites.h"
#define MAX_COMMANDS 100
#define paste(front,back) front ## back

#include "GoMenu.hpp"

//Semigraphics table.
bool fRun=true;
const char *logo = "\
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
const char* OS365Logo = "4444444444444444444444444444444444444444\
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
const char *mswpicon="0000000000000000\
0000000001110000\
0000000010001000\
0000000100400040\
0000000104004004\
0000111111110000\
0001111111111000\
0011111111111100\
0011111111111100\
0011111111111100\
0011111111111100\
0011111111111100\
0011111111111100\
0011111111111100\
0001111111111000\
0000111111110000\
";
const char *particon="0000000000000000\
0000000000000000\
0000000000000000\
0111111111111110\
0144442222333310\
0144442222333310\
0144442222333310\
0144442222333310\
0144442222333310\
0144442222333310\
0144442222333310\
0144442222333310\
0144442222333310\
0111111111111110\
0000000000000000\
0000000000000000\
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
	setIconVars(6,mswpicon,/*tNames[LANG_RUS][LC_NAME_MINESWEEPER]*/ "FIX IT",10,192);
	setIconVars(7,particon,/*tNames[LANG_RUS][LC_NAME_PIXART]*/ "FIX IT",10,222);

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
	unsigned char olds,oldm,oldh;
	drawLine(0,50,230,450,LIGHT_BROWN);
	int oldMin;
	do
	{
		read_rtc(); //update the time...
		//and print new time.
		;
		if(second!=olds&&second<60)
		olds++;
		//hour-=20;
		if(second>59)
		{
			second-=(second-10);
			
		}
		if(!get_update_in_progress_flag())
		{
		vgaWriteStr(clock.x+5,clock.y+21,itoa(oldh+3),MAGENTA,LIGHT_GREY);
		vgaWriteStr(clock.x+21,clock.y+21,":",MAGENTA,LIGHT_GREY);
		vgaWriteStr(clock.x+29,clock.y+21,itoa(oldm),MAGENTA,LIGHT_GREY);
		vgaWriteStr(clock.x+45,clock.y+21,":",MAGENTA,LIGHT_GREY);
		vgaWriteStr(clock.x+53,clock.y+21,itoa(olds),MAGENTA,LIGHT_GREY);
		}
				if(second<60)
				olds=second;
				if(minute!=oldm&&minute<60)
		oldm=minute;
						if(hour!=oldh&&hour<60)
		oldh=hour;
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
	vgaWriteStr(0,0,"System logs of OS365. Press X to exit.",WHITE,BLACK);
	char c=0;
	do
	{
		c=inb(0x60);
		i=0;
		for(int j=0;i<2048&&i<lnum;i++,j++)
		{
			vgaWriteStr(0,8+j*8,logs[i],WHITE,BLACK);
		}
	}
	while(c!=charToScancode('x'));
	if(currLang==LANG_RUS)
        setRusFonts();
	fRun=true;
	startZ(true);
}
#define WHEIGHT 217
#define WWIDTH 245
#define WCENTERX 100
#define WCENTERY 100
#define RIGHTW WCENTERX + WWIDTH - 5
#define LEFTW WCENTERX + 5
#define TOPW WCENTERY + 20
#define DOWNW WCENTERY + WHEIGHT - 50
//SYSTEM FUNCTION
char getScancode() {
	char c=0;
	while(1) {
		if(inb(0x60)!=c) {
			c=inb(0x60);
			if(c>0) return c;
		}
	}
}

// REWRITE THIS FUCKING SHIT AS FAST AS YOU CAN!!!
// STORE IN
// src/Static.cpp as const char*

//SPRITES
int en1[64] = { 0,0,0,0xFFFFFF,0xFFFFFF,0,0,0,
		0,0,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0,0,
		0,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0,
		0xFFFFFF,0xFFFFFF,0,0xFFFFFF,0xFFFFFF,0,0xFFFFFF,0xFFFFFF,
		0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,
		0,0,0xFFFFFF,0,0,0xFFFFFF,0,0,
		0,0xFFFFFF,0,0xFFFFFF,0xFFFFFF,0,0xFFFFFF,0,
		0xFFFFFF,0,0xFFFFFF,0,0,0xFFFFFF,0,0xFFFFFF };

int en2[88] = { 0,0,0xFFFFFF,0,0,0,0,0,0xFFFFFF,0,0,
		0,0,0,0xFFFFFF,0,0,0,0xFFFFFF,0,0,0,
		0,0,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0,0,
		0,0xFFFFFF,0xFFFFFF,0,0xFFFFFF,0xFFFFFF,0xFFFFFF,0,0xFFFFFF,0xFFFFFF,0,
		0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,
		0xFFFFFF,0,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0,0xFFFFFF,
		0xFFFFFF,0,0xFFFFFF,0,0,0,0,0,0xFFFFFF,0,0xFFFFFF,
		0,0,0,0xFFFFFF,0xFFFFFF,0,0xFFFFFF,0xFFFFFF,0,0,0 };

int en3[96] = { 0,0,0,0,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0,0,0,0,
		0,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0,
		0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,
		0xFFFFFF,0xFFFFFF,0xFFFFFF,0,0,0xFFFFFF,0xFFFFFF,0,0,0xFFFFFF,0xFFFFFF,0xFFFFFF,
		0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,
		0,0,0xFFFFFF,0xFFFFFF,0xFFFFFF,0,0,0xFFFFFF,0xFFFFFF,0xFFFFFF,0,0,
		0,0xFFFFFF,0xFFFFFF,0,0,0xFFFFFF,0xFFFFFF,0,0,0xFFFFFF,0xFFFFFF,0,
		0,0,0xFFFFFF,0xFFFFFF,0,0,0,0,0xFFFFFF,0xFFFFFF,0,0 };

int plr[91] = { 0,0,0,0,0,0,0x00EE00,0,0,0,0,0,0,
		0,0,0,0,0,0x00EE00,0x00EE00,0x00EE00,0,0,0,0,0,
		0,0,0,0,0,0x00EE00,0x00EE00,0x00EE00,0,0,0,0,0,
		0,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0,
		0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,
		0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,
		0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00,0x00EE00 };

//ARRAY OF BAD GUYS
int ens[55] = { 1,1,1,1,1,1,1,1,1,1,1,
		4,2,2,2,2,2,2,2,2,2,2,
		4,2,2,2,2,2,2,2,2,2,2,
		5,3,3,3,3,3,3,3,3,3,3,
		5,3,3,3,3,3,3,3,3,3,3 };

//WINDOW

//VARIABLES
int ex, ey, px, py, lives = 3, score, hiscore;
bool ifend = false;
float ali_spd, plr_spd;
window wnd(WHEIGHT, WWIDTH, WCENTERX, WCENTERY, "Space Invaders", 0);
//DRAW FUNCTIONS

void draw_aliens(int x, int y) {
	for(int i = 0; i < 33; i++) {
		if(ens[i] == 1) {
			drawBitmap((const char*)en1, x, y, 8, 8);
			x += 16;
		} else if(ens[i] == 4) {
			y += 18; x -= 160;
			drawBitmap((const char*)en2, x, y, 11, 8);
			x += 16;
		} else if(ens[i] == 2) {
			drawBitmap((const char*)en2, x, y, 11, 8);
			x += 16;
		} else if(ens[i] == 5) {
			y += 18; x -= 160;
			drawBitmap((const char*)en3, x, y, 12, 8);
			x += 16;
		} else if(ens[i] == 3) {
			drawBitmap((const char*)en3, x, y, 12, 8);
			x += 16;
		}
	}
}

void draw_player(int x, int y) {
	drawBitmap((const char*)plr, x, y, 13, 7);
}

void draw_score_lives() {
	vgaWriteStr(LEFTW, TOPW, "SCORE", 0, 0xFFFFFF);
	vgaWriteStr(WCENTERX + WWIDTH - 70, TOPW, "HI-SCORE", 0, 0xFFFFFF);
	vgaWriteStr(LEFTW + 10, TOPW + 10, itoa(score), 0, 0xFFFFFF);
	vgaWriteStr(RIGHTW - 30, TOPW + 10, itoa(hiscore), 0, 0xFFFFFF);
	vgaWriteStr(WCENTERX + 5, DOWNW + 45, itoa(lives), 0, 0xFFFFFF);
	for(int i = 0; i < lives; i++) {
		draw_player(px, py);
		px += 18;
	}
}

void game_over() {
	drawObj(wnd, 0, 0xEE0000);
	draw_aliens(ex, ey);
	draw_score_lives();
	vgaWriteStr(WCENTERX + 70, TOPW + 50, "GAME OVER", 0, 0xEE0000);
}

//MAIN FUNCTION
void spaceInv() {
	drawObj(wnd, 0, 0x0000EE);
	draw_score_lives();
	ali_spd = 0.01;
	plr_spd = 0.03;
	while(ey <= DOWNW) {
		if(getScancode() == 0x4B || px >= LEFTW) px -= plr_spd;
		else if(getScancode() == 0x4D || px <= RIGHTW) px += plr_spd;

		drawObj(wnd, 0, 0x0000EE);
		draw_aliens(ex, ey);
		draw_player(px, py);

		if(ex >= RIGHTW) { ifend = true; ey += 18; }
		else if(ex <= LEFTW) { ifend = false; ey += 18; }

		if(ifend == true) ex -= ali_spd;
		else if(ifend == false) ex += ali_spd;
	}
	game_over();
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
	//spaceInv();
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
//extern void mario();
void minesweeper()
{
	//mario();
	//asm("int $83");
	struct mswpEntry {
		int x;
		int y;
		union {
			bool isBomb;
			int num;
		}u;
	}entries[24][24];
	int count=0;
	int j=0;
	//srand(rdtsc());
	for(int i=0; i<22; i++)
	{
		for(j=0; j<22; j++,count++)
		{
			entries[j][i].x=j;
			entries[j][i].y=i;
			//if(rand()%6==0)
			//entries[j][i].u.isBomb=true;
		}
	}
	int posx=0, posy=0;
	drawmain();
	window mswp(225,226,100,100,/*tNames[LANG_RUS][LC_NAME_MINESWEEPER]*/ "FIX IT","");
	drawObj(mswp);
	hLine(mswp.x+5,mswp.y+21,200,BLACK);
	hLine(mswp.x+5+200,mswp.y+21,200,BLACK);
	vLine(mswp.x+5,mswp.y+21,200,BLACK);
	vLine(mswp.x+5,mswp.y+21+200,200,BLACK);
	for(int i=0; i<24*9; i+=9)
	hLine(mswp.x+5+i,mswp.y+21,200,BLACK);
	for(int j=0; j<24*9; j+=9)
	vLine(mswp.x+5,mswp.y+21+j,200,BLACK);
	char c=0;
	do
	{
		if(inb(0x60)!=c)
		{
			c=inb(0x60);
			if(c>0)
			{
                switch(c)
                {
                    case 0x4b:drawRect(9,9,mswp.x+5+posx*9,mswp.y+21+posy*9,BLACK);if(posx>0)posx--; drawRect(9,9,mswp.x+5+posx*9,mswp.y+21+posy*9,GREEN);break;
                    case 0x4d:drawRect(9,9,mswp.x+5+posx*9,mswp.y+21+posy*9,BLACK);if(posx<21)posx++; drawRect(9,9,mswp.x+5+posx*9,mswp.y+21+posy*9,GREEN);break;
                    case 0x50:drawRect(9,9,mswp.x+5+posx*9,mswp.y+21+posy*9,BLACK);if(posy<21)posy++; drawRect(9,9,mswp.x+5+posx*9,mswp.y+21+posy*9,GREEN);break;
                    case 0x48:drawRect(9,9,mswp.x+5+posx*9,mswp.y+21+posy*9,BLACK);if(posy>0)posy--; drawRect(9,9,mswp.x    +5+posx*9,mswp.y+21+posy*9,GREEN);break;
/*					case 0x39: if(entries[posx][posy].u.isBomb==true){sleep(5000);for(int i=0; i < 22; i++){for(int j=0; j<22; j++){if(entries[j][i].u.isBomb==true)vgaPutchar('0',mswp.x+5+j*9+1,mswp.y+21+i*9+1,0xFF0000,LIGHT_GREY);}}vgaWriteStr(mswp.x+5,mswp.y+21,tNames[LANG_RUS][LC_NAME_MINESWEEPER_GAMEOVER],0x87cefa,DARK_GREY);waitForKey(1); delWin(mswp); startZ(true);}else{fillRect(10,10,mswp.x+5+posx*9,mswp.y+21+posy*9,DARK_GREY);				}*/
                }
            }
        }
        drawRect(9,9,mswp.x+5+posx*9,mswp.y+21+posy*9,GREEN);
    }
    while(c!=1);
    delWin(mswp);
    startZ(true);
}
void pixArt()
{
	int posx=0, posy=0;
	drawmain();
	uint32_t modeColor=DARK_GREY,outlineColor=GREEN;
	bool erase=false;
	window part(910,550,100,100,/*tNames[LANG_RUS][LC_NAME_PIXART]*/ "FIX IT","");
	drawObj(part);
	again:
	drawRect(900,524,part.x+5,part.y+21,DARK_GREY);
	for(int i=0; i<900; i+=5)
	hLine(part.x+5+i,part.y+21,524,DARK_GREY);
	for(int j=0; j<525; j+=5)
	vLine(part.x+5,part.y+21+j,900,DARK_GREY);
	char c=0;
	do
	{
		if(inb(0x60)!=c)
		{
			c=inb(0x60);
			if(c>0)
			{
				switch(c)
				{
					case 0x40:if(!erase){erase=true;outlineColor=RED;}else{erase=false;outlineColor=GREEN;} break;
					case 0x4b:drawRect(5,5,part.x+5+posx*5,part.y+21+posy*5,DARK_GREY);if(posx>0)posx--; drawRect(5,5,part.x+5+posx*5,part.y+21+posy*5,outlineColor);break;
					case 0x4d:drawRect(5,5,part.x+5+posx*5,part.y+21+posy*5,DARK_GREY);if(posx<179)posx++; drawRect(5,5,part.x+5+posx*5,part.y+21+posy*5,outlineColor);break;
					case 0x50:drawRect(5,5,part.x+5+posx*5,part.y+21+posy*5,DARK_GREY);if(posy<104)posy++; drawRect(5,5,part.x+5+posx*5,part.y+21+posy*5,outlineColor);break;
					case 0x48:drawRect(5,5,part.x+5+posx*5,part.y+21+posy*5,DARK_GREY);if(posy>0)posy--; drawRect(5,5,part.x+5+posx*5,part.y+21+posy*5,outlineColor);break;
					case 0x39:if(!erase)fillRect(6,6,part.x+5+posx*5,part.y+21+posy*5,DARK_GREY); else fillRect(6,6,part.x+5+posx*5,part.y+21+posy*5,LIGHT_GREY); break;
					case 0x3C:{
							drawRect(900,524,part.x+5,part.y+21,LIGHT_GREY);
	for(int i=0; i<900; i+=5)
	hLine(part.x+5+i,part.y+21,524,LIGHT_GREY);
	for(int j=0; j<525; j+=5)
	vLine(part.x+5,part.y+21+j,900,LIGHT_GREY);
	waitForKey(0x1c);
	goto again;
					}
				}
			}
		}
		drawRect(5,5,part.x+5+posx*5,part.y+21+posy*5,outlineColor);
		
	}while(c!=1);
	delWin(part);
	startZ(true);
}
void authors()
{
	log("[USER] Started program: Authors");
	drawmain();
	//gets(0,0);
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
	GoMenu::main();
}
void help()
{
	log("[USER] Started program: Help");
	drawmain();
	window help(1000,500,10,30,tNames[LANG_RUS][LC_NAME_HELP],"");
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
				vgaWriteStr(0,j*8,"OS365 Authors and Developers Team",LIGHT_CYAN,BLACK);
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
				
				vgaWriteStr(0,j*8,"OS365 1.1.",LIGHT_CYAN,BLACK);
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

// This should be removed and reorganized as text driver
char translateTable[2][128];
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
    translateTable[LANG_ENG]['m']='m';
    translateTable[LANG_ENG]['p']='p';
    translateTable[LANG_RUS]['a']='f';
    translateTable[LANG_RUS]['o']='b';
    translateTable[LANG_RUS]['t']='3';
    translateTable[LANG_RUS]['g']='r';
    translateTable[LANG_RUS]['l']='z';
    translateTable[LANG_RUS]['c']='x';
    translateTable[LANG_RUS]['m']='c';
    translateTable[LANG_RUS]['p']='g';
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
                else
                {
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
			if(c==charToScancode(desktopTranslate('m')))
			{
				minesweeper();
			}
			if(c==charToScancode(desktopTranslate('p')))
			{
				pixArt();
			}
/*			if(c==0x43)
			{
				startCLI();
			}*/

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