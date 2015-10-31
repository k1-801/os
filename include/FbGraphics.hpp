#pragma once

#ifndef FBGRAPHICS_HPP
#define FBGRAPHICS_HPP

// All of the contents is DEPRECATED

#include "HCL/Std.hpp"
#include "Window.hpp"
#include "mboot.h"

// from there - remove
typedef enum
{
    BLACK         = 0x000000,
    BLUE          = 0x0000EE,
    GREEN         = 0x00EE00,
    CYAN          = 0x33EE33,
    RED           = 0xEE0000,
    MAGENTA       = 0x770077,
    BROWN         = 0x964B00,
    LIGHT_GREY    = 0xAAAAAA,
    DARK_GREY     = 0x777777,
    LIGHT_BLUE    = 0x0000FF,
    LIGHT_GREEN   = 0x00FF00,
    LIGHT_CYAN    = 0x00FFFF,
    LIGHT_RED     = 0xFF0000,
    LIGHT_MAGENTA = 0xDD00DD,
    LIGHT_BROWN   = 0xFFFF00,
    WHITE         = 0xFFFFFF,
} colors;

// from io.h - remove
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long int qword;

// from there - remove
typedef struct
{
    byte
    gen_mis,
    seq[5],
    crt[25],
    gct[9],
    act[5];
} vgaregs_t;

extern size_t vgaCol;
extern size_t vgaRow;
extern const size_t scrH;
extern const size_t scrW;
extern word x;
extern word y;
extern bool textMode;
extern bool settedMode;
extern bool mSet;
extern const char* bitmap;
extern const char* a;
extern vbe_info_t vbeMode;

extern const char *roundLT;
extern const char *roundRT;
extern const char *roundLB;
extern const char *roundRB;

extern byte PAL16[48];

extern byte tbl_mod_txt8p[3];
extern byte tbl_mod_txt9p[3];
extern byte tbl_mod_gra16c[3];
extern byte tbl_mod_gra256c[3];

extern uint8_t *framebuffer;
extern uint8_t *vram;
extern uint32_t fbpitch;
extern uint8_t  fbbpp;
extern bool changed;

// Functions
void VGAWriteReg(byte set, byte index, byte value);
byte VGAReadReg(byte set, byte index);
void resetregs(vgaregs_t* regs);
void vgachangemode(vgaregs_t*regs);
void settextplane(void);
void setfontplane(void);
void VGASetPal(byte*pal,byte first,word num);
void VGAGetPal(byte*pal,byte first,word num);
void VGAGotoXY(byte x,byte y,byte w);
void VGAWhereXY(byte*x,byte*y,byte w);
void VGASetCursor(byte y,byte h);
void VGAGetCursor(byte*y,byte*h);
void VGACursor(byte e);
void VGASetFont(byte*fnt,byte ch,word first,word num);
void VGAGetFont(byte*fnt,byte ch,word first,word num);
void VGAWaitVBL(void);
byte VGAMode(byte m,word w,word h,byte o);
void VGAPix16(word x,word y,uint32_t color,word w,word h);

void vgaPutchar(char c,word x,word y,uint32_t fg,uint32_t bg, bool dnf=false);
void vgaWriteStr(uint64_t x, uint64_t y, const char * str, uint32_t fg, uint32_t bg);
void vgaWriteStr(word x,word y,const char * str,uint32_t fg,uint32_t bg, bool dnf);

void putpix(uint32_t color);
uint32_t colorMix(uint32_t c1, uint32_t c2);
void hLine(word x1,word y1,word length,uint32_t color);
void drawLine(word x1,word y1,word x2,word y2,uint32_t color);
void vLine(word x1,word y1,word length,uint32_t color);
void drawRect(word w,word h, word x_, word y_, uint32_t color);
void fillRect(word w,word h, word x_, word y_, uint32_t color);
void drawGradient(int x, int y, int x2, int y2, uint32_t c1, uint32_t c2,bool rev=false);
void drawBitmap(const char* bm, word x,word y,word width,word height,uint32_t bg,uint32_t c1,uint32_t c2,uint32_t c3,uint32_t c4,bool dnf=false);
void drawBitmap(const char* bm,word x,word y,word width,word height);
void setGraphicsMode();
void textModeOn();

void drawObj(Window*, uint32_t = LIGHT_GREY, uint32_t=LIGHT_BLUE);
void drawObj(Window*, bool);
void delWin(Window*);

#endif // FBGRAPHICS_HPP