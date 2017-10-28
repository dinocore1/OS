#include <os.h>
#include <drivers/screen.h>

#define VMEM 0xb8000
#define WIDTH 80
#define HEIGHT 25
#define SD 2

static struct {
  int cursorX;
  int cursorY;

} screen;

static
void clearLine(uint8 firstLine, uint8 numLines) {
  uint16 i = WIDTH * firstLine * SD;
  const uint16 end = WIDTH * (firstLine + numLines) * SD;
  uint8* vidmem = (uint8*)VMEM;
  for(i;i<end;i++) {
    vidmem[i] = 0x0;
  }
}

static
void updateCursor() {
  uint16 temp = screen.cursorY * WIDTH + screen.cursorX;

  outportb(0x3D4, 14);
  outportb(0x3D5, temp >> 8);
  outportb(0x3D4, 15);
  outportb(0x3D5, temp);
}

void clearScreen() {
  clearLine(0, HEIGHT);
  screen.cursorX = 0;
  screen.cursorY = 0;
  updateCursor();
}

void printch(char c)
{
  uint8* vidmem = (uint8*)VMEM;
  switch(c) {
    case('\r'):
      screen.cursorX = 0;
      break;

    case('\n'):
      screen.cursorX = 0;
      screen.cursorY++;
      break;

    default:
      vidmem[(screen.cursorY * WIDTH + screen.cursorX)*SD] = c;
      vidmem[(screen.cursorY * WIDTH + screen.cursorX)*SD + 1] = 0x0F;
      screen.cursorX++;
      break;
  }
}

void print(char* str) {
  uint16 i = 0;
  while(str[i]) {
    printch(str[i]);
    i++;
  }
  updateCursor();
}
