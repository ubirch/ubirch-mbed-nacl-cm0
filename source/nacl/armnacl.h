/*
 * File:    armnacl.h
 * Author:  Michael Hutter, Peter Schwabe, Andreas Schuler
 * Version: Tue Aug 12 08:23:16 2014 +0200
 * Public Domain
 */

#ifndef ARMNACL_H
#define ARMNACL_H
#define ARMNACL_VERSION "2017-09-07"

#ifdef __cplusplus
extern "C" {
#endif

typedef char crypto_int8;
typedef unsigned char crypto_uint8;
typedef short crypto_int16;
typedef unsigned short crypto_uint16;
typedef long crypto_int32;
typedef unsigned long crypto_uint32;
typedef long long crypto_int64;
typedef unsigned long long crypto_uint64;

#define crypto_auth_PRIMITIVE "hmacsha512256"
#define crypto_auth crypto_auth_hmacsha512256
#define crypto_auth_verify crypto_auth_hmacsha512256_verify
#define crypto_auth_BYTES crypto_auth_hmacsha512256_BYTES
#define crypto_auth_KEYBYTES crypto_auth_hmacsha512256_KEYBYTES
#define crypto_auth_hmacsha512256_BYTES 32
#define crypto_auth_hmacsha512256_KEYBYTES 32

extern int crypto_auth_hmacsha512256(unsigned char *, const unsigned char *, crypto_uint16, const unsigned char *);

extern int
crypto_auth_hmacsha512256_verify(const unsigned char *, const unsigned char *, crypto_uint16, const unsigned char *);


#define crypto_hashblocks_PRIMITIVE "sha512"
#define crypto_hashblocks crypto_hashblocks_sha512
#define crypto_hashblocks_STATEBYTES crypto_hashblocks_sha512_STATEBYTES
#define crypto_hashblocks_BLOCKBYTES crypto_hashblocks_sha512_BLOCKBYTES
#define crypto_hashblocks_sha512_STATEBYTES 64
#define crypto_hashblocks_sha512_BLOCKBYTES 128

extern int crypto_hashblocks_sha512(unsigned char *, const unsigned char *, crypto_uint16);

#define crypto_hash_PRIMITIVE "sha512"
#define crypto_hash crypto_hash_sha512
#define crypto_hash_BYTES crypto_hash_sha512_BYTES
#define crypto_hash_sha512_BYTES 64

extern int crypto_hash_sha512(unsigned char *, const unsigned char *, crypto_uint16);

#define crypto_sign_PRIMITIVE "ed25519"
#define crypto_sign crypto_sign_ed25519
#define crypto_sign_open crypto_sign_ed25519_open
#define crypto_sign_keypair crypto_sign_ed25519_keypair
#define crypto_sign_BYTES crypto_sign_ed25519_BYTES
#define crypto_sign_PUBLICKEYBYTES crypto_sign_ed25519_PUBLICKEYBYTES
#define crypto_sign_SECRETKEYBYTES crypto_sign_ed25519_SECRETKEYBYTES
#define crypto_sign_ed25519_BYTES 64
#define crypto_sign_ed25519_PUBLICKEYBYTES 32
#define crypto_sign_ed25519_SECRETKEYBYTES 64

extern int
crypto_sign_ed25519(unsigned char *, crypto_uint16 *, const unsigned char *, crypto_uint16, const unsigned char *);

extern int
crypto_sign_ed25519_open(unsigned char *, crypto_uint16 *, const unsigned char *, crypto_uint16, const unsigned char *);

extern int crypto_sign_ed25519_keypair(unsigned char *, unsigned char *);


#define crypto_verify_PRIMITIVE "16"
#define crypto_verify crypto_verify_16
#define crypto_verify_BYTES crypto_verify_16_BYTES
#define crypto_verify_16_BYTES 16

extern int crypto_verify_16(const unsigned char *, const unsigned char *);

#define crypto_verify_32_BYTES 32

extern int crypto_verify_32(const unsigned char *, const unsigned char *);

#ifdef __cplusplus
}
#endif

#endif
