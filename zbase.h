#ifndef __ZBASE_H
#define __ZBASE_H
#include "graphics.h"
#include "scrio.h"
#include "locale.h"
byte BGCOLOR=3;
class window {
	public:
	size_t width;
	size_t height;
	size_t x;
	size_t y;
	const char * caption;
	const char * text;
	window(size_t width, size_t height, size_t x, size_t y, const char * caption, const char * text);
	//window(size_t width, size_t height, size_t x, size_t y, const wchar_t * caption, const char * text);
};
window::window(size_t width, size_t height, size_t x, size_t y, const char * caption, const char * text)
{
	this->width=width;
	this->height=height;
	this->x=x;
	this->y=y;
	this->caption=caption;
	this->text=text;
}
/*window::window(size_t width, size_t height, size_t x, size_t y, const wchar_t * caption, const char * text)
{
	this->width=width;
	this->height=height;
	this->x=x;
	this->y=y;
	this->caption=caption;
	this->text=text;
}*/
/*class Widget {
	public:
	size_t width;
	size_t height;
	size_t x;
	size_t y;
};*/
void printw(const char * msg, window wnd);
bool drawObj(window target,bool);
void z_init();
char *roundLT = "\
0000022222222222\
0002222222222222\
0022111111111111\
0221111111111111\
0221111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
";
char *roundRT = "\
2222222222200000\
2222222222222000\
1111111111112200\
1111111111111220\
1111111111111220\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
";
char *roundLB = "\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
2211111111111111\
0221111111111111\
0221111111111111\
0022111111111111\
0002222222222222\
0000022222222222\
";
char *roundRB = "\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111122\
1111111111111220\
1111111111111220\
1111111111112200\
2222222222222000\
2222222222200000\
";

bool drawObj(window target,bool noBtmCrn=true)
{
	fillRect(target.width,target.height,target.x,target.y,LIGHT_GREY);
	fillRect(target.width,16,target.x,target.y,LIGHT_BLUE);
	//drawRect(target.width,target.height,target.x,target.y,BLACK);
	//vLine(target.x,target.y,target.height,DARK_GREY);
	//vLine(target.x+target.width,target.y,target.height,DARK_GREY);
	//hLine(target.x,target.y+target.height,target.width,DARK_GREY);
	//hLine(target.x+target.width,target.y+target.height,target.width,DARK_GREY);
		vLine(target.x,target.y,target.width,DARK_GREY);
			vLine(target.x,target.y+target.height-1,target.width,DARK_GREY);
						hLine(target.x+1,target.y,target.height,DARK_GREY);
			
			hLine(target.x+target.width,target.y,target.height,DARK_GREY);
		vLine(target.x,target.y+1,target.width,DARK_GREY);
			vLine(target.x,target.y+target.height-2,target.width,DARK_GREY);
						hLine(target.x+2,target.y,target.height,DARK_GREY);
			
			hLine(target.x+target.width-1,target.y,target.height,DARK_GREY);
			
	drawBitmap(roundLT,target.x+1,target.y,16,16,BGCOLOR,LIGHT_BLUE,DARK_GREY,0,0);
	drawBitmap(roundRT,target.x+1+target.width-16,target.y,16,16,BGCOLOR,LIGHT_BLUE,DARK_GREY,0,0);
	if(noBtmCrn)
	{
	drawBitmap(roundLB,target.x+1,target.y+target.height-16,16,16,BGCOLOR,LIGHT_GREY,DARK_GREY,0,0);
	drawBitmap(roundRB,target.x+1+target.width-16,target.y+target.height-16,16,16,BGCOLOR,LIGHT_GREY,DARK_GREY,0,0);
	}
	vLine(target.x,target.y+16,target.width,DARK_GREY);
	vgaWriteStr(target.x+5,target.y+5,target.caption,LIGHT_GREEN,LIGHT_BLUE);
	vgaWriteStr(target.x+5,target.y+21,target.text,MAGENTA,LIGHT_GREY);

}
void delWin(window wnd)
{
	fillRect(wnd.width,wnd.height,wnd.x,wnd.y,BGCOLOR);
	/*int i=0,j=0;
	while(i<wnd.height)
	{
		while(j<wnd.width)
		{
			VGAPix16(wnd.x+j,wnd.y+i,BGCOLOR,640,480);
			j++;
		}
		i++;
	}*/
}
void drawmain()
{
	//"OS365 Kernel 1.0.3, Z Window System 1.1.0.                                              "
	//"Press left CTRL to display main menu, or F1 to show help.                               "
	vgaWriteStr(0,0,tNames[LANG_RUS][LC_NAME_MAINTOP],WHITE,LIGHT_BLUE);
	vgaWriteStr(0,471,tNames[LANG_RUS][LC_NAME_MAINBOTTOM],WHITE,LIGHT_BLUE);

}
void printw(const char * msg, window wnd)
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
