#pragma once

#ifndef FBGRAPHICS_HPP
#define FBGRAPHICS_HPP

// All of the contents is DEPRECATED

#include "HCL/Std.hpp"
#include "Window.hpp"
#include "mboot.h"

//constants
#define min(a,b) (a<b) ? a : b
#define VGA_CRT 0              //CRT set
#define VGA_ACT 1              //attribute controller set
#define VGA_GEN 2              //general registers set
#define VGA_SEQ 3              //sequencer set
#define VGA_GCT 4              //graphics controller set
#define VGA_OLD 5              //old pallete enable

#define VGA__GEN__MIS 0        //miscellaneous in the generals set
#define VGA__GEN__ST1 1        //status 1 in the generals set, readonly
#define VGA__OLD__ENA 0        //old pallete enable index

#define VGA__GEN_MISC_R 0x3cc  //general miscellaneous, read
#define VGA__GEN_MISC_W 0x3c2  //general miscellaneous, write
#define VGA__GEN_STATUS1 0x3da //general status 1
#define VGA__SEQ_ADDR 0x3c4    //sequencer, address
#define VGA__SEQ_DATA 0x3c5    //sequencer, data
#define VGA__SEQ__RST 0        //sequencer, reset
#define VGA__SEQ__CLK 1        //sequencer, clock mode
#define VGA__SEQ__MAP 2        //sequencer, map selection
#define VGA__SEQ__FNT 3        //sequencer, font selection
#define VGA__SEQ__MEM 4        //sequencer, memory mode
#define VGA__CRT_ADDR 0x3d4    //CRT, address
#define VGA__CRT_DATA 0x3d5    //CRT, data
#define VGA__CRT__HTO 0        //CRT, horizontal total
#define VGA__CRT__HDE 1        //CRT, horizontal display-enable end
#define VGA__CRT__HBS 2        //CRT, horizontal blanking start
#define VGA__CRT__HBE 3        //CRT, horizontal blanking end
#define VGA__CRT__HRS 4        //CRT, horizontal retrace start
#define VGA__CRT__HRE 5        //CRT, horizontal retrace end
#define VGA__CRT__VTO 6        //CRT, vertical total
#define VGA__CRT__MSB 7        //CRT, most significant bits
#define VGA__CRT__PRS 8        //CRT, preset scanline
#define VGA__CRT__MSL 9        //CRT, maximum scanline
#define VGA__CRT__CSL 10       //CRT, cursor start
#define VGA__CRT__CEL 11       //CRT, cursor end
#define VGA__CRT__SAH 12       //CRT, start address (high)
#define VGA__CRT__SAL 13       //CRT, start address (low)
#define VGA__CRT__CLH 14       //CRT, cursor location (high)
#define VGA__CRT__CLL 15       //CRT, cursor location (low)
#define VGA__CRT__VRS 16       //CRT, vertical retrace start
#define VGA__CRT__VRE 17       //CRT, vertical retrace end
#define VGA__CRT__VDE 18       //CRT, vertical display-enable end
#define VGA__CRT__OFF 19       //CRT, offset (logical line width)
#define VGA__CRT__ULL 20       //CRT, underline location
#define VGA__CRT__VBS 21       //CRT, vertical blanking start
#define VGA__CRT__VBE 22       //CRT, vertical blanking end
#define VGA__CRT__MOD 23       //CRT, mode
#define VGA__CRT__SSL 24       //CRT, line compare (split screen line)
#define VGA__GCT_ADDR 0x3ce    //graphics controller, address
#define VGA__GCT_DATA 0x3cf    //graphics controller, data
#define VGA__GCT__WRV 0        //graphics controller, write value
#define VGA__GCT__WRS 1        //graphics controller, write selection
#define VGA__GCT__COC 2        //graphics controller, color compare
#define VGA__GCT__DRO 3        //graphics controller, data rotate
#define VGA__GCT__RDM 4        //graphics controller, read map
#define VGA__GCT__GMO 5        //graphics controller, graphics mode
#define VGA__GCT__MIS 6        //graphics controller, miscelaneous
#define VGA__GCT__CSE 7        //graphics controller, color selection
#define VGA__GCT__BIT 8        //graphics controller, bit mask
#define VGA__ACT_ADDA 0x3c0    //attribute controller, address and data
#define VGA__ACT_READ 0x3c1    //attribute controller, read
#define VGA__ACT__ATB 16       //attribute controller, attributes
#define VGA__ACT__BOR 17       //attribute controller, border color
#define VGA__ACT__PEN 18       //attribute controller, plane enable
#define VGA__ACT__OFF 19       //attribute controller, offset
#define VGA__ACT__CSE 20       //attribute controller, color selection
#define VGA__DAC_ADDR_R 0x3c7  //pallete, read address
#define VGA__DAC_ADDR_W 0x3c8  //pallete, write address
#define VGA__DAC_DATA 0x3c9    //pallete, data
#define VGA__DAC_MASK 0x3c6    //pallete, bit mask

// from graphics.h - remove
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

extern uint8_t *framebuffer;
extern uint8_t *vram;
extern uint32_t fbpitch;
extern uint8_t  fbbpp;
extern bool changed;

// Functions
void    VGAWriteReg(uint8_t, uint8_t, uint8_t);
uint8_t VGAReadReg (uint8_t, uint8_t);

void resetregs(vgaregs_t*);
void vgachangemode(vgaregs_t*);
void settextplane();
void setfontplane();

void VGASetPal(uint8_t*, uint8_t, uint32_t);
void VGAGetPal(uint8_t*, uint8_t, uint32_t);
void VGAGotoXY(uint8_t, uint8_t, uint8_t);
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