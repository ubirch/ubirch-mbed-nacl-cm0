if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/yotta_targets/calliope-mini-classic-gcc/CMake/toolchain.cmake)
    message(FATAL_ERROR "Attention: mbed-os 2: run 'yotta update'!")
endif()

set(CMAKE_TOOLCHAIN_FILE yotta_targets/mbed-gcc/CMake/toolchain.cmake)
set(CMAKE_BUILD_TYPE Debug)

project(ubirch-mbed-nacl-cm0 C CXX)
set(CMAKE_CXX_STANDARD 98)

include(yotta_targets/calliope-mini-classic-gcc/CMake/toolchain.cmake)

add_definitions(-DNRF51 -DTARGET_NRF51 -DTARGET_NRF51_CALLIOPE)

file(GLOB MBED_INC
        yotta_modules/mbed-classic/api
        yotta_modules/mbed-classic/hal
        yotta_modules/mbed-classic/targets/cmsis
        yotta_modules/mbed-classic/targets/cmsis/TARGET_NORDIC
        yotta_modules/mbed-classic/targets/cmsis/TARGET_NORDIC/TARGET_MCU_NRF51822
        yotta_modules/mbed-classic/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822
        yotta_modules/mbed-classic/targets/hal/TARGET_NORDIC/TARGET_MCU_NRF51822/TARGET_NRF51_CALLIOPE
        yotta_modules/nrf51-sdk/source/nordic_sdk/components/ble
        yotta_modules/nrf51-sdk/source/nordic_sdk/components/device
        yotta_modules/nrf51-sdk/source/nordic_sdk/components/drivers_nrf
        yotta_modules/nrf51-sdk/source/nordic_sdk/components/libraries
        yotta_modules/nrf51-sdk/source/nordic_sdk/components/softdevice/common/softdevice_handler
        yotta_modules/nrf51-sdk/source/nordic_sdk/components/softdevice/s130/headers
        )
file(GLOB_RECURSE MBED_SRC
        yotta_modules/mbed-classic/common/*.c
        yotta_modules/mbed-classic/common/*.cpp
        yotta_modules/mbed-classic/targets/TARGET_NORDIC/*.c
        yotta_modules/nrf51-sdk/source/nordic_sdk/components/*.c*
        )

add_library(mbed-os ${MBED_SRC})
include_directories(${MBED_INC})

add_library(greentea-client yotta_modules/greentea-client/source/test_env.cpp)
target_include_directories(greentea-client PUBLIC yotta_modules/greentea-client)

add_custom_target(compile
        COMMAND yt build
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
