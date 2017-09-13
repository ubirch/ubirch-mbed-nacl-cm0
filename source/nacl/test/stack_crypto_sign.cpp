/*
 * File:    test/stack_crypto_sign.c
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

#define pklen crypto_sign_PUBLICKEYBYTES
#define sklen crypto_sign_SECRETKEYBYTES

unsigned char pk[pklen];
unsigned char sk[sklen];
unsigned char sm[MAXTEST_BYTES + crypto_sign_BYTES]; 
crypto_uint16 smlen,mlen;
  
unsigned int i,j;

unsigned int ctr=0,newctr;
unsigned char canary;
volatile unsigned char *p;

int main(void)
{
  print("Starting stack_crypto_sign()\r\n");

  volatile unsigned char a; /* Mark the beginning of the stack */

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_sign_keypair(pk,sk);
	 newctr = MAXSTACK - stack_count(canary,&a);
    ctr = MAXSTACK - stack_count(canary,&a);
  }
  print_stack("crypto_sign_keypair",-1,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_sign(sm,&smlen,sm,0,sk);
    newctr = MAXSTACK - stack_count(canary,&a);
    ctr = MAXSTACK - stack_count(canary,&a);
  }
  print_stack("crypto_sign",0,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_sign_open(sm,&mlen,sm,smlen,pk);
    newctr = MAXSTACK - stack_count(canary,&a);
    ctr = MAXSTACK - stack_count(canary,&a);
  }
  print_stack("crypto_sign_open",smlen,ctr);

  for(j=1;j<=MAXTEST_BYTES;j<<=1)
  {
    mlen = j;

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_sign(sm,&smlen,sm,mlen,sk);
      newctr = MAXSTACK - stack_count(canary,&a);
      ctr = MAXSTACK - stack_count(canary,&a);
    }
    print_stack("crypto_sign",mlen,ctr);

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_sign_open(sm,&mlen,sm,smlen,pk);
      newctr = MAXSTACK - stack_count(canary,&a);
      ctr = MAXSTACK - stack_count(canary,&a);
    }
    print_stack("crypto_sign_open",smlen,ctr);
  }

  fail("Done.");
  return 0;
}
