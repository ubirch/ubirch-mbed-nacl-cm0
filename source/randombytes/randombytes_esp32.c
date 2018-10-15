//
// Created by wowa on 14.08.18.
//
/*!
 * @file
 * @brief Generate random numbers using the nRF51 hardware RNG
 *
 * @author Matthias L. Jugel
 * @date   2017-09-11
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
#ifdef __ESP32__
#include "esp_system.h"


void randombytes(unsigned char *x, unsigned long long xlen) {
    while (xlen > 0) {
        *x = (unsigned char) esp_random();
        x++;
        xlen--;
    }
}

#endif // __ESP32__

