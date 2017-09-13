/*
 * File:    test/test_crypto_sign.c
 * Author:  Michael Hutter, Peter Schwabe, Andreas Schuler
 * Version: 2017-09-07
 * Public Domain
 */

/*
 * Based on crypto_sign/try.c version 20111119 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>

extern "C" {
#include "nacl/armnacl.h"
#include "randombytes/randombytes.h"
}

#include "print.h"
#include "random.h"

#define MAXTEST_BYTES 80


static unsigned char *pk; long long pklen; static unsigned char *pk2;
static unsigned char *sk; long long sklen; static unsigned char *sk2;
static unsigned char *m; crypto_uint16 mlen; static unsigned char *m2;
static unsigned char *sm; crypto_uint16 smlen; static unsigned char *sm2;
static unsigned char *t; crypto_uint16 tlen; static unsigned char *t2;


static unsigned char chain[37]; long long chainlen = 37;
char checksum[37 * 2 + 1];

int main(void)
{
  long long mlen;
  long long i;
  long long j;
  long long loops;

  print("Starting test_crypto_sign()\r\n");

  pklen = crypto_sign_PUBLICKEYBYTES;
  sklen = crypto_sign_SECRETKEYBYTES;

  pk  = (unsigned char*)calloc(pklen+32,1);
  if(!pk) fail("allocation of pk failed");
  sk  = (unsigned char*)calloc(sklen+32,1);
  if(!sk) fail("allocation of sk failed");
  m   = (unsigned char*)calloc(MAXTEST_BYTES + crypto_sign_BYTES+32,1);
  if(!m) fail("allocation of m failed");
  sm  = (unsigned char*)calloc(MAXTEST_BYTES + crypto_sign_BYTES+32,1);
  if(!sm) fail("allocation of sm failed");
  t   = (unsigned char*)calloc(MAXTEST_BYTES + crypto_sign_BYTES+32,1);
  if(!t) fail("allocation of t failed");
  pk2 = (unsigned char*)calloc(pklen+32,1);
  if(!pk2) fail("allocation of pk2 failed");
  sk2 = (unsigned char*)calloc(sklen+32,1);
  if(!sk2) fail("allocation of sk2 failed");
  m2  = (unsigned char*)calloc(MAXTEST_BYTES + crypto_sign_BYTES+32,1);
  if(!m2) fail("allocation of sm2 failed");
  sm2 = (unsigned char*)calloc(MAXTEST_BYTES + crypto_sign_BYTES+32,1);
  if(!sm2) fail("allocation of sm2 failed");
  t2  = (unsigned char*)calloc(MAXTEST_BYTES + crypto_sign_BYTES+32,1);
  if(!t2) fail("allocation of t2 failed");

  print("Allocation complete!\r\n");

  pk  += 16;
  sk  += 16;
  m   += 16;
  sm  += 16;
  t   += 16;
  pk2 += 16;
  sk2 += 16;
  m2  += 16;
  sm2 += 16;
  t2  += 16;


  //for (loops = 0;loops < 10;++loops) 
  for (loops = 0;loops < 2;++loops) 
  {
	 printnum("loops:", loops);

    for (j = -16;j < 0;++j) sk2[j] = sk[j] = random();
    for (j = 0;j < sklen + 16;++j) sk2[j] = sk[j] = random();
    for (j = -16;j < 0;++j) pk2[j] = pk[j] = random();
    for (j = 0;j < pklen + 16;++j) pk2[j] = pk[j] = random();
    if (crypto_sign_keypair(pk,sk) != 0) fail("crypto_sign_keypair returns nonzero");
    for (j = -16;j < 0;++j) if (pk[j] != pk2[j]) fail("crypto_sign_keypair writes before pk");
    for (j = pklen;j < pklen + 16;++j) if (pk[j] != pk2[j]) fail("crypto_sign_keypair writes after pk");
    for (j = -16;j < 0;++j) if (sk[j] != sk2[j]) fail("crypto_sign_keypair writes before sk");
    for (j = sklen;j < sklen + 16;++j) if (sk[j] != sk2[j]) fail("crypto_sign_keypair writes after sk");
  
    for (mlen = 0;mlen < MAXTEST_BYTES;mlen += 1 + (mlen / 16)) 
    {
      printnum("mlen:", mlen);

      for (j = -16;j < 0;++j) m2[j] = m[j] = random();
      for (j = mlen;j < mlen + 16;++j) m2[j] = m[j] = random();
      randombytes(m,mlen);
      if (mlen > 0)
        for (j = 0;j < chainlen;++j) m[j % mlen] ^= chain[j];
      for (j = 0;j < mlen;++j) m2[j] = m[j];
      for (j = -16;j < 0;++j) pk2[j] = pk[j];
      for (j = 0;j < pklen + 16;++j) pk2[j] = pk[j];
      for (j = -16;j < 0;++j) sk2[j] = sk[j];
      for (j = 0;j < sklen + 16;++j) sk2[j] = sk[j];
      for (j = -16;j < 0;++j) sm2[j] = sm[j] = random();
      for (j = 0;j < mlen + crypto_sign_BYTES + 16;++j) sm2[j] = sm[j] = random();
  
      if (crypto_sign(sm,&smlen,m,mlen,sk) != 0) fail("crypto_sign returns nonzero");
      if (smlen > mlen + crypto_sign_BYTES) fail("crypto_sign returns more than crypto_sign_BYTES extra bytes");
      if (smlen == 0) fail("crypto_sign returns empty message");
      for (j = -16;j < 0;++j) if (pk[j] != pk2[j]) fail("crypto_sign writes before pk 1");
      for (j = 0;j < pklen + 16;++j) if (pk[j] != pk2[j]) fail("crypto_sign overwrites pk 1");
      for (j = -16;j < 0;++j) if (sk[j] != sk2[j]) fail("crypto_sign writes before sk 1");
      for (j = 0;j < sklen + 16;++j) if (sk[j] != sk2[j]) fail("crypto_sign overwrites sk 1");
      for (j = -16;j < 0;++j) if (m[j] != m2[j]) fail("crypto_sign writes before m 1");
      for (j = 0;j < mlen + 16;++j) if (m[j] != m2[j]) fail("crypto_sign overwrites m 1");
      for (j = -16;j < 0;++j) if (sm[j] != sm2[j]) fail("crypto_sign writes before sm 1");
      for (j = smlen;j < smlen + 16;++j) if (sm[j] != sm2[j]) fail("crypto_sign writes after sm 1");

      for (j = 0;j < smlen;++j) chain[j % chainlen] ^= sm[j];
  
      for (j = -16;j < 0;++j) sm2[j] = sm[j];
      for (j = 0;j < smlen + 16;++j) sm2[j] = sm[j];
      for (j = -16;j < 0;++j) t2[j] = t[j] = random();
      for (j = 0;j < smlen + 16;++j) t2[j] = t[j] = random();
  
      if (crypto_sign_open(t,&tlen,sm,smlen,pk) != 0) fail("crypto_sign_open returns nonzero");
      if (tlen != mlen) fail("crypto_sign_open does not match length");
      for (i = 0;i < tlen;++i)
        if (t[i] != m[i])
          fail("crypto_sign_open does not match contents");
      for (j = -16;j < 0;++j) if (pk[j] != pk2[j]) fail("crypto_sign_open writes before pk 2");
      for (j = 0;j < pklen + 16;++j) if (pk[j] != pk2[j]) 
      {
        printbytes("pk",pk, pklen);
        printbytes("pk2",pk2, pklen);
        fail("crypto_sign_open overwrites pk 2");
      }
      for (j = -16;j < 0;++j) if (sk[j] != sk2[j]) fail("crypto_sign_open writes before sk 2");
      for (j = 0;j < sklen + 16;++j) if (sk[j] != sk2[j]) fail("crypto_sign_open overwrites sk 2");
      for (j = -16;j < 0;++j) if (sm[j] != sm2[j]) fail("crypto_sign_open writes before sm 2");
      for (j = 0;j < smlen + 16;++j) if (sm[j] != sm2[j]) fail("crypto_sign_open overwrites sm 2");
      for (j = -16;j < 0;++j) if (t[j] != t2[j]) fail("crypto_sign_open writes before t 2");
      for (j = smlen;j < smlen + 16;++j) if (t[j] != t2[j]) fail("crypto_sign_open writes after t 2");
  
      j = random() % smlen;
      sm[j] ^= 1;
      for (j = -16;j < 0;++j) sm2[j] = sm[j];
      for (j = 0;j < smlen + 16;++j) sm2[j] = sm[j];
      for (j = -16;j < 0;++j) t2[j] = t[j] = random();
      for (j = 0;j < smlen + 16;++j) t2[j] = t[j] = random();
      if (crypto_sign_open(t,&tlen,sm,smlen,pk) == 0) {
        if (tlen != mlen) fail("crypto_sign_open allows trivial forgery of length");
        for (i = 0;i < tlen;++i)
          if (t[i] != m[i])
            fail("crypto_sign_open allows trivial forgery of contents");
      }
      for (j = -16;j < 0;++j) if (pk[j] != pk2[j]) fail("crypto_sign_open overwrites pk 3");
      for (j = 0;j < pklen + 16;++j) if (pk[j] != pk2[j]) fail("crypto_sign_open overwrites pk 3");
      for (j = -16;j < 0;++j) if (sk[j] != sk2[j]) fail("crypto_sign_open overwrites sk 3");
      for (j = 0;j < sklen + 16;++j) if (sk[j] != sk2[j]) fail("crypto_sign_open overwrites sk 3");
      for (j = -16;j < 0;++j) if (sm[j] != sm2[j]) fail("crypto_sign_open overwrites sm 3");
      for (j = 0;j < smlen + 16;++j) if (sm[j] != sm2[j]) fail("crypto_sign_open overwrites sm 3");
      for (j = -16;j < 0;++j) if (t[j] != t2[j]) fail("crypto_sign_open writes before t 3");
      for (j = smlen;j < smlen + 16;++j) if (t[j] != t2[j]) fail("crypto_sign_open writes after t 3");
      sm[j] ^= 1;
    }
  }

  for (i = 0;i < chainlen;++i) {
    checksum[2 * i] = "0123456789abcdef"[15 & (chain[i] >> 4)];
    checksum[2 * i + 1] = "0123456789abcdef"[15 & chain[i]];
  }
  checksum[2 * i] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  pk  -= 16;
  sk  -= 16;
  m   -= 16;
  sm  -= 16;
  t   -= 16;
  pk2 -= 16;
  sk2 -= 16;
  m2  -= 16;
  sm2 -= 16;
  t2  -= 16;

  free(pk);
  free(sk);
  free(m);
  free(sm);
  free(t);
  free(pk2);
  free(sk2);
  free(m2);
  free(sm2);
  free(t2);

  print("Test done successful.\r\n");

  return 0;
}

