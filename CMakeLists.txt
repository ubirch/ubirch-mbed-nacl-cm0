# This file is mainly for use with CLion, to make sure it picks up all
# the libraries and we can use syntax highlighting.
#
# DO NOT USE RUN! Use build (M-F9) on the target "compile".

cmake_minimum_required(VERSION 3.5)
if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/.mbed AND NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/yotta_targets)
    message(FATAL_ERROR
            "Please install for mbed-os 2 or 5\n  --> mbed-os 5: run 'mbed new .'\n  --> mbed-os 2: run 'yotta update'"
            )
endif()

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/.mbed)
    message(STATUS "BUILDING FOR MBED OS 2")
    # this is used in case we develop for mbed-os 2
    include(mbed2.cmake)
else()
    message(STATUS "BUILDING FOR MBED OS 5")
    # mbed-os 5
    include(mbed5.cmake)
endif()

include(lib.cmake)

add_executable(test-stack-crypto-hash
        TESTS/stack/hash/TestStackCryptoHash.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-stack-crypto-hash mbed-os libnacl)

add_executable(test-stack-crypto-hashblocks
        TESTS/stack/hashblocks/TestStackCryptoHashBlocks.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-stack-crypto-hashblocks mbed-os libnacl)

add_executable(test-stack-crypto-sign
        TESTS/stack/sign/TestStackCryptoSign.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-stack-crypto-sign mbed-os libnacl)

add_executable(test-stack-crypto-verify
        TESTS/stack/verify/TestStackCryptoVerify.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-stack-crypto-verify mbed-os libnacl)

add_executable(test-crypto-hash
        TESTS/crypto/hash/TestCryptoHash.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-crypto-hash mbed-os libnacl)

add_executable(test-crypto-hashblocks
        TESTS/crypto/hashblocks/TestCryptoHashBlocks.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-crypto-hashblocks mbed-os libnacl)

add_executable(test-crypto-sign
        TESTS/crypto/sign/TestCryptoSign.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-crypto-sign mbed-os libnacl)

add_executable(test-crypto-verify
        TESTS/crypto/verify/TestCryptoVerify.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-crypto-verify mbed-os libnacl)


# NaCl library tests
add_executable(stack_crypto_hash source/nacl/test/stack_crypto_hash.cpp)
target_link_libraries(stack_crypto_hash mbed-os libnacl)
add_executable(stack_crypto_hashblocks source/nacl/test/stack_crypto_hashblocks.cpp)
target_link_libraries(stack_crypto_hashblocks mbed-os libnacl)
add_executable(stack_crypto_sign source/nacl/test/stack_crypto_sign.cpp)
target_link_libraries(stack_crypto_sign mbed-os libnacl)
add_executable(stack_crypto_verify source/nacl/test/stack_crypto_verify.cpp)
target_link_libraries(stack_crypto_verify mbed-os libnacl)
add_executable(test_crypto_hash source/nacl/test/test_crypto_hash.cpp)
target_link_libraries(test_crypto_hash mbed-os libnacl)
add_executable(test_crypto_hashblocks source/nacl/test/test_crypto_hashblocks.cpp)
target_link_libraries(test_crypto_hashblocks mbed-os libnacl)
add_executable(test_crypto_sign source/nacl/test/test_crypto_sign.cpp)
target_link_libraries(test_crypto_sign mbed-os libnacl)
add_executable(test_crypto_verify source/nacl/test/test_crypto_verify.cpp)
target_link_libraries(test_crypto_verify mbed-os libnacl)

