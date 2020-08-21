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
#ifdef NRF52

#include <stdint.h>
#include <nrf_sdm.h>
#include <nrf.h>

void randombytes(unsigned char *x, unsigned long long xlen) {
    uint8_t softdevice_enabled;

    sd_softdevice_isEnabled(&softdevice_enabled);
    if (softdevice_enabled == 1) {
        uint8_t bytes_available = 0;
        while(xlen > 0) {
            sd_rand_application_bytes_available_get(&bytes_available);
            if (bytes_available > 0) {
                sd_rand_application_vector_get(x, 1);
                x++;
                xlen--;
            }
        }
    } else {
        NRF_RNG->TASKS_START = 1;
        NRF_RNG->CONFIG = 1;

        NRF_RNG->EVENTS_VALRDY = 0;
        while(xlen > 0) {
            while (NRF_RNG->EVENTS_VALRDY == 0);
            *x = (uint8_t) NRF_RNG->VALUE;
            x++;
            xlen--;
        }

        NRF_RNG->TASKS_STOP = 1;
    }
}

#endif // NRF52

#ifdef NRF52840_XXAA

#include <stdint.h>
#include <nrf_sdm.h>
#include <nrf.h>

void randombytes(unsigned char *x, unsigned long long xlen) {
	uint8_t softdevice_enabled;

	sd_softdevice_is_enabled(&softdevice_enabled);
	if (softdevice_enabled == 1) {
		uint8_t bytes_available = 0;
		while(xlen > 0) {
			sd_rand_application_bytes_available_get(&bytes_available);
			if (bytes_available > 0) {
				sd_rand_application_vector_get(x, 1);
				x++;
				xlen--;
			}
		}
	} else {
		NRF_RNG->TASKS_START = 1;
		NRF_RNG->CONFIG = 1;

		NRF_RNG->EVENTS_VALRDY = 0;
		while(xlen > 0) {
			while (NRF_RNG->EVENTS_VALRDY == 0);
			*x = (uint8_t) NRF_RNG->VALUE;
			x++;
			xlen--;
		}

		NRF_RNG->TASKS_STOP = 1;
	}
}

#endif // NRF52

