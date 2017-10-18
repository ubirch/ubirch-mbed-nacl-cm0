#ifndef __TEST_HELPER_H__
#define __TEST_HELPER_H__

extern "C" {
#include "randombytes/randombytes.h"
}

#include <cstdio>

// the default random() returns a long value, which creates problems with the
// test routines as it does not fit into the unsigned char and creates a stack overflow
inline unsigned char test_random() {
    static uint32_t r;
    randombytes((unsigned char *) (&r), 4);
    return (unsigned char) r & 0xff;
}

#define fail(m)                 {TEST_ASSERT_MESSAGE(false, (m))}
#define print(...)              printf(__VA_ARGS__)
#define printnum(s, n)          printf((s " %llu\r\n"), (n))
#define printbytes(s, x, l)     {printf(s);for(int i = 0; i < (int)(l); i++) printf("%02x", (x)[i]);}
#define print_stack(p, b, s)    {printf(p);if((b) != (unsigned int)-1) printf(" [%x]",(b)); printf(" %d stack bytes\r\n",(s));}
#define random()                test_random()


#endif