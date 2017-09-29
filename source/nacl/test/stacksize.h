#ifndef STACKDEFS_H
#define STACKDEFS_H

#define MAXSTACK 2000
#define WRITE_CANARY(X) {p=X;while(p>= (X-MAXSTACK)) *(p--) = canary;}

unsigned int stack_count(unsigned char canary,volatile unsigned char *a);

#endif
