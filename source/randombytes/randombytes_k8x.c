/*!
 * @file
 * @brief Generate random numbers using the TRNG of the K8x MCU family
 *
 * @author Matthias L. Jugel
 * @date   2017-12-20
 *
 * @copyright &copy; 2017 ubirch GmbH (https://ubirch.com)
 *
 * @section LICENSE
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
#ifdef TARGET_K82F

#include <randombytes.h>
#include <hal/trng_api.h>
#include <fsl_trng.h>
#include <stdlib.h>

static bool initialized = false;

void randombytes(unsigned char *x, unsigned long long xlen) {
    if (!initialized) {
        trng_config_t trngConfig;
        initialized = (TRNG_GetDefaultConfig(&trngConfig) == kStatus_Success && TRNG_Init(TRNG0, &trngConfig));;
    }

    if (TRNG_GetRandomData(TRNG0, x, (size_t) xlen) != kStatus_Success)
        random();
}

#endif