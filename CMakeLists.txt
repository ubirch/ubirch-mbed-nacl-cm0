# This file is mainly for use with CLion, to make sure it picks up all
# the libraries and we can use syntax highlighting.
#
# DO NOT USE RUN! Use build (M-F9) on the target "compile".

cmake_minimum_required(VERSION 3.5)
if(EXISTS .mbed)
    # this is used in case we develop for mbed-os 2
    include(mbed2.cmake)
else()
    # mbed-os 5
    set(CMAKE_BUILD_TYPE Debug)

    project(ubirch-mbed-nrf52-storage C CXX)
    set(CMAKE_CXX_STANDARD 98)

    # == MBED OS 5 settings ==
    set(PLATFORM TARGET_NORDIC/TARGET_NRF5)
    set(MCU NRF52832)
    set(TARGET MCU_NRF52832)
    set(BOARD NRF52_DK)

    set(FEATURES frameworks)

    add_definitions(
            -DTOOLCHAIN_GCC
            -DNRF52
            -D${MCU}
            -DTARGET_${TARGET}
            -DTARGET_${BOARD}
            -DMBED_CONF_RTOS_PRESENT
            -DMBED_CONF_NSAPI_PRESENT
            -DMBED_CONF_EVENTS_PRESENT
            -D__MBED__
            -DDEVICE_SLEEP
            -DDEVICE_RTC
            -DDEVICE_I2C
            -DDEVICE_SPI
            -DDEVICE_SERIAL
            -DDEVICE_TRNG
            -DDEVICE_INTERRUPTIN
            -DMBED_CONF_EVENTS_PRESENT=1
            -DMBED_CONF_RTOS_PRESENT=1
            -DMBED_CONF_PLATFORM_STDIO_BAUD_RATE=9600
            -DMBED_CONF_NSAPI_PRESENT=1
            -DMBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE=9600
            -DMBED_CONF_PLATFORM_STDIO_FLUSH_AT_EXIT=0
            -DMBED_CONF_PLATFORM_STDIO_CONVERT_NEWLINES=0
            -DMBED_CONF_NORDIC_NRF_LF_CLOCK_SRC=NRF_LF_SRC_XTAL
            -DMBED_CONF_NORDIC_UART_HWFC=1
    )

    set(MBED_OS
            mbed-os/targets/${PLATFORM}/TARGET_${TARGET}/TARGET_${BOARD}
            mbed-os/targets/${PLATFORM}/TARGET_${TARGET}/device/TOOLCHAIN_GCC_ARM
            mbed-os/targets/${PLATFORM}/TARGET_${TARGET}/sdk/
            mbed-os/targets/${PLATFORM}/TARGET_${TARGET}/sdk/driver_nrf/pwm
            mbed-os/targets/${PLATFORM}/TARGET_${TARGET}/sdk/driver_nrf/saadc
            mbed-os/targets/${PLATFORM}/TARGET_${TARGET}/sdk/softdevice/s132/headers/nrf52
            mbed-os/targets/${PLATFORM}/TARGET_${TARGET}/sdk/softdevice/s132/headers
            mbed-os/targets/${PLATFORM}/TARGET_${TARGET}/device
            mbed-os/targets/${PLATFORM}/TARGET_${TARGET}
            mbed-os/targets/${PLATFORM}/sdk/ble/ble_advertising
            mbed-os/targets/${PLATFORM}/sdk/ble/ble_db_discovery
            mbed-os/targets/${PLATFORM}/sdk/ble/ble_debug_assert_handler
            mbed-os/targets/${PLATFORM}/sdk/ble/ble_dtm
            mbed-os/targets/${PLATFORM}/sdk/ble/ble_error_log
            mbed-os/targets/${PLATFORM}/sdk/ble/ble_racp
            mbed-os/targets/${PLATFORM}/sdk/ble/ble_radio_notification
            mbed-os/targets/${PLATFORM}/sdk/ble/ble_services/ble_dfu
            mbed-os/targets/${PLATFORM}/sdk/ble/common
            mbed-os/targets/${PLATFORM}/sdk/ble/device_manager
            mbed-os/targets/${PLATFORM}/sdk/ble/peer_manager
            mbed-os/targets/${PLATFORM}/sdk/device
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/ble_flash
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/clock
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/common
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/config
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/delay
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/gpiote
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/hal
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/ppi
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/pstorage
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/spi_master
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/spi_slave
            mbed-os/targets/${PLATFORM}/sdk/drivers_nrf/timer
            mbed-os/targets/${PLATFORM}/sdk/libraries/bootloader_dfu
            mbed-os/targets/${PLATFORM}/sdk/libraries/crc16
            mbed-os/targets/${PLATFORM}/sdk/libraries/experimental_section_vars
            mbed-os/targets/${PLATFORM}/sdk/libraries/fds
            mbed-os/targets/${PLATFORM}/sdk/libraries/fstorage
            mbed-os/targets/${PLATFORM}/sdk/libraries/hci
            mbed-os/targets/${PLATFORM}/sdk/libraries/pwm
            mbed-os/targets/${PLATFORM}/sdk/libraries/scheduler
            mbed-os/targets/${PLATFORM}/sdk/libraries/trace
            mbed-os/targets/${PLATFORM}/sdk/libraries/util
            mbed-os/targets/${PLATFORM}/sdk/softdevice/common/softdevice_handler
            # -- special for newer mbed-os
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/ble_advertising
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/ble_db_discovery
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/ble_debug_assert_handler
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/ble_dtm
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/ble_error_log
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/ble_racp
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/ble_radio_notification
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/ble_services/ble_dfu
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/common
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/device_manager
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/ble/peer_manager
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/device
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/ble_flash
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/clock
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/common
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/config
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/delay
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/gpiote
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/hal
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/ppi
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/pstorage
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/spi_master
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/spi_slave
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/drivers_nrf/timer
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/bootloader_dfu
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/crc16
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/experimental_section_vars
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/fds
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/fstorage
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/hci
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/pwm
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/scheduler
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/trace
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/libraries/util
            mbed-os/targets/${PLATFORM}/TARGET_SDK11/softdevice/common/softdevice_handler
            # -- end special
            mbed-os/targets/${PLATFORM}
            mbed-os/rtos/rtx/TARGET_CORTEX_M/TARGET_RTOS_M4_M7
            mbed-os/rtos/rtx/TARGET_CORTEX_M
            mbed-os/rtos
            mbed-os/features/FEATURE_BLE/ble/services
            mbed-os/features/FEATURE_BLE/ble
            mbed-os/features/FEATURE_BLE/source/services
            mbed-os/features/FEATURE_BLE/source
            mbed-os/features/FEATURE_BLE/targets/TARGET_NORDIC/TARGET_NRF5/source/btle/custom
            mbed-os/features/FEATURE_BLE/targets/TARGET_NORDIC/TARGET_NRF5/source/btle
            mbed-os/features/FEATURE_BLE/targets/TARGET_NORDIC/TARGET_NRF5/source
            mbed-os/features/FEATURE_BLE/targets/TARGET_NORDIC/TARGET_NRF5
            mbed-os/features/FEATURE_BLE
            mbed-os/features/frameworks/greentea-client
            mbed-os/features/frameworks/unity
            mbed-os/features/frameworks/utest
            mbed-os/features
            mbed-os/platform
            mbed-os/hal/storage_abstraction
            mbed-os/hal
            mbed-os/events/enqueue
            mbed-os/events
            mbed-os/drivers
            mbed-os/cmsis
            mbed-os
            )

    set(MBED_OS_SRCS "")
    foreach (DIR in ${MBED_OS})
        if (DIR MATCHES "mbed-os/features")
            foreach (FEATURE in ${FEATURES})
                file(GLOB_RECURSE includes
                        ${DIR}/${FEATURE}/*.cpp ${DIR}/${FEATURE}/*.c ${DIR}/${FEATURE}/*.s ${DIR}/${FEATURE}/*.S)
                list(APPEND MBED_OS_SRCS ${includes})
            endforeach ()
        else ()
            file(GLOB includes ${DIR}/*.cpp ${DIR}/*.c ${DIR}/*.s ${DIR}/*.S)
            list(APPEND MBED_OS_SRCS ${includes})
        endif ()
    endforeach ()

    add_library(mbed-os ${MBED_OS_SRCS})
    include_directories(${MBED_OS})
    # == END MBED OS 5 ==

endif()

include(lib.cmake)

add_executable(test-nacl-crypto-hash
        TESTS/nacl/crypto-hash/TestCryptoHash.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-nacl-crypto-hash mbed-os libnacl)

add_executable(test-nacl-crypto-hashblocks
        TESTS/nacl/crypto-hashblocks/TestCryptoHashBlocks.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-nacl-crypto-hashblocks mbed-os libnacl)

add_executable(test-nacl-crypto-sign
        TESTS/nacl/crypto-sign/TestCryptoSign.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-nacl-crypto-sign mbed-os libnacl)

add_executable(test-nacl-crypto-verify
        TESTS/nacl/crypto-verify/TestCryptoVerify.cpp
        source/randombytes/randombytes_nrf52.c
        )
target_link_libraries(test-nacl-crypto-verify mbed-os libnacl)


# NaCl library tests
#add_executable(stack_crypto_hash source/nacl/test/stack_crypto_hash.cpp)
#target_link_libraries(stack_crypto_hash mbed-os libnacl)
#add_executable(stack_crypto_hashblocks source/nacl/test/stack_crypto_hashblocks.cpp)
#target_link_libraries(stack_crypto_hashblocks mbed-os libnacl)
#add_executable(stack_crypto_sign source/nacl/test/stack_crypto_sign.cpp)
#target_link_libraries(stack_crypto_sign mbed-os libnacl)
#add_executable(stack_crypto_verify source/nacl/test/stack_crypto_verify.cpp)
#target_link_libraries(stack_crypto_verify mbed-os libnacl)
#add_executable(test_crypto_hash source/nacl/test/test_crypto_hash.cpp)
#target_link_libraries(test_crypto_hash mbed-os libnacl)
#add_executable(test_crypto_hashblocks source/nacl/test/test_crypto_hashblocks.cpp)
#target_link_libraries(test_crypto_hashblocks mbed-os libnacl)
#add_executable(test_crypto_sign source/nacl/test/test_crypto_sign.cpp)
#target_link_libraries(test_crypto_sign mbed-os libnacl)
#add_executable(test_crypto_verify source/nacl/test/test_crypto_verify.cpp)
#target_link_libraries(test_crypto_verify mbed-os libnacl)

add_custom_target(run-test-crypto-hash
        COMMAND mbed test -n tests-nacl-crypto-hash -vv
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(run-test-crypto-hashblocks
        COMMAND mbed test -n tests-nacl-crypto-hashblocks -vv
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(run-test-crypto-sign
        COMMAND mbed test -n tests-nacl-crypto-sign -vv
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(run-test-crypto-verify
        COMMAND mbed test -n tests-nacl-crypto-verify -vv
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(run-tests ALL
        COMMAND mbed test -n tests-nacl*
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(debug-tests ALL
        COMMAND mbed test -n tests-nacl-crypto-sign* -vv --profile mbed-os/tools/profiles/debug.json
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(compile-debug-tests ALL
        COMMAND mbed test -n tests-nacl* -c --compile --profile mbed-os/tools/profiles/debug.json
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
