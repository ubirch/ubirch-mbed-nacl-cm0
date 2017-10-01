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
#include "mbed.h"

extern "C" {
#include "nacl/armnacl.h"
}

#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"
#include "../../testhelper.h"

using namespace utest::v1;

static unsigned char *x;
static unsigned char *y;


static const char *check(void)
{
    int r = crypto_verify(x,y);
    if (r == 0)
    {
        if (memcmp(x,y,crypto_verify_BYTES)) return "different strings pass verify";
    }
    else if (r == -1)
    {
        if (!memcmp(x,y,crypto_verify_BYTES)) return "equal strings fail verify";
    }
    else
    {
        return "weird return value from verify";
    }
    return 0;
}

static char checksum[2];

void TestCryptoVerify(void)
{
    print("Starting test_crypto_verify()\r\n");

    long long tests;
    long long i;
    const char *c;

    x = (unsigned char*)calloc(crypto_verify_BYTES,1);
    if(!x) fail("allocation of x failed");
    y = (unsigned char*)calloc(crypto_verify_BYTES,1);
    if(!y) fail("allocation of y failed");

    print("Allocation Done.");

    for (tests = 0;tests < 100;++tests)
    {
        printnum("Loop:", tests);

        randombytes(x,crypto_verify_BYTES);
        randombytes(y,crypto_verify_BYTES);

        c = check(); if (c) fail(c);
        for (i = 0;i < crypto_verify_BYTES;++i) y[i] = x[i];
        c = check(); if (c) fail(c);

        y[random() % crypto_verify_BYTES] = random();
        c = check(); if (c) fail(c);
        y[random() % crypto_verify_BYTES] = random();
        c = check(); if (c) fail(c);
        y[random() % crypto_verify_BYTES] = random();
        c = check(); if (c) fail(c);
    }

    checksum[0] = '0';
    checksum[1] = 0;

    print("Checksum: ");
    print(checksum);
    print("\n");

    free(x);
    free(y);

    printf("Done.");
}


utest::v1::status_t greentea_failure_handler(const Case *const source, const failure_t reason) {
    greentea_case_failure_abort_handler(source, reason);
    return STATUS_ABORT;
}

Case cases[] = {
Case("Test crypto-verify", TestCryptoVerify, greentea_failure_handler),
};

utest::v1::status_t greentea_test_setup(const size_t number_of_cases) {
    GREENTEA_SETUP(60, "default_auto");
    return greentea_test_setup_handler(number_of_cases);
}

int main() {
    Specification specification(greentea_test_setup, cases, greentea_test_teardown_handler);
    Harness::run(specification);
}