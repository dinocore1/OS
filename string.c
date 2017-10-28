
#include <os.h>
#include <string.h>

uint16 strlength(char* str) {
  uint16 i = 0;
  while(str[i+1]) {
    i++;
  }
  return i;
}
