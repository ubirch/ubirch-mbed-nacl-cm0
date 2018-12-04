# ESP-32 IDF CMakeLists.txt
file(GLOB_RECURSE COMPONENT_SRCS "${CMAKE_CURRENT_LIST_DIR}/source/nacl/*.c")
list(APPEND COMPONENT_SRCS ${CMAKE_CURRENT_LIST_DIR}/source/randombytes/randombytes_esp32.c)
set(COMPONENT_ADD_INCLUDEDIRS
        source/nacl
        source/nacl/crypto_sign
        source/nacl/crypto_hash
        source/nacl/crypto_hashblocks
        source/nacl/include
        source/nacl/crypto_verify
        source/nacl/shared
        source/randombytes
        )
register_component()
