#include "../include/FbGraphics.hpp"

#include "../include/Static.hpp"
#include "../include/Syslog.hpp"

#include "../include/io.h"
#include "../include/fonts.h"
#include "../include/mboot.h"

bool textMode = false;
bool settedMode=false;
bool mSet;

vbe_info_t vbeMode;

//writes a value in a VGA register
//set is 0 for CRT controller, 1 for attribute controller, 2 for
//generals, 3 for sequencer, 4 for graphics controller, 5 for
//old pallete enable
void VGAWriteReg(byte set, byte index, byte value)
{
   switch(set)
   {
      case VGA_CRT:
         if(index<=24)
         {
            outb(VGA__CRT_ADDR,index);
            outb(VGA__CRT_DATA,value);
         }
         break;
      case VGA_ACT:
         if(index<=20)
         {
            inb(VGA__GEN_STATUS1);
            index=(inb(VGA__ACT_ADDA)&0x20)|index;
            inb(VGA__GEN_STATUS1);
            outb(VGA__ACT_ADDA,index);
            outb(VGA__ACT_ADDA,value);
         }
         break;
      case VGA_GEN:
         if(index==0)
         {
            outb(VGA__GEN_MISC_W,value);
         }
         break;
      case VGA_SEQ:
         if(index<=4)
         {
            outb(VGA__SEQ_ADDR,index);
            outb(VGA__SEQ_DATA,value);
         }
         break;
      case VGA_GCT:
         if(index<=8)
         {
            outb(VGA__GCT_ADDR,index);
            outb(VGA__GCT_DATA,value);
         }
         break;
      case VGA_OLD:
         if(index==0)
         {
            value=value?0x20:0;
            inb(VGA__GEN_STATUS1);
            outb(VGA__ACT_ADDA,value);
         }
         break;
   }
}

//reads a value from a VGA register
//set is 0 for CRT controller, 1 for attribute controller, 2 for
//generals, 3 for sequencer, 4 for graphics controller, 5 for
//old pallete enable
byte VGAReadReg(byte set, byte index)
{
   byte r=0;
   switch(set)
   {
   case VGA_CRT:
      if(index<=24)
      {
         outb(VGA__CRT_ADDR,index);
         r=inb(VGA__CRT_DATA);
      }
      break;
   case VGA_ACT:
      if(index<=20)
      {
         inb(VGA__GEN_STATUS1);
         index=(inb(VGA__ACT_ADDA)&0x20)|index;
         inb(VGA__GEN_STATUS1);
         outb(VGA__ACT_ADDA,index);
         r=inb(VGA__ACT_READ);
      }
      break;
   case VGA_GEN:
      if(index==VGA__GEN__MIS)
      {
         r=inb(VGA__GEN_MISC_R);
      }
      if(index==VGA__GEN__ST1)
      {
         r=inb(VGA__GEN_STATUS1);
      }
      break;
   case VGA_SEQ:
      if(index<=4)
      {
         outb(VGA__SEQ_ADDR,index);
         r=inb(VGA__SEQ_DATA);
      }
      break;
   case VGA_GCT:
      if(index<=8)
      {
         outb(VGA__GCT_ADDR,index);
         r=inb(VGA__GCT_DATA);
      }
      break;
   case VGA_OLD:
      if(index==0)
      {
         inb(VGA__GEN_STATUS1);
         r=(inb(VGA__ACT_ADDA)>>5)&1;
      }
      break;
   }
return(r);
}

//resets the registers in a VGA register structure
void resetregs(vgaregs_t*regs)
{
   dword i;
   byte*p=(byte*)regs;
   for(i=0;i<sizeof(vgaregs_t);i++)
   {
      *p++=0;
   }
   regs->gen_mis=0x23;//enable video memory, normal mode, upper 64KB page
   regs->seq[VGA__SEQ__CLK]=0x02;//set bit to 1
   regs->seq[VGA__SEQ__MAP]=0x0f;//select the 4 planes
   regs->seq[VGA__SEQ__MEM]=0x02;//enable 256KB
   regs->crt[VGA__CRT__HBE]=0x80;//set bit to 1
   regs->crt[VGA__CRT__VRE]=0x30;//disable IRQs
   regs->crt[VGA__CRT__ULL]=31;//underline location
   regs->crt[VGA__CRT__MSB]=0x10;//split screen
   regs->crt[VGA__CRT__MSL]=0x40;
   regs->crt[VGA__CRT__SSL]=0xff;
   regs->crt[VGA__CRT__MOD]=0xa3;//normal mode
   regs->gct[VGA__GCT__BIT]=0xff;//bit mask
   regs->act[VGA__ACT__ATB-16]=0x04;//enable line characters
   regs->act[VGA__ACT__PEN-16]=0x0f;//enable the 4 planes
}

//changes the video mode by writing in all the VGA registers
void vgachangemode(vgaregs_t*regs)
{
   word i;
   //unlock some CRTC registrrs
   VGAWriteReg(VGA_CRT,VGA__CRT__VRE,VGAReadReg(VGA_CRT,VGA__CRT__VRE)&0x7f);
   //enable pallete
   outb(VGA__DAC_MASK,0xff);
   //wait until display-enable start
   //while(!(VGAReadReg(VGA_GEN,VGA__GEN__ST1)&0x08));
   //while(VGAReadReg(VGA_GEN,VGA__GEN__ST1)&0x08);
   //stop sequencer
   VGAWriteReg(VGA_SEQ,VGA__SEQ__RST,0x01);
   //write in the registers
   VGAWriteReg(VGA_GEN,VGA__GEN__MIS,regs->gen_mis);
   for(i=1;i<5;i++)
      VGAWriteReg(VGA_SEQ,i,regs->seq[i]);
   for(i=0;i<25;i++)
      VGAWriteReg(VGA_CRT,i,regs->crt[i]);
   for(i=0;i<9;i++)
      VGAWriteReg(VGA_GCT,i,regs->gct[i]);
   for(i=0;i<5;i++)
      VGAWriteReg(VGA_ACT,i+16,regs->act[i]);
   //reset old pallete
   VGAWriteReg(VGA_OLD,VGA__OLD__ENA,0);
   for(i=0;i<16;i++)
      VGAWriteReg(VGA_ACT,i,i);
   VGAWriteReg(VGA_OLD,VGA__OLD__ENA,1);
   //resume sequencer
   VGAWriteReg(VGA_SEQ,VGA__SEQ__RST,0x03);
}

//selects the text plane
void settextplane(void)
{
   VGAWriteReg(VGA_GCT,VGA__GCT__GMO,0x10);
   VGAWriteReg(VGA_GCT,VGA__GCT__MIS,(VGAReadReg(VGA_GCT,VGA__GCT__MIS)&0x0c)|2);
   VGAWriteReg(VGA_SEQ,VGA__SEQ__MAP,0x03);
   VGAWriteReg(VGA_GCT,VGA__GCT__RDM,1);
   VGAWriteReg(VGA_SEQ,VGA__SEQ__MEM,0x02);
}

//selects the font plane
void setfontplane(void)
{
   VGAWriteReg(VGA_GCT,VGA__GCT__GMO,0x00);
   VGAWriteReg(VGA_GCT,VGA__GCT__MIS,VGAReadReg(VGA_GCT,VGA__GCT__MIS)&0x0c);
   VGAWriteReg(VGA_SEQ,VGA__SEQ__MAP,0x04);
   VGAWriteReg(VGA_GCT,VGA__GCT__RDM,2);
   VGAWriteReg(VGA_SEQ,VGA__SEQ__MEM,0x06);
}

//modifies the VGA pallete
//pal=poworder to the first pallete color to be used
//first=first color to modify
//num=number of colors to modify
void VGASetPal(uint8_t* pal, uint8_t first, uint32_t num)
{
   if((num+first)>256)num=256-first;
   if(!num)return;
   num*=3;
   outb(VGA__DAC_ADDR_W,first);
   while(num--)
   {
      outb(VGA__DAC_DATA,(*pal)>>2);
      pal++;
   }
}

//obtains the VGA pallete
//pal=poworder to the first pallete color to be overwritten
//first=first color to read
//num=number of colors to read
void VGAGetPal(byte*pal,byte first,word num)
{
   if((num+first)>256)num=256-first;
   if(!num)return;
   num*=3;
   outb(VGA__DAC_ADDR_R,first);
   while(num--)
   {
      *pal=inb(VGA__DAC_DATA)<<2;
      pal++;
   }
}

//puts the text cursor in the x,y coordinates
//w is the visual screen width in characters
void VGAGotoXY(byte x,byte y,byte w)
{
   word c;
   c=y;c*=w;
   c+=x;
   VGAWriteReg(VGA_CRT,VGA__CRT__CLH,c>>8);
   VGAWriteReg(VGA_CRT,VGA__CRT__CLL,c);
}

//gets the cursor coordinates and returns them in x,y
//w is the visual screen width in characters
void VGAWhereXY(byte*x,byte*y,byte w)
{
   word c;
   c=VGAReadReg(VGA_CRT,VGA__CRT__CLH);
   c<<=8;
   c|=VGAReadReg(VGA_CRT,VGA__CRT__CLL);
   *x=c%w;
   *y=c/w;
}

//changes the text cursor appearence
//y=first line
//h=block height
void VGASetCursor(byte y,byte h)
{
   VGAWriteReg(VGA_CRT,VGA__CRT__CSL,y&31);
   VGAWriteReg(VGA_CRT,VGA__CRT__CEL,(y+h-1)&31);
}

//gets the text cursor appearence
//y=first line
//h=block height
void VGAGetCursor(byte*y,byte*h)
{
   *y=VGAReadReg(VGA_CRT,VGA__CRT__CSL)&31;
   *h=VGAReadReg(VGA_CRT,VGA__CRT__CEL)&31;
   *h-=*y;
   (*h)++;
}

//enables or disables the text cursor
void VGACursor(byte e)
{
   e=e?0:0x20;
   VGAWriteReg(VGA_CRT,VGA__CRT__CSL,(VGAReadReg(VGA_CRT,VGA__CRT__CSL)&31)|e);
}/*end function*/

//modifies the text font
//fnt=poworder to the first font character to be used
//ch=character height in the font
//first=first character in the VGA font to modify
//num=number of characters to modify
void VGASetFont(byte*fnt,byte ch,word first,word num)
{
   byte*v=(byte*)0xb8000;
   word i,j;
   if((num+first)>512)num=512-first;
   if(!num)return;
   v+=first*32;
   setfontplane();
   for(i=0;i<num;i++)
   {
      for(j=0;j<ch;j++)
      {
         v[j]=fnt[j];
      }
      for(j=ch;j<32;j++)
      {
         v[j]=0;
      }
      fnt+=ch;
      v+=32;
   }
   settextplane();
}

//obtains the text font
//fnt=poworder to the first font character to be overwritten
//ch=character height in the font
//first=first character in the VGA font to read
//num=number of characters to read
void VGAGetFont(byte*fnt,byte ch,word first,word num)
{
   byte*v=(byte*)0xb8000;
   word i,j;
   if((num+first)>512)num=512-first;
   if(!num)return;
   v+=first*32;
   setfontplane();
   for(i=0;i<num;i++)
   {
      for(j=0;j<ch;j++)
      {
         fnt[j]=v[j];
      }
      fnt+=ch;
      v+=32;
   }
   settextplane();
}

//waits until a vertical retrace period starts
void VGAWaitVBL(void)
{
   while(VGAReadReg(VGA_GEN,VGA__GEN__ST1)&8);
   while(!(VGAReadReg(VGA_GEN,VGA__GEN__ST1)&8));
}/*end function*/

//sets a VGA video mode
//returns 1 if the mode is valid, 0 if not
//m=mode
//  0=text (8-pixels-wide characters)
//  1=text (9-pixels-wide characters)
//  2=graphics 16 colors
//  3=graphics 256 colors
//w=width (in characters or in pixels)
//h=height (in characters or in pixels)
//o=option
//  text modes:
//    8=8-pixels-high characters
//    12=12-pixels-high characters
//    14=14-pixels-high characters
//    16=16-pixels-high characters
//  graphic modes:
//    0=normal
//    1=chained mode
//----------------------------------------------------------------
//text mode widths (8p): 40, 80, 90
//text mode widths (9p): 40, 80
//text mode heights (8-pix-h): 25, 30, 50, 60
//text mode heights (12-pix-h): 20, 40
//text mode heights (14-pix-h): 25
//text mode heights (16-pix-h): 25, 30
//graphic mode widths (16c): 640, 720
//graphic mode widths (256c): 320, 360
//graphic mode heights: 200, 240, 350, 400, 480
//chained mode only allows 320*200 at 256 colors
byte VGAMode(uint8_t m, uint64_t w, uint64_t h, uint8_t o)
{
   byte*tbl_hor,*tbl_ver,*tbl_mod;
   byte*v;
   dword i;
   vgaregs_t regs;
   byte chained=0;
   byte curstart=0,curheight=0;
   resetregs(&regs);
   switch(m)
   {
      case 0://txt 8p
      case 1://txt 9p
         if(m)
         {
            tbl_mod=tbl_mod_txt9p;
            regs.gen_mis|=0x04;
         }
         else
         {
            tbl_mod=tbl_mod_txt8p;
         }
         switch(w)
         {
            case 40:
               tbl_hor=tbl_hor_txt40;
               break;
            case 80:
               tbl_hor=tbl_hor_txt80;
               break;
            case 90:
               if(m==1)return(0);
               tbl_hor=tbl_hor_txt90;
               regs.gen_mis|=0x04;
               break;
            default:
               return(0);
         }
         switch(h)
         {
            case 20:
               switch(o)
               {
                  case 12:
                     tbl_ver=tbl_ver_txt20_12;
                     break;
                  default:
                     return(0);
               }
               break;
            case 25:
               switch(o)
               {
                  case 8:
                     tbl_ver=tbl_ver_txt25_8;
                     break;
                  case 14:
                     tbl_ver=tbl_ver_txt25_14;
                     break;
                  case 16:
                     tbl_ver=tbl_ver_txt25_16;
                     break;
                  default:
                     return(0);
               }
               break;
            case 30:
               switch(o)
               {
                  case 8:
                     tbl_ver=tbl_ver_txt30_8;
                     break;
                  case 16:
                     tbl_ver=tbl_ver_txt30_16;
                     break;
                  default:
                     return(0);
               }
               break;
            case 40:
               switch(o)
               {
                  case 12:
                     tbl_ver=tbl_ver_txt40_12;
                     break;
                  default:
                     return(0);
               }
               break;
            case 50:
               switch(o)
               {
                  case 8:
                     tbl_ver=tbl_ver_txt50_8;
                     break;
                  default:
                     return(0);
               }
               break;
            case 60:
               switch(o)
               {
                  case 8:
                     tbl_ver=tbl_ver_txt60_8;
                     break;
                  default:
                     return(0);
               }
               break;
            default:
               return(0);
         }
         break;
      case 2://gra 16c
         if(o)return(0);
         tbl_mod=tbl_mod_gra16c;
         switch(w)
         {
            case 640:
               tbl_hor=tbl_hor_gra640;
               break;
            case 720:
               regs.gen_mis|=0x04;
               tbl_hor=tbl_hor_gra720;
               break;
            default:
               return(0);
         }
         switch(h)
         {
            case 200:
               tbl_ver=tbl_ver_gra200;
               break;
            case 240:
               tbl_ver=tbl_ver_gra240;
               break;
            case 350:
               tbl_ver=tbl_ver_gra350;
               break;
            case 400:
               tbl_ver=tbl_ver_gra400;
               break;
            case 480:
               tbl_ver=tbl_ver_gra480;
               break;
            default:
               return(0);
         }
         break;
      case 3://gra 256c
         tbl_mod=tbl_mod_gra256c;
         switch(w)
         {
            case 320:
               tbl_hor=tbl_hor_gra320;
               break;
            case 360:
               regs.gen_mis|=0x04;
               tbl_hor=tbl_hor_gra360;
               break;
            default:
               return(0);
         }
         switch(h)
         {
            case 200:
               tbl_ver=tbl_ver_gra200;
               break;
            case 240:
               tbl_ver=tbl_ver_gra240;
               break;
            case 350:
               tbl_ver=tbl_ver_gra350;
               break;
            case 400:
               tbl_ver=tbl_ver_gra400;
               break;
            case 480:
               tbl_ver=tbl_ver_gra480;
               break;
            default:
               return(0);
         }
         switch(o)
         {
            case 0:
               break;
            case 1:
               chained=1;
               if((w!=320)||(h!=200))
                  return(0);
               break;
            default:
               return(0);
         }
         break;
      default:
         return(0);
   }
   regs.seq[VGA__SEQ__CLK]|=tbl_hor[0];
   regs.seq[VGA__SEQ__MEM]|=tbl_hor[1];
   regs.crt[VGA__CRT__HTO]|=tbl_hor[2];
   regs.crt[VGA__CRT__HDE]|=tbl_hor[3];
   regs.crt[VGA__CRT__HBS]|=tbl_hor[4];
   regs.crt[VGA__CRT__HBE]|=tbl_hor[5];
   regs.crt[VGA__CRT__HRS]|=tbl_hor[6];
   regs.crt[VGA__CRT__HRE]|=tbl_hor[7];
   regs.crt[VGA__CRT__OFF]|=tbl_hor[8];
   regs.gct[VGA__GCT__GMO]|=tbl_hor[9];
   regs.gct[VGA__GCT__MIS]|=tbl_hor[10];
   regs.act[VGA__ACT__ATB-16]|=tbl_hor[11];

   regs.gen_mis|=tbl_ver[0];
   regs.crt[VGA__CRT__VTO]|=tbl_ver[1];
   regs.crt[VGA__CRT__MSB]|=tbl_ver[2];
   regs.crt[VGA__CRT__MSL]|=tbl_ver[3];
   regs.crt[VGA__CRT__VRS]|=tbl_ver[4];
   regs.crt[VGA__CRT__VRE]|=tbl_ver[5];
   regs.crt[VGA__CRT__VDE]|=tbl_ver[6];
   regs.crt[VGA__CRT__VBS]|=tbl_ver[7];
   regs.crt[VGA__CRT__VBE]|=tbl_ver[8];

   regs.seq[VGA__SEQ__CLK]|=tbl_mod[0];
   regs.act[VGA__ACT__OFF-16]|=tbl_mod[1];
   regs.crt[VGA__CRT__MOD]|=tbl_mod[2];

   if(chained)
   {
      regs.seq[VGA__SEQ__MEM]|=0x08;
      regs.crt[VGA__CRT__ULL]|=0x40;
      regs.crt[VGA__CRT__MOD]&=0xbf;
   }

   vgachangemode(&regs);
   switch(m)
   {
      case 0:
      case 1:
         setfontplane();
         v=(byte*)0xb8000;
         for(i=0;i<32480;i++)*v++=0;
         settextplane();
         v=(byte*)0xb8000;
         for(i=0;i<32480;i++)*v++=0;
         switch(o)
         {
            case 8:
               curstart=o-2;
               curheight=2;
               break;
            case 12:
               curstart=o-4;
               curheight=2;
               break;
            case 14:
               curstart=o-4;
               curheight=2;
               break;
            case 16:
               curstart=o-6;
               curheight=2;
         }
         VGASetCursor(curstart,curheight);
         break;
      case 2:
      case 3:
         v=(byte*)0xa0000;
         VGAWriteReg(VGA_SEQ,VGA__SEQ__MAP,15);
         for(i=0;i<65536;i++)*v++=0;
   }
   return(1);
}
//puts a pixel in 16 color mode
//x,y=pixel coordinates
//color=pixel color
//w,h=screen dimensions
/*struct VRAMPlanarEntry {
	uint8_t pix1 : 4;
	uint8_t pix2 : 4;
	uint8_t pix3 : 4;
	uint8_t pix4 : 4;

}__attribute__((__packed__));
struct VRAMPlanarEntry *vram=(struct VRAMPlanarEntry*)0xA000;*/
uint8_t *framebuffer;
uint8_t *vram=(uint8_t*)0xA0000;
   /*byte*v=(byte*)0xa0000;
   dword off;
   int plane;
   byte mask;
   if((x>=w)||(y>=h))return;
   off=(y*w+x)>>3;
   v+=off;
   for(plane=0;plane<4;plane++)
   {
      VGAWriteReg(VGA_SEQ,VGA__SEQ__MAP,1<<plane);
      VGAWriteReg(VGA_GCT,VGA__GCT__RDM,plane);
      mask=1<<(7-(x&7));
      if(color&(1<<plane))
         *v|=mask;
      else
         *v&=~mask;
   }*/
   /*
   //More fast code:
   //First, see if we are getting too long.
   if(x>w||y>h) //if we are not in screen area
   return;//do nothing
   //Now see, what pixel we need in 1 byte.
   unsigned long pixNum=y*w+x;
   //Now get number of byte in VRAM.
   unsigned long byteInVRAM=(pixNum-(pixNum%4));
   //Now get the position in byte.
   uint8_t pixPos=pixNum%4;
   //And now finally really put pixel in the memory.
   //BEcause we have 4 bitplanes, we need switch.
   switch(pixPos)
   {
	   case 0: vram[byteInVRAM].pix1=color; break;
	   case 1: vram[byteInVRAM].pix2=color; break;
	   case 2: vram[byteInVRAM].pix3=color; break;
	   case 3: vram[byteInVRAM].pix4=color; break;
   }
   //Job done.
   return;*/
uint32_t fbpitch;
uint8_t fbbpp;

void VGAPix16(uint64_t x, uint64_t y, uint32_t color)
{
	unsigned where = x*(fbbpp/8) + y*fbpitch;
	framebuffer[where] = color;              // BLUE
    framebuffer[where + 1] = (color >> 8);   // GREEN
    framebuffer[where + 2] = (color >> 16);  // RED
}

bool changed=false;
void vgaPutchar(char c, uint64_t x, uint64_t y,uint32_t fg, uint32_t bg, bool dnf)
{
    int i, j, count = 0;
    for(i = 0; i < 8; ++i)
    {
        for(j = 0; j < 8; ++j)
        {
            if(font[(uint32_t)c][count] == '1')
                VGAPix16(x + j, y + i, fg);
            else
                if(!dnf)
                    VGAPix16(x + j, y + i, bg);
            ++count;
        }
    }
}
void vgaWriteStr(uint64_t x, uint64_t y, const char * str, uint32_t fg, uint32_t bg)
{
    uint64_t i;
    for(i = 0; str[i]; ++i)
    {
        vgaPutchar(str[i], x + i * 8, y, fg, bg);
	}
}
void vgaWriteStr(uint64_t x, uint64_t y, const char* str, uint32_t fg, uint32_t bg, bool dnf)
{
    int i;
    for(i = 0; str[i]; ++i)
    {
        vgaPutchar(str[i], x + i * 8, y, fg, bg, true);
    }
}

uint32_t colorMix(uint32_t c1, uint32_t c2)
{
	return c1+c2-(16777216-min(c1,c2));
}

void hLine(uint64_t x1, uint64_t y1, uint64_t length, uint32_t color)
{
	word i;
	while(i != length)
	{
		i++;
		y1++;
		VGAPix16(x1,y1,color);
	}
}
void drawLine(uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2, uint32_t color)
{
    uint64_t i, j;
    for(i = 0; i < (y2 - y1); ++i)
    {
        for(j = 0; j < (x2 - x1) / (y2 - y1); ++j)
        {
            VGAPix16(x1+j*i,y1+i,color);
        }
    }
}
void vLine(uint64_t x1, uint64_t y1, uint64_t length, uint32_t color)
{
    uint64_t i;
    for(i = 0; i < length; ++i)
    {
        VGAPix16(x1+i,y1,color);
    }
}

void drawRect(uint64_t w, uint64_t h, uint64_t x_, uint64_t y_, uint32_t color)
{
	vLine(x_,y_,w,color);
	hLine(x_,y_,h,color);
	vLine(x_,y_+h,w,color);
	hLine(x_,y_+h,h,color);
}

void fillRect(uint64_t w, uint64_t h, uint64_t x_, uint64_t y_, uint32_t color)
{
	word w_=w, h_=h, x=x_, y=y_, i=0;
	while(i!=h)
	{
		vLine(x,y+i,w_,color);
		i++;
	}
}

void drawGradient(uint64_t x, uint64_t y, uint64_t x2, uint64_t y2, uint32_t c1, uint32_t c2, bool rev)
{
    if(!rev)
    {
        for(int i=0; (i < x2-x)&&((c1+i)<c2); i++)
        {
            hLine(x+i,y,y2-y,c1+i);
        }
    }
    else
    {
        for(int i=x2-x; i>=0; i--)
        {
            hLine(x+i,y,y2-y,c1+i);
        }
    }
}

void drawBitmap(const char* bm, uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t bg ,uint32_t c1, uint32_t c2, uint32_t c3, uint32_t c4, bool dnf)
{
    uint64_t i, j, count = 0;
    for(i = 0; i < height; ++i)
    {
        for(j = 0; j < width; ++j)
        {
            if(bm[count] == '0')
            {
                if(!dnf)
                {
                    VGAPix16(x+j,y+i,bg);
                }
            }
            else if(bm[count] == '1')
            VGAPix16(x+j,y+i,c1);
            else if(bm[count] == '2')
            VGAPix16(x+j,y+i,c2);
            else if(bm[count] == '3')
            VGAPix16(x+j,y+i,c3);
            else if(bm[count] == '4')
            VGAPix16(x+j,y+i,c4);
            count++;
        }
    }
}

void drawBitmap(const char* bm, uint64_t x, uint64_t y, uint64_t width, uint64_t height)
{
    uint64_t i, j, count = 0;

    for(i = 0; i < height; ++i)
	{
        for(j = 0; j < width; ++j)
        {
            if(bm[count] >= 'A' && bm[count] <= 'F')
                VGAPix16(x + j, y + i, bm[count] - 'A' + 10);
            else
                if(bm[count] >= '0' && bm[count] <= '9')
                    VGAPix16(x + j, y + i, bm[count] - '0');
            ++count;
        }
    }
}
void clrscr(uint32_t color)
{
	fillRect(640,480,0,0,color);
}
void setGraphicsMode()
{
	if(!mSet)log("[INFO] Calling VGAMode...");
    VGAMode(2,640,480,0);//set 640*480 at 16 colors //2
    if(!mSet)log("[INFO] Set standard VGA mode 640x480 with 16 colors.");
    //VGASetFont(FONT,fonteight,0,256);//this only in text mode to set the font
    //VGACursor(0);//this only in text mode in case you want to disable the cursor
    if(!mSet)log("[INFO] Setting palette...");
    VGASetPal(PAL16, 0, 16);//set the pallete
    if(!mSet)log("done.");
    mSet=true;
}
void textModeOn()
{
	setGraphicsMode();
	textMode = true;
}