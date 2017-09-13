/*
 * File:    test/test_crypto_hashblocks.c
 * Author:  Michael Hutter, Peter Schwabe, Andreas Schuler
 * Version: Tue Aug 5 09:35:45 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_hashblocks/try.c version 20110424 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>

extern "C" {
#include "nacl/armnacl.h"
#include "randombytes/randombytes.h"
}

#include "print.h"
#include "random.h"


#define MAXTEST_BYTES (1024 + crypto_hashblocks_STATEBYTES)

static unsigned char *h;
static unsigned char *h2;
static unsigned char *m;
static unsigned char *m2;

char checksum[crypto_hashblocks_STATEBYTES * 2 + 1];

int main(void)
{
  print("Starting test_crypto_hashblocks\r\n");

  long long i;
  long long j;

  h  = (unsigned char*)calloc(crypto_hashblocks_STATEBYTES+32,1);
  if(!h) fail("allocation of h failed");
  h2 = (unsigned char*)calloc(crypto_hashblocks_STATEBYTES+32,1);
  if(!h2) fail("allocation of h2 failed");
  m  = (unsigned char*)calloc(MAXTEST_BYTES+32,1);
  if(!m) fail("allocation of m failed");
  m2 = (unsigned char*)calloc(MAXTEST_BYTES+32,1);
  if(!m2) fail("allocation of m2 failed");

  print("Allocation complete.");

  h  += 16;
  h2 += 16;
  m  += 16;
  m2 += 16;

  for (i = 0;i < MAXTEST_BYTES;++i) 
  {
    printnum("Loop:",i);

    long long hlen = crypto_hashblocks_STATEBYTES;
    long long mlen = i;
    for (j = -16;j < 0;++j) h[j] = random();
    for (j = hlen;j < hlen + 16;++j) h[j] = random();
    for (j = -16;j < hlen + 16;++j) h2[j] = h[j];
    for (j = -16;j < 0;++j) m[j] = random();
    for (j = mlen;j < mlen + 16;++j) m[j] = random();
    for (j = -16;j < mlen + 16;++j) m2[j] = m[j];
    if (crypto_hashblocks(h,m,mlen) != mlen % crypto_hashblocks_BLOCKBYTES) fail("crypto_hashblocks returns wrong remaining length");
    for (j = -16;j < mlen + 16;++j) if (m2[j] != m[j]) fail("crypto_hashblocks writes to input");
    for (j = -16;j < 0;++j) if (h2[j] != h[j]) fail("crypto_hashblocks writes before output");
    for (j = hlen;j < hlen + 16;++j) if (h2[j] != h[j]) fail("crypto_hashblocks writes after output");
    for (j = 0;j < hlen;++j) m2[j] = h2[j];
    if (crypto_hashblocks(h2,m2,mlen) != mlen % crypto_hashblocks_BLOCKBYTES) fail("crypto_hashblocks returns wrong remaining length");
    if (crypto_hashblocks(m2,m2,mlen) != mlen % crypto_hashblocks_BLOCKBYTES) fail("crypto_hashblocks returns wrong remaining length");
    for (j = 0;j < hlen;++j) if (m2[j] != h2[j]) fail("crypto_hashblocks does not handle overlap");
    for (j = 0;j < mlen;++j) m[j] ^= h[j % hlen];
    m[mlen] = h[0];
  }
  if (crypto_hashblocks(h,m,MAXTEST_BYTES) != MAXTEST_BYTES % crypto_hashblocks_BLOCKBYTES) fail("crypto_hashblocks returns wrong remaining length");

  for (i = 0;i < crypto_hashblocks_STATEBYTES;++i) {
    printnum("ChkSum:",i);

    checksum[2 * i] = "0123456789abcdef"[15 & (h[i] >> 4)];
    checksum[2 * i + 1] = "0123456789abcdef"[15 & h[i]];
  }
  checksum[2 * i] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  h  -= 16;
  h2 -= 16;
  m  -= 16;
  m2 -= 16;

  free(h);
  free(h2);
  free(m);
  free(m2);

  fail("Done.");
  return 0;
}
