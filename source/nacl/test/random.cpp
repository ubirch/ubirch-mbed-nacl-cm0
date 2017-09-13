#include <stdlib.h>

extern "C" {
#include "randombytes/randombytes.h"
}


unsigned char random()
{
   unsigned char c;
   randombytes(&c,1);
   return c;
}

