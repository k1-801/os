#include "../include/Window.hpp"

#include "../include/Static.hpp"

// I have no idea where should it be defined, so I redefined it temporarily
#define BGCOLOR BLACK

Window::Window(const char* _t, uint64_t _x, uint64_t _y, uint64_t _w, uint64_t _h)
{
    title  = _t;
    x      = _x;
    y      = _y;
    height = _h;
    width  = _w;
}

bool drawObj(Window* target, uint32_t color, uint32_t captColor)
{
    fillRect(target->width-32,target->height-32,target->x+16,target->y+16,color);
    fillRect(16,target->height-32,target->x,target->y+16,color);
    fillRect(16,target->height-32,target->x+(target->width-16),target->y+16,color);
    fillRect(target->width-32,16,target->x+16,target->y+(target->height-16),color);
    fillRect(target->width-32,16,target->x+16,target->y,captColor);

    //drawGradient(target->x,target->y,target->x+target->width,target->y+16,0x000000,0xFF0000);
    //drawRect(target->width,target->height,target->x,target->y,BLACK);
    //vLine(target->x,target->y,target->height,DARK_GREY);
    //vLine(target->x+target->width,target->y,target->height,DARK_GREY);
    //hLine(target->x,target->y+target->height,target->width,DARK_GREY);
    //hLine(target->x+target->width,target->y+target->height,target->width,DARK_GREY);

    vLine(target->x + 16,              target->y,                  target->width  - 32, DARK_GREY);
    vLine(target->x + 16,              target->y+target->height-1, target->width  - 32, DARK_GREY);
    hLine(target->x + 1,               target->y+16,               target->height - 32, DARK_GREY);
    hLine(target->x + target->width,   target->y+16,               target->height - 32, DARK_GREY);
    vLine(target->x + 16,              target->y+1,                target->width  - 32, DARK_GREY);
    vLine(target->x + 16,              target->y+target->height-2, target->width  - 32, DARK_GREY);
    hLine(target->x + 2,               target->y+16,               target->height - 32, DARK_GREY);
    hLine(target->x + target->width-1, target->y+16,               target->height - 32, DARK_GREY);

    drawBitmap(roundLT, target->x+1,target->y,                                     16 ,16, BGCOLOR, captColor, DARK_GREY, 0, 0, true);
    drawBitmap(roundRT, target->x+1+target->width-16, target->y,                   16, 16, BGCOLOR, captColor, DARK_GREY, 0, 0, true);
    drawBitmap(roundLB, target->x+1,                  target->y+target->height-16, 16, 16, BGCOLOR,     color, DARK_GREY, 0, 0, true);
    drawBitmap(roundRB, target->x+1+target->width-16, target->y+target->height-16, 16, 16, BGCOLOR,     color, DARK_GREY, 0, 0, true);

    vLine(target->x,target->y+16,target->width,DARK_GREY);
    vgaWriteStr(target->x+5,target->y+5,target->title, LIGHT_GREEN, captColor);
    //vgaWriteStr(target->x+5,target->y+21,target->text,MAGENTA,color);
}

bool drawObj(Window* target, bool noBtmCrn)
{
	
	fillRect(target->width-32,target->height-32,target->x+16,target->y+16,LIGHT_GREY);
	fillRect(16,target->height-32,target->x,target->y+16,LIGHT_GREY);
	fillRect(16,target->height-32,target->x+(target->width-16),target->y+16,LIGHT_GREY);
	fillRect(target->width-32,16,target->x+16,target->y+(target->height-16),LIGHT_GREY);
	fillRect(target->width-32,16,target->x+16,target->y,LIGHT_GREEN);
	//drawGradient(target->x,target->y,target->x+target->width,target->y+16,0x000000,0xFF0000);
	if(!noBtmCrn)
	{
		fillRect(target->width,16,target->x,target->y+(target->height-16),LIGHT_GREY);
		vLine(target->x,target->y+target->height-2,target->width-2,DARK_GREY);
		vLine(target->x,target->y+target->height-1,target->width-2,DARK_GREY);
		hLine(target->x+2,target->y+16,target->height-16,DARK_GREY);
		hLine(target->x+1,target->y+16,target->height-16,DARK_GREY);
        hLine(target->x+target->width,target->y+16,target->height-17,DARK_GREY);
			
        hLine(target->x+target->width-1,target->y+16,target->height-17,DARK_GREY);

	}
	//drawRect(target->width,target->height,target->x,target->y,BLACK);
	//vLine(target->x,target->y,target->height,DARK_GREY);
	//vLine(target->x+target->width,target->y,target->height,DARK_GREY);
	//hLine(target->x,target->y+target->height,target->width,DARK_GREY);
	//hLine(target->x+target->width,target->y+target->height,target->width,DARK_GREY);

    vLine(target->x+16,             target->y,                  target->width-32,  DARK_GREY);
    vLine(target->x+16,             target->y+target->height-1, target->width-32,  DARK_GREY);
    hLine(target->x+1,              target->y+16,               target->height-32, DARK_GREY);
    hLine(target->x+target->width,  target->y+16,               target->height-32, DARK_GREY);
    vLine(target->x+16,             target->y+1,                target->width-32,  DARK_GREY);
    vLine(target->x+16,             target->y+target->height-2, target->width-32,  DARK_GREY);
    hLine(target->x+2,              target->y+16,               target->height-32, DARK_GREY);
    hLine(target->x+target->width-1,target->y+16,               target->height-32, DARK_GREY);

    drawBitmap(roundLT,target->x+1,target->y,16,16,BGCOLOR, LIGHT_GREEN, DARK_GREY,0,0,true);
    drawBitmap(roundRT,target->x+1+target->width-16,target->y,16,16, BGCOLOR, LIGHT_GREEN, DARK_GREY,0,0,true);
    if(noBtmCrn)
    {
        drawBitmap(roundLB,target->x+1,                  target->y+target->height-16, 16, 16,BGCOLOR, LIGHT_GREY, DARK_GREY,0,0,true);
        drawBitmap(roundRB,target->x+1+target->width-16, target->y+target->height-16, 16, 16,BGCOLOR, LIGHT_GREY, DARK_GREY,0,0,true);
    }
    vLine(target->x,target->y+16,target->width,DARK_GREY);
    vgaWriteStr(target->x+5,target->y+5,target->title,LIGHT_BLUE,LIGHT_GREEN);
    //vgaWriteStr(target->x+5,target->y+21,target->text,MAGENTA,LIGHT_GREY);

}

void delWin(Window* target)
{
	fillRect(target->width, target->height, target->x, target->y, BGCOLOR);
}