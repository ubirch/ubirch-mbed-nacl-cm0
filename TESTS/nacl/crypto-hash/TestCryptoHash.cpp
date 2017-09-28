/*
 * µNaCl library tests (included with original lib).
 *
 * @author Matthias L. Jugel
 * @date 2017-07-25
 *
 * Copyright 2017 ubirch GmbH (https://ubirch.com)
 *
 * ```
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ```
 */

#include <sdk_common.h>
#include <softdevice/s132/headers/nrf_soc.h>
#include <softdevice/s132/headers/nrf_sdm.h>
#include "mbed.h"

extern "C" {
#include "nacl/armnacl.h"
#include "randombytes/randombytes.h"
}

#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"

using namespace utest::v1;

#define MAXTEST_BYTES (1024 + crypto_hash_BYTES)

static unsigned char *h;
static unsigned char *h2;
static unsigned char *m;
static unsigned char *m2;

static char checksum[crypto_hash_BYTES * 2 + 1];

#define fail(m) {TEST_ASSERT_MESSAGE(false, m)}
#define print printf
#define printnum(s, n) printf((s " %llu\r\n"), (n))

long random() {
    static uint32_t r;
    randombytes((unsigned char *) (&r), 4);
    return r;
}

void TestCryptoHash() {
    long long i;
    long long j;

    print("Starting test_crypto_hash()\r\n");

    h = (unsigned char *) calloc(crypto_hash_BYTES + 32, 1);
    if (!h) fail("allocation of h failed");
    h2 = (unsigned char *) calloc(crypto_hash_BYTES + 32, 1);
    if (!h2) fail("allocation of h2 failed");
    m = (unsigned char *) calloc(MAXTEST_BYTES + 32, 1);
    if (!m) fail("allocation of m failed");
    m2 = (unsigned char *) calloc(MAXTEST_BYTES + 32, 1);
    if (!m2) fail("allocation of m2 failed");

    print("Allocation done.\r\n");

    h += 16;
    h2 += 16;
    m += 16;
    m2 += 16;


    for (i = 0; i < MAXTEST_BYTES; ++i) {
        //printnum("Loop:", i);

        long long hlen = crypto_hash_BYTES;
        long long mlen = i;
        for (j = -16; j < 0; ++j) h[j] = random();
        for (j = hlen; j < hlen + 16; ++j) h[j] = random();
        for (j = -16; j < hlen + 16; ++j) h2[j] = h[j];
        for (j = -16; j < 0; ++j) m[j] = random();
        for (j = mlen; j < mlen + 16; ++j) m[j] = random();
        for (j = -16; j < mlen + 16; ++j) m2[j] = m[j];
        if (crypto_hash(h, m, mlen) != 0) fail("crypto_hash returns nonzero");
        for (j = -16; j < mlen + 16; ++j) if (m2[j] != m[j]) fail("crypto_hash writes to input");
        for (j = -16; j < 0; ++j) if (h2[j] != h[j]) fail("crypto_hash writes before output");
        for (j = hlen; j < hlen + 16; ++j) if (h2[j] != h[j]) fail("crypto_hash writes after output");
        if (crypto_hash(m2, m2, mlen) != 0) fail("crypto_hash returns nonzero");
        for (j = 0; j < hlen; ++j) if (m2[j] != h[j]) fail("crypto_hash does not handle overlap");
        for (j = 0; j < mlen; ++j) m[j] ^= h[j % hlen];
        m[mlen] = h[0];
    }
    if (crypto_hash(h, m, MAXTEST_BYTES) != 0) fail("crypto_hash returns nonzero");

    for (i = 0; i < crypto_hash_BYTES; ++i) {
        //printnum("chksumloop:", i);

        checksum[2 * i] = "0123456789abcdef"[15 & (h[i] >> 4)];
        checksum[2 * i + 1] = "0123456789abcdef"[15 & h[i]];
    }
    checksum[2 * i] = 0;

    print("Checksum: ");
    print(checksum);
    print("\n");

    h -= 16;
    h2 -= 16;
    m -= 16;
    m2 -= 16;

    free(h);
    free(h2);
    free(m);
    free(m2);
}

utest::v1::status_t greentea_failure_handler(const Case *const source, const failure_t reason) {
    greentea_case_failure_abort_handler(source, reason);
    return STATUS_CONTINUE;
}

Case cases[] = {
Case("Test crypto-hash", TestCryptoHash, greentea_failure_handler),
};

utest::v1::status_t greentea_test_setup(const size_t number_of_cases) {
    GREENTEA_SETUP(300, "default_auto");
    return greentea_test_setup_handler(number_of_cases);
}

int main() {
    Specification specification(greentea_test_setup, cases, greentea_test_teardown_handler);
    Harness::run(specification);
}