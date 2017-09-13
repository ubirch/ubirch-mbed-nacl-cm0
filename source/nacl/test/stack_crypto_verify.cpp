/*
 * File:    test/stack_crypto_verify.c
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

unsigned char x[crypto_verify_BYTES];
unsigned char y[crypto_verify_BYTES];
  
unsigned int i;

unsigned int ctr=0,newctr;
unsigned char canary;
volatile unsigned char *p;


int main(void)
{
  print("Starting stack_crypto_verify()\r\n");

  volatile unsigned char a; /* Mark the beginning of the stack */

  for(i=0;i<15;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_verify(x,y);
    newctr = MAXSTACK - stack_count(canary,&a);
    ctr=(newctr>ctr)?newctr:ctr;
    print_stack("crypto_verify",0,ctr);
  }
  print_stack("crypto_verify",0,ctr);

  return 0;
}
