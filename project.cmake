add_library(tests
        TESTS/crypto/hash/TestCryptoHash.cpp
        TESTS/crypto/hashblocks/TestCryptoHashBlocks.cpp
        TESTS/crypto/sign/TestCryptoSign.cpp
        TESTS/crypto/verify/TestCryptoVerify.cpp
        TESTS/stack/hash/TestStackCryptoHash.cpp
        TESTS/stack/hashblocks/TestStackCryptoHashBlocks.cpp
        TESTS/stack/sign/TestStackCryptoSign.cpp
        TESTS/stack/verify/TestStackCryptoVerify.cpp
        )
target_link_libraries(tests mbed-ubirch-protocol)

add_custom_target(run-tests
        COMMAND mbed test -n tests-stack*,tests-crypto* --profile ${MBED_BUILD_PROFILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
