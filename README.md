# A μNaCl port for ARM Cortex M0

This is an implementation of the [NaCl](https://nacl.cr.yp.to/) API
for the ARM Cortex-M0. It is based on the AVR implementation of
[μNaCl](https://munacl.cryptojedi.org/curve25519-atmega.shtml).

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
