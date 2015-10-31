#pragma once

#ifndef FBGRAPHICS_HPP
#define FBGRAPHICS_HPP

// All of the contents is DEPRECATED

#include "HCL/Std.hpp"
#include "HCL/Surface.hpp"
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

class FbGraphics
{
    private:
        void* _fb; // framebuffer
        Hcl::Surface draw;

    public:
        void append(const Hcl::Surface&);
        void swap();
};

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

// from there - remove
typedef struct
{
    uint8_t gen_mis;
    uint8_t seq[5];
    uint8_t crt[25];
    uint8_t gct[9];
    uint8_t act[5];
} vgaregs_t;

extern bool textMode;
extern bool settedMode;
extern bool mSet;
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

void    VGASetPal (uint8_t*, uint8_t , uint32_t);
void    VGAGetPal (uint8_t*, uint8_t , uint32_t);
void    VGAGotoXY (uint8_t , uint8_t , uint8_t);
void    VGAWhereXY(uint8_t*, uint8_t*, uint8_t);
void    VGASetCursor(uint8_t , uint8_t);
void    VGAGetCursor(uint8_t*, uint8_t*);
void    VGACursor(uint8_t);
void    VGASetFont(uint8_t*, uint8_t, uint64_t, uint64_t);
void    VGAGetFont(uint8_t*, uint8_t, uint64_t, uint64_t);
void    VGAWaitVBL(void);
uint8_t VGAMode(uint8_t, uint64_t, uint64_t, uint8_t);

void    VGAPix16(uint64_t, uint64_t, uint32_t);

void vgaPutchar(char, uint64_t, uint64_t, uint32_t, uint32_t, bool=false);
void vgaWriteStr(uint64_t, uint64_t, const char*, uint32_t, uint32_t);
void vgaWriteStr(uint64_t, uint64_t, const char*, uint32_t, uint32_t, bool);

uint32_t colorMix(uint32_t c1, uint32_t c2);

void drawLine(uint64_t, uint64_t, uint64_t, uint64_t, uint32_t color);
void hLine   (uint64_t, uint64_t, uint64_t,           uint32_t color);
void vLine   (uint64_t, uint64_t, uint64_t,           uint32_t color);
void drawRect(uint64_t, uint64_t, uint64_t, uint64_t, uint32_t color);
void fillRect(uint64_t, uint64_t, uint64_t, uint64_t, uint32_t color);

// DEPRECATED
void drawGradient(uint64_t, uint64_t, uint64_t, int, uint32_t, uint32_t, bool=false);
void drawBitmap(const char*, uint64_t, uint64_t, uint64_t, uint64_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, bool=false);
void drawBitmap(const char*, uint64_t, uint64_t, uint64_t, uint64_t);
void setGraphicsMode();
void textModeOn();

#endif // FBGRAPHICS_HPP