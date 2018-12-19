# A μNaCl port for ARM Cortex M0

This is an implementation of the [NaCl](https://nacl.cr.yp.to/) API
for the ARM Cortex-M0. It is based on the AVR implementation of
[μNaCl](https://munacl.cryptojedi.org/curve25519-atmega.shtml).

## mbed-os 5

```bash
mbed add https://github.com/ubirch/ubirch-mbed-nacl-cm0
```

## mbed-os 2

To use this library with a [yotta](http://docs.yottabuild.org/) project
add this github repository as a dependency:

```json
{
  ...
  "dependencies": {
    "nacl": "ubirch/ubirch-mbed-nacl-cm0#v1.0.0"
  },
  ...
}
```

> About the `CMakeLists.txt` file. This is mainly used to get
> [CLion](https://www.jetbrains.com/clion/) to find headers and make the
> syntax highlighting useful. It includes `lib.cmake` which can be used
> in a another project and only adds the library sources.

## ESP32

To use this library within your esp32 project, you have to add it as a
git submodule to your components directory:

```bash
git submodule add https://github.com/ubirch/ubirch-mbed-nacl-cm0.git
```

Afterwards, copy the `esp32.cmake` file to `CMakeLists.txt` or make a link.
This way the cmake of your project will know and include all components
of this library.

## Testing

> The tests are long-running, so please be patient.

```bash
mbed new .
mbed target NRF52_DK
mbed toolchain GCC_ARM
mbed test -n 'tests-stack*,tests-crypto*'
```

These tests are the original tests that came with the library, adapted to run in the mbed test harness.

Test suites:
```
+------------------+---------------+-------------------------+--------+--------------------+-------------+
| target           | platform_name | test suite              | result | elapsed_time (sec) | copy_method |
+------------------+---------------+-------------------------+--------+--------------------+-------------+
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-crypto-hash       | OK     | 191.01             | default     |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-crypto-hashblocks | OK     | 203.61             | default     |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-crypto-sign       | OK     | 329.61             | default     |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-crypto-verify     | OK     | 40.07              | default     |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-stack-hash        | OK     | 40.14              | default     |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-stack-hashblocks  | OK     | 40.23              | default     |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-stack-sign        | OK     | 180.06             | default     |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-stack-verify      | OK     | 40.68              | default     |
+------------------+---------------+-------------------------+--------+--------------------+-------------+
```

Individual test results:
```
+------------------+---------------+-------------------------+------------------------------+--------+--------+--------+--------------------+
| target           | platform_name | test suite              | test case                    | passed | failed | result | elapsed_time (sec) |
+------------------+---------------+-------------------------+------------------------------+--------+--------+--------+--------------------+
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-crypto-hash       | Test crypto-hash             | 1      | 0      | OK     | 152.57             |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-crypto-hashblocks | Test crypto-hashblocks       | 1      | 0      | OK     | 164.14             |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-crypto-sign       | Test crypto-sign             | 1      | 0      | OK     | 291.11             |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-crypto-verify     | Test crypto-verify           | 1      | 0      | OK     | 2.47               |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-stack-hash        | Test stack-crypto-hash       | 1      | 0      | OK     | 1.47               |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-stack-hashblocks  | Test stack-crypto-hashblocks | 1      | 0      | OK     | 1.16               |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-stack-sign        | Test stack-crypto-sign       | 1      | 0      | OK     | 137.2              |
| NRF52_DK-GCC_ARM | NRF52_DK      | tests-stack-verify      | Test stack-crypto-verify     | 1      | 0      | OK     | 0.68               |
+------------------+---------------+-------------------------+------------------------------+--------+--------+--------+--------------------+

```

# Credits

The port was done by Andreas Schuler for [ubirch GmbH](http://ubirch.com) and
adapted for use with [mbed](https://mbed.org) and [Calliope mini](http://calliope.cc)
by [Matthias L. Jugel](https://github.com/thinkberg).

# Status

> ⚡ *Work in progress.* An audit for this implementation is pending.

# License

This work is available under the [Apache License](LICENSE)

```
Copyright 2017 ubirch GmbH

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
````
