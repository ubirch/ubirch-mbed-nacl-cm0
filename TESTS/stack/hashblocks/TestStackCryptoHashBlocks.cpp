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
}

#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"
#include "nacl/test/stacksize.h"
#include "../../testhelper.h"

using namespace utest::v1;

#define MAXTEST_BYTES 1024

unsigned char h[crypto_hashblocks_STATEBYTES];
unsigned char m[MAXTEST_BYTES];

unsigned int i,mlen;

unsigned int ctr=0,newctr;
unsigned char canary;
volatile unsigned char *p;

void TestStackCryptoHashBlocks() {
    print("Starting stack_crypto_hashblocks\r\n");

    volatile unsigned char a; /* Mark the beginning of the stack */

    for(i=0;i<5;i++)
    {
        canary = random();
        WRITE_CANARY(&a);
        crypto_hashblocks(h,m,0);
        newctr = MAXSTACK - stack_count(canary,&a);
        ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack("crypto_hashblocks",0,ctr);

    for(mlen=1;mlen<=MAXTEST_BYTES;mlen<<=1)
    {
        for(i=0;i<5;i++)
        {
            canary = random();
            WRITE_CANARY(&a);
            crypto_hashblocks(h,m,mlen);
            newctr = MAXSTACK - stack_count(canary,&a);
            ctr = (newctr>ctr)?newctr:ctr;
        }
        print_stack("crypto_hashblocks",mlen,ctr);
    }

    print("Done.");
}

utest::v1::status_t greentea_failure_handler(const Case *const source, const failure_t reason) {
    greentea_case_failure_abort_handler(source, reason);
    return STATUS_CONTINUE;
}

Case cases[] = {
Case("Test crypto-hash", TestStackCryptoHashBlocks, greentea_failure_handler),
};

utest::v1::status_t greentea_test_setup(const size_t number_of_cases) {
    GREENTEA_SETUP(300, "default_auto");
    return greentea_test_setup_handler(number_of_cases);
}

int main() {
    Specification specification(greentea_test_setup, cases, greentea_test_teardown_handler);
    Harness::run(specification);
}