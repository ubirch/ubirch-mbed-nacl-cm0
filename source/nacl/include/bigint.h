#ifndef BIGINT_H
#define BIGINT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Arithmetic on big integers represented as arrays of unsigned char in radix 2^256 */

#define bigint_add avrnacl_bigint_add
#define bigint_sub avrnacl_bigint_sub
#define bigint_mul avrnacl_bigint_mul
#define bigint_mul32 avrnacl_bigint_mul32
#define bigint_cmov avrnacl_bigint_cmov

unsigned char bigint_add(unsigned char *r, const unsigned char *a, const unsigned char *b, unsigned int len);

unsigned char bigint_sub(unsigned char *r, const unsigned char *a, const unsigned char *b, unsigned int len);

void bigint_mul(unsigned char *r, const unsigned char *a, const unsigned char *b, unsigned int len);

void bigint_mul32(unsigned char *r, const unsigned char *a, const unsigned char *b);

void bigint_cmov(unsigned char *r, const unsigned char *x, unsigned char b, unsigned int len);

#ifdef __cplusplus
}
#endif

#endif
