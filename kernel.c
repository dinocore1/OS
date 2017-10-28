#include <os.h>

#include <drivers/screen.h>

void kmain()
{
  clearScreen();
  print("hello world\n");
}
