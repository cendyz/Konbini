cmake_minimum_required(VERSION 3.16)

project(konbini)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.17.0
)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_library(CoreLogic
        src/main.cpp
        src/Accounts.cpp
        src/Cart.cpp
        src/Konbini.cpp
        src/KonbiniUI.cpp
        src/LanguageManager.cpp
        src/Products.cpp
        src/Cart.cpp
)

target_include_directories(CoreLogic PUBLIC include)

add_executable(konbini src/main.cpp)
target_link_libraries(konbini PRIVATE CoreLogic)

target_compile_definitions(CoreLogic PUBLIC
        DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/"
)

enable_testing()
include(GoogleTest)

add_executable(tests
        tests/utilsTests.cpp
        tests/LngManagerTests.cpp
)

target_link_libraries(tests PRIVATE GTest::gtest_main CoreLogic)
target_link_libraries(CoreLogic PRIVATE GTest::gtest)
gtest_discover_tests(tests)