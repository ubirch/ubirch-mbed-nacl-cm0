/*
 * File:    test/test_crypto_verify.c
 * Author:  Michael Hutter, Peter Schwabe, Andreas Schuler
 * Version: Wed Jul 30 12:16:08 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_verify/try.c version 20090118 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>
#include <string.h>

extern "C" {
#include "nacl/armnacl.h"
#include "randombytes/randombytes.h"
}

#include "print.h"
#include "random.h"


static unsigned char *x;
static unsigned char *y;


static const char *check(void)
{
  int r = crypto_verify(x,y);
  if (r == 0) 
  {
    if (memcmp(x,y,crypto_verify_BYTES)) return "different strings pass verify";
  } 
  else if (r == -1) 
  {
    if (!memcmp(x,y,crypto_verify_BYTES)) return "equal strings fail verify";
  } 
  else 
  {
    return "weird return value from verify";
  }
  return 0;
}

static char checksum[2];

int main(void)
{
  print("Starting test_crypto_verify()\r\n");

  long long tests;
  long long i;
  const char *c;

  x = (unsigned char*)calloc(crypto_verify_BYTES,1);
  if(!x) fail("allocation of x failed");
  y = (unsigned char*)calloc(crypto_verify_BYTES,1);
  if(!y) fail("allocation of y failed");

  print("Allocation Done.");

  for (tests = 0;tests < 100;++tests) 
  {
    printnum("Loop:", tests);

    randombytes(x,crypto_verify_BYTES);
    randombytes(y,crypto_verify_BYTES);

    c = check(); if (c) fail(c);
    for (i = 0;i < crypto_verify_BYTES;++i) y[i] = x[i];
    c = check(); if (c) fail(c);

    y[random() % crypto_verify_BYTES] = random();
    c = check(); if (c) fail(c);
    y[random() % crypto_verify_BYTES] = random();
    c = check(); if (c) fail(c);
    y[random() % crypto_verify_BYTES] = random();
    c = check(); if (c) fail(c);
  }

  checksum[0] = '0';
  checksum[1] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  free(x);
  free(y);

  fail("Done.");

  return 0;
}
