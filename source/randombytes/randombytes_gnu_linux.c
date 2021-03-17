#include <sys/syscall.h>

#if defined(SYS_getrandom)

#include <sys/random.h>

void randombytes(unsigned char *x, unsigned long long xlen) {
    getrandom(x, xlen, 0);
}

#else

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void randombytes(unsigned char *x, unsigned long long xlen) {
    const int randomdata = open("/dev/urandom", O_RDONLY);
    if (randomdata < 0) {
        printf("randombytes failed opening /dev/urandom: %s\n", strerror(errno));
        exit(errno);
    } else {
        if (read(randomdata, x, xlen) < 0) {
            printf("randombytes failed reading from /dev/urandom: %s\n", strerror(errno));
            exit(errno);
        }
    }
}

#endif
