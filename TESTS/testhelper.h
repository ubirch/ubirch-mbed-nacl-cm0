#ifndef __TEST_HELPER_H__
#define __TEST_HELPER_H__

extern "C" {
#include "randombytes/randombytes.h"
}

#include <cstdio>

#define fail(m) {TEST_ASSERT_MESSAGE(false, m)}
#define print printf
#define printnum(s, n) printf((s " %llu\r\n"), (n))
#define fail(m) {TEST_ASSERT_MESSAGE(false, m)}
#define printbytes(s, x, l) {printf(s);for(int i = 0; i < l; i++) printf("%02x", x[i]);}
#define print_stack(p, b, s) {printf(p);if(b != (unsigned int)-1) printf("[%x] ",b); printf("%d stack bytes\r\n",s);}

inline long random() {
    static uint32_t r;
    randombytes((unsigned char *) (&r), 4);
    return r;
}

#endif