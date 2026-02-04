cmake_minimum_required(VERSION 3.10)

project(Serial
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)

set(TEST_DATADIR "${CMAKE_SOURCE_DIR}/data" CACHE STRING "Path to test data")
configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config.h @ONLY)

# Auto download googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        52eb8108c5bdec04579160ae17225d66034bd723 # v1.17.0
)
FetchContent_MakeAvailable(googletest)

add_executable(testSerial
  Serial.cc
  testSerial.cc
)

target_include_directories(testSerial
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
)

target_compile_options(testSerial
  PRIVATE
  "-Wall" "-Wextra" "-g" "-O0" "-fsanitize=address,undefined"
)

target_compile_features(testSerial
  PUBLIC
    cxx_std_17
)

set_target_properties(testSerial
  PROPERTIES
    CXX_EXTENSIONS OFF
    LINK_FLAGS "-fsanitize=address,undefined"
)

target_include_directories(testSerial
  PRIVATE
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(testSerial
  PRIVATE
    GTest::gtest_main
    Threads::Threads
)

include(GoogleTest)
gtest_discover_tests(testSerial)
