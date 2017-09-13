#include <MicroBit.h>
#include "print.h"

MicroBit uBit;

void init_print()
{
   uBit.init();
   uBit.serial.baud(115200);
}

void print(const char *text)
{
	uBit.serial.send(text);
}

void printbytes(const char *text, unsigned char* bytes, int cnt)
{
   uBit.serial.send(text);
   for(int i=0;i<cnt;i++)
   {
      printbyte(bytes[i]);
   }

   uBit.serial.send("\r\n");
}

void printbyte(unsigned char b)
{
   char text[3];
   itoa16(b, text);
   text[2]=0;
   uBit.serial.send(text);
   uBit.serial.send(" ");
}


void itoa16(char val, char *text)
{
   if(text)
   {
      text[0]=nibble(val>>4);
      text[1]=nibble(val);
   }
}

unsigned char nibble(char val)
{
   val&=0x0f;
   if(val>9)
      return val+0x61-10;
   else
      return val+0x30;
}

void printnum(const char* text, int val)
{
   uBit.serial.send(text);
   char num[15];
   itoa(val,num);
   uBit.serial.send(num);
   uBit.serial.send("\r\n");
}

void fail(const char* text)
{
	print(text);
	while(1);
}

void print_stack(const char *primitive, const unsigned int bytes, unsigned int stack)
{
  char num[15];
  print(primitive);
  print(": ");
  if(bytes != (unsigned int)-1)
  {
    print("[");
    itoa(bytes,num);
    print(num);
    print("] ");
  }

  itoa(stack,num);
  print(num);
  print(" stack bytes\r\n");
}

