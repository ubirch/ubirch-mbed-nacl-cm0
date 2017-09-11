add_library(libnacl
        ${CMAKE_CURRENT_LIST_DIR}/source/nacl/shared/bigint.c
        ${CMAKE_CURRENT_LIST_DIR}/source/nacl/shared/consts.c
        ${CMAKE_CURRENT_LIST_DIR}/source/nacl/shared/fe25519.c
        ${CMAKE_CURRENT_LIST_DIR}/source/nacl/crypto_hash/sha512.c
        ${CMAKE_CURRENT_LIST_DIR}/source/nacl/crypto_hashblocks/sha512.c
        ${CMAKE_CURRENT_LIST_DIR}/source/nacl/crypto_sign/ed25519.c
        ${CMAKE_CURRENT_LIST_DIR}/source/nacl/crypto_sign/ge25519.c
        ${CMAKE_CURRENT_LIST_DIR}/source/nacl/crypto_sign/sc25519.c
        ${CMAKE_CURRENT_LIST_DIR}/source/nacl/crypto_verify/verify.c
        # add more source files here, if needed
        # ...
        # do write your own randombytes function
        #${CMAKE_CURRENT_LIST_DIR}/source/randombytes/randombytes.c
        )
target_include_directories(libnacl PUBLIC ${CMAKE_CURRENT_LIST_DIR}/source)
