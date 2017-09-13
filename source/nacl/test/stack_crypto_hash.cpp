/*
 * File:    test/stack_crypto_hash.c
 * Author:  Michael Hutter, Peter Schwabe, Andreas Schuler
 * Version: Wed Aug 13 04:15:13 2014 +0200
 * Public Domain
 */

#include <stdlib.h>

extern "C" {
#include "nacl/armnacl.h"
#include "randombytes/randombytes.h"
}

#include "print.h"
#include "random.h"
#include "stacksize.h"

#define MAXTEST_BYTES 1024

unsigned char h[crypto_hash_BYTES];
unsigned char m[MAXTEST_BYTES];
  
unsigned int i,mlen;

unsigned int ctr=0,newctr;
unsigned char canary;
volatile unsigned char *p;

int main(void)
{
  print("Starting stack_crypto_hash()\r\n");

  volatile unsigned char a; /* Mark the beginning of the stack */

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_hash(h,m,0);
    newctr = MAXSTACK - stack_count(canary,&a);
    ctr=(newctr>ctr)?newctr:ctr;
  }
  print_stack("crypto_hash",0,ctr);


  for(mlen=1;mlen<=MAXTEST_BYTES;mlen<<=1)
  {
    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_hash(h,m,mlen);
      ctr = MAXSTACK - stack_count(canary,&a);
      ctr=(newctr>ctr)?newctr:ctr;
    }
    print_stack("crypto_hash",mlen,ctr);
  }

  fail("Done.");
  return 0;
}
