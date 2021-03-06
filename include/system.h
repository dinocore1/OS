#ifndef SYSTEM_H
#define SYSTEM_H

static inline
uint8 inportb(uint16 port)
{
    uint8 rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

static inline
void outportb(uint16 port, uint8 data)
{
  __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

#endif // SYSTEM_H
