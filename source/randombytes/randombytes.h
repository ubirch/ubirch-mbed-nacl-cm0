#ifndef RANDOMBYTES_H
#define RANDOMBYTES_H

/*
 * Fill the buffer x with xlen bytes of randomness.
 * Returns 0 on success. On error, the contents of
 * x must NOT be used and assumed non-random.
 */
int randombytes (unsigned char *x,unsigned long long xlen);

#endif
