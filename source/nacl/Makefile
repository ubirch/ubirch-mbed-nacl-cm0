include ../config

CFLAGS  = -g -Wall -Wextra -Werror -mmcu=$(TARGET_DEVICE) -O3 -I../randombytes/ -I.. -I./include/ -DF_CPU=$(CPUFREQ) -mcall-prologues
CFLAGS_SMALL = -g -Wall -Wextra -Werror -mmcu=$(TARGET_DEVICE) -Os -I../randombytes/ -I.. -I./include/ -DF_CPU=$(CPUFREQ) -mcall-prologues

all: test speed stack

include ../test.mk
include ../speed.mk
include ../stack.mk


obj/libnacl.a: obj/crypto_stream/salsa20.o \
 							 obj/crypto_stream/xsalsa20.o \
 							 obj/crypto_core/hsalsa20.o \
 							 obj/crypto_core/salsa20.o \
 							 obj/crypto_verify/verify.o \
 							 obj/crypto_hashblocks/sha512.o \
 							 obj/crypto_hash/sha512.o \
 							 obj/crypto_auth/hmac.o \
 							 obj/crypto_onetimeauth/poly1305.o \
							 obj/shared/consts.o \
							 obj/shared/fe25519.o \
							 obj/shared/bigint.o \
 							 obj/crypto_scalarmult/curve25519.o \
 							 obj/crypto_dh/curve25519.o \
							 obj/crypto_secretbox/xsalsa20poly1305.o \
							 obj/crypto_box/curve25519xsalsa20poly1305.o \
							 obj/crypto_sign/ed25519.o \
							 obj/crypto_sign/ge25519.o \
							 obj/crypto_sign/sc25519.o
	$(AR) -ar cr obj/libnacl.a $^
	$(STRIP) -g --strip-unneeded obj/libnacl.a $^


obj/crypto_stream/%.o: crypto_stream/%.[cS]
	mkdir -p obj/crypto_stream
	$(CC) $(CFLAGS) -c $^ -o $@

obj/crypto_core/%.o: crypto_core/%.[cS]
	mkdir -p obj/crypto_core
	$(CC) $(CFLAGS) -c $^ -o $@

obj/crypto_verify/%.o: crypto_verify/%.[cS]
	mkdir -p obj/crypto_verify
	$(CC) $(CFLAGS) -c $^ -o $@

obj/crypto_hashblocks/%.o: crypto_hashblocks/%.[cS]
	mkdir -p obj/crypto_hashblocks
	$(CC) $(CFLAGS_SMALL) -c $^ -o $@

obj/crypto_hash/%.o: crypto_hash/%.[cS]
	mkdir -p obj/crypto_hash
	$(CC) $(CFLAGS_SMALL) -c $^ -o $@

obj/crypto_auth/%.o: crypto_auth/%.[cS]
	mkdir -p obj/crypto_auth
	$(CC) $(CFLAGS) -c $^ -o $@

obj/crypto_onetimeauth/%.o: crypto_onetimeauth/%.[cS]
	mkdir -p obj/crypto_onetimeauth
	$(CC) $(CFLAGS) -c $^ -o $@

obj/crypto_scalarmult/%.o: crypto_scalarmult/%.[cS]
	mkdir -p obj/crypto_scalarmult
	$(CC) $(CFLAGS) -c $^ -o $@

obj/crypto_dh/%.o: crypto_dh/%.[cS]
	mkdir -p obj/crypto_dh
	$(CC) $(CFLAGS) -c $^ -o $@

obj/crypto_secretbox/%.o: crypto_secretbox/%.[cS]
	mkdir -p obj/crypto_secretbox
	$(CC) $(CFLAGS) -c $^ -o $@

obj/crypto_box/%.o: crypto_box/%.[cS]
	mkdir -p obj/crypto_box
	$(CC) $(CFLAGS) -c $^ -o $@

obj/crypto_sign/%.o: crypto_sign/%.[cS]
	mkdir -p obj/crypto_sign
	$(CC) $(CFLAGS) -c $^ -o $@

obj/shared/invert.o: shared/invert.c
	mkdir -p obj/shared
	$(CC) $(CFLAGS_SMALL) -c $^ -o $@

obj/shared/pow2523.o: shared/pow2523.c
	mkdir -p obj/shared
	$(CC) $(CFLAGS_SMALL) -c $^ -o $@

obj/shared/%.o: shared/%.[cS]
	mkdir -p obj/shared
	$(CC) $(CFLAGS) -c $^ -o $@

obj/randombytes.o: ../randombytes/randombytes.c
	mkdir -p obj/
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	-rm -r obj/*
	-rm -r test/*
