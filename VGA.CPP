#include "colors.hpp"
#include "constants.hpp"
#include "input.hpp"
#include <i86.h>
#include <conio.h>
#include <stdlib.h>
#include "p4pal.hpp"

int frameCounter = 0;
int paletteCount = -1;
unsigned int palette[256] = {0};
unsigned int *linearFrameBuffer = NULL;
bool banking32Bit = false;

void setBiosGraphicsMode(int mode) {
    union REGS regs;
    regs.x.eax = mode;
    int386(0x10, &regs, &regs);
}

int getBiosGraphicsMode() {
    union REGS regs;
    regs.w.ax = 0x0f00;
    int386 (0x10, &regs, &regs);
    return regs.h.al;
}

void setBiosCursor(int x, int y) {
    union REGS regs;
    regs.x.eax = 0x200;
    regs.h.bh = 0;
    regs.h.dl = x;
    regs.h.dh = y;
    int386(0x10, &regs, &regs);
}

void setPalette(int index, unsigned int color) {
  outp(0x3c8,index);
  outp(0x3c9,(color & 255)>>2);
  outp(0x3c9,((color>>8) & 255)>>2);
  outp(0x3c9,((color>>16) & 255)>>2);
  palette[index] = color;
}

unsigned int getPalette(int index) {
  outp(0x3c8,index);
  int r = inp(0x3c9);
  int g = inp(0x3c9);
  int b = inp(0x3c9);
  return 0xff000000|(r<<2)|(g<<10)|(b<<18);
}

unsigned char getPaletteIndex(unsigned int rgba) {
  const int r = rgba & 255;rgba>>=8;
  const int g = rgba & 255;rgba>>=8;
  const int b = rgba & 255;rgba>>=8;
  int ld = 256*256*4;
  int ri = 0;
  for (int i = 0; i < 256; i++) {
    unsigned int pal = palette[i];
    const int r2 = pal & 255;pal >>= 8;
    const int g2 = pal & 255;pal >>= 8;
    const int b2 = pal & 255;pal >>= 8;
    const int d = (r2-r)*(r2-r)+(g2-g)*(g2-g)+(b2-b)*(b2-b);
    if (d < ld) {
      ld = d;
      ri = i;
    }
  }
  return ri;
}

unsigned char getPaletteIndex16(unsigned int rgba) {
  const int r = rgba & 255;rgba>>=8;
  const int g = rgba & 255;rgba>>=8;
  const int b = rgba & 255;rgba>>=8;
  int ld = 256*256*4;
  int ri = 0;
  for (int i = 0; i < 16; i++) {
    unsigned int pal = palette[i];
    const int r2 = pal & 255;pal >>= 8;
    const int g2 = pal & 255;pal >>= 8;
    const int b2 = pal & 255;pal >>= 8;
    const int d = (r2-r)*(r2-r)+(g2-g)*(g2-g)+(b2-b)*(b2-b);
    if (d < ld) {
      ld = d;
      ri = i;
    }
  }
  return ri;
}


void randomPalette() {
  paletteCount = 256;
  for (int i = 1; i < 256; i++) {
    int r = rand() & 255;
    int g = rand() & 255;
    int b = rand() & 255;
    if (i > 256-64) {
      r = (i - (256-64))*4;
      g = r;
      b = r;
    }
    setPalette(i,r|(g<<8)|(b<<16)|0xff000000);
  }
}

void plus4Palette() {
  for (int i = 0; i < sizeof(plus4PaletteStandard)/4; i++) {
    setPalette(i,plus4PaletteStandard[i]);
  }
}

void egaPalette(int startColor, bool setColors) {
  palette[EGA_COLOR_BLACK+startColor] = _EGA_COLOR_BLACK;
  palette[EGA_COLOR_BLUE+startColor] = _EGA_COLOR_BLUE;
  palette[EGA_COLOR_GREEN+startColor] = _EGA_COLOR_GREEN;
  palette[EGA_COLOR_CYAN+startColor] = _EGA_COLOR_CYAN;
  palette[EGA_COLOR_RED+startColor] = _EGA_COLOR_RED;
  palette[EGA_COLOR_VIOLET+startColor] = _EGA_COLOR_VIOLET;
  palette[EGA_COLOR_BROWN+startColor] = _EGA_COLOR_BROWN;
  palette[EGA_COLOR_GREY_LIGHT+startColor] = _EGA_COLOR_GREY_LIGHT;
  palette[EGA_COLOR_GREY_DARK+startColor] = _EGA_COLOR_GREY_DARK;
  palette[EGA_COLOR_BLUE_LIGHT+startColor] = _EGA_COLOR_BLUE_LIGHT;
  palette[EGA_COLOR_GREEN_LIGHT+startColor] = _EGA_COLOR_GREEN_LIGHT;
  palette[EGA_COLOR_CYAN_LIGHT+startColor] = _EGA_COLOR_CYAN_LIGHT;
  palette[EGA_COLOR_RED_LIGHT+startColor] = _EGA_COLOR_RED_LIGHT;
  palette[EGA_COLOR_VIOLET_LIGHT+startColor] = _EGA_COLOR_VIOLET_LIGHT;
  palette[EGA_COLOR_YELLOW+startColor] = _EGA_COLOR_YELLOW;
  palette[EGA_COLOR_WHITE+startColor] = _EGA_COLOR_WHITE;
  if (setColors) {
    for (int i = 0; i < 16; i++) setPalette(i+startColor,palette[i+startColor]);
  }
}

void palette16Colors() {
  paletteCount = 16;
  egaPalette(0,false);
}

extern unsigned int frameBufferWidth;
extern unsigned int frameBufferHeight;

void frameBufferToScreen16Colors(unsigned int *frameBuffer) {
    int x,y,i,j,b;
    unsigned char *read;
    unsigned char *write;
    int width = 640;
    int height = 480;
    unsigned char *buffer = new unsigned char[width*height];
    unsigned char *b2 = buffer;
    for (y = 0; y < height; y++) {
      unsigned int *read = &frameBuffer[y * frameBufferHeight/height * frameBufferWidth];
      for (x = 0; x < width; x++) {
        *b2++=getPaletteIndex16(read[x*frameBufferWidth/width]);
      }
    }

    for (y = 0; y < height; y++) {
        for (j = 0; j < 4; j++) {
            outp(0x3c4, 2);
            outp(0x3c5, 1<<j);
            read = &buffer[y * width];
            write = (unsigned char *)(0xa0000 + (width/8)*y);
            int xi = 0;
            for (x = 0; x < width/8; x++) {
                b = 0;
                for (i = 0; i < 8; i++) {
                    b |= (((read[xi])>>j) & 1)<<(7-i);
                    xi++;
                }
                *write++ = b;
            }
        }
    }
    delete[] buffer;
}

void setLinearFrameBuffer32Bit(unsigned int *frameBuffer) {
  linearFrameBuffer = frameBuffer;
}

void setBanking32Bit() {
  banking32Bit = true;
}
__inline unsigned int switchRB(unsigned int rgba) {
  return ((rgba&255)<<16)|(rgba&0xff00ff00)|((rgba>>16)&255);
}

void saveScreenShot(const char *fileName, unsigned int *data, int width,int height);

void frameBufferToScreen(unsigned int *frameBuffer) {
  frameCounter++;
  if (key == VK_P_CTRL) {
    saveScreenShot("scrnsht.png",frameBuffer,frameBufferWidth,frameBufferHeight);
  }
  if (banking32Bit) {
    // not implemented, yet..
    unsigned int *videoRam = (unsigned int*)0xa0000;
    for (int y = 0; y < 768; y++) {
      for (int x = 0; x < 1024; x++) {
        if ((unsigned int)videoRam>0xb0000) videoRam-=0x10000/4;
        *videoRam++ = switchRB(frameBuffer[x*frameBufferWidth/1024+y*frameBufferHeight/768*frameBufferWidth]);
      }
    }
    return;
  }
  if (linearFrameBuffer != NULL) {
    unsigned int *videoRam = linearFrameBuffer;
    for (int y = 0; y < frameBufferHeight; y++) {
      for (int x = 0; x < frameBufferWidth; x++) {
        *videoRam++ = switchRB(frameBuffer[x*frameBufferWidth/frameBufferWidth+y*frameBufferHeight/frameBufferHeight*frameBufferWidth]);
      }
    }
    return;
  }
  if (frameBufferWidth == 640 && frameBufferHeight == 480) {
    frameBufferToScreen16Colors(frameBuffer);
    return;
  }
  unsigned char *videoRam = (unsigned char *)0xa0000;
  for (int y = 0; y < 200; y++) {
    for (int x = 0; x < 320; x++) {
      *videoRam++ = getPaletteIndex(frameBuffer[x*frameBufferWidth/320+y*frameBufferHeight/200*frameBufferWidth]);
    }
  }
}