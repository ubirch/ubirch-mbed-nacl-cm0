/*
 * File:    avrnacl_8bitc/crypto_sign/ed25519.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Tue Aug 12 08:23:16 2014 +0200
 * Public Domain
 */

#include "../armnacl.h"

#include "ge25519.h"
#include "sc25519.h"
#include "../../randombytes/randombytes.h"


static void get_hram(unsigned char *hram, const unsigned char *sm, const unsigned char *pk, unsigned char *playground, unsigned long long smlen)
{
  unsigned long long i;

  for (i =  0;i < 32;++i)    playground[i] = sm[i];
  for (i = 32;i < 64;++i)    playground[i] = pk[i-32];
  for (i = 64;i < smlen;++i) playground[i] = sm[i];

  crypto_hash_sha512(hram,playground,smlen);
}


int crypto_sign_ed25519_keypair(
    unsigned char *pk,
    unsigned char *sk
    )
{
  sc25519 scsk;
  ge25519 gepk;
  unsigned char extsk[64];
  int i;

  if (randombytes(sk, 32) != 0) {
    return (-1);
  }

  crypto_hash_sha512(extsk, sk, 32);
  extsk[0] &= 248;
  extsk[31] &= 127;
  extsk[31] |= 64;

  sc25519_from32bytes(&scsk,extsk);

  ge25519_scalarmult_base(&gepk, &scsk);
  ge25519_pack(pk, &gepk);
  for(i=0;i<32;i++)
    sk[32 + i] = pk[i];
  return 0;
}

int crypto_sign_ed25519(
    unsigned char *sm,crypto_uint16 *smlen,
    const unsigned char *m,crypto_uint16 mlen,
    const unsigned char *sk
    )
{
  sc25519 sck, scs, scsk;
  ge25519 ger;
  unsigned char r[32];
  unsigned char s[32];
  unsigned char extsk[64];
  unsigned long long i;
  unsigned char hmg[crypto_hash_sha512_BYTES]; //64 bytes
  unsigned char hram[crypto_hash_sha512_BYTES]; //64 bytes

  crypto_hash_sha512(extsk, sk, 32);
  extsk[0] &= 248;
  extsk[31] &= 127;
  extsk[31] |= 64;

  *smlen = mlen+64;
  for(i=0;i<mlen;i++)
    sm[64 + i] = m[i];
  for(i=0;i<32;i++)
    sm[32 + i] = extsk[32+i];

  crypto_hash_sha512(hmg, sm+32, mlen+32); // Generate k as h(extsk[32],...,extsk[63],m) 

  // Computation of R 
  sc25519_from64bytes(&sck, hmg);
  ge25519_scalarmult_base(&ger, &sck);
  ge25519_pack(r, &ger);

  // Computation of s 
  for(i=0;i<32;i++)
    sm[i] = r[i];

  get_hram(hram, sm, sk+32, sm, mlen+64);

  sc25519_from64bytes(&scs, hram);
  sc25519_from32bytes(&scsk, extsk);
  sc25519_mul(&scs, &scs, &scsk);

  sc25519_add(&scs, &scs, &sck);

  sc25519_to32bytes(s,&scs); // cat s
  for(i=0;i<32;i++)
    sm[32 + i] = s[i];

  return 0;
}

int crypto_sign_ed25519_open(
    unsigned char *m,crypto_uint16 *mlen,
    const unsigned char *sm,crypto_uint16 smlen,
    const unsigned char *pk
    )
{
  unsigned int i, ret;
  unsigned char t2[32];
  ge25519 get1, get2;
  sc25519 schram, scs;
  unsigned char hram[crypto_hash_sha512_BYTES];

  if (smlen < crypto_sign_ed25519_BYTES) return -1;
  if (ge25519_unpackneg_vartime(&get1, pk)) return -1;

  get_hram(hram,sm,pk,m,smlen);

  sc25519_from64bytes(&schram, hram);

  sc25519_from32bytes(&scs, sm+32);

  ge25519_double_scalarmult_vartime(&get2, &get1, &schram, &ge25519_base, &scs);
  ge25519_pack(t2, &get2);

  ret = crypto_verify_32(sm, t2);

  if (!ret)
  {
    for(i=0;i<((unsigned int)(smlen))-crypto_sign_ed25519_BYTES;i++)
      m[i] = sm[i + crypto_sign_ed25519_BYTES];
    *mlen = smlen-crypto_sign_ed25519_BYTES;
  }
  else
  {
    for(i=0;i<((unsigned int)(smlen))-crypto_sign_ed25519_BYTES;i++)
      m[i] = 0;
    *mlen = (crypto_uint16) -1;
  }
  return ret;
}
