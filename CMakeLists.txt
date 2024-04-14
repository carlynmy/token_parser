cmake_minimum_required(VERSION 3.5)

project(libtoken_parser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TOKEN_PARSER_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(TOKEN_PARSER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TOKEN_PARSER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(
  ${TOKEN_PARSER_INCLUDE_DIR}
)

set(TOKEN_PARSER_SOURCE
  ${TOKEN_PARSER_INCLUDE_DIR}/token_parser/string_parser.h
  ${TOKEN_PARSER_INCLUDE_DIR}/token_parser/stream_parser.h
  ${TOKEN_PARSER_INCLUDE_DIR}/token_parser/file_parser.h
  ${TOKEN_PARSER_INCLUDE_DIR}/token_parser/token.h
  ${TOKEN_PARSER_INCLUDE_DIR}/token_parser/settings.h
  ${TOKEN_PARSER_SRC_DIR}/string_parser.cc
  ${TOKEN_PARSER_SRC_DIR}/stream_parser.inc
  ${TOKEN_PARSER_SRC_DIR}/file_parser.cc
  ${TOKEN_PARSER_SRC_DIR}/token.cc
  ${TOKEN_PARSER_SRC_DIR}/settings.cc
)

set(TOKEN_PARSER_SOURCE_TESTS
  ${TOKEN_PARSER_TESTS_DIR}/tests.h
  ${TOKEN_PARSER_TESTS_DIR}/tests.cc
  ${TOKEN_PARSER_TESTS_DIR}/token_seq_test.cc
  ${TOKEN_PARSER_TESTS_DIR}/next_token_test.cc
  ${TOKEN_PARSER_TESTS_DIR}/token_test.cc
  ${TOKEN_PARSER_TESTS_DIR}/settings_test.cc
)

set(TOKEN_PARSER_COVERAGE_LIBS "" CACHE STRING "")
set(TOKEN_PARSER_COVERAGE_FLAGS "" CACHE STRING "")
set(TOKEN_PARSER_WARNING_FLAGS "-Wall -Werror -Wextra" CACHE STRING "")
set(TOKEN_PARSER_STANDART_FLAGS "-std=c++17" CACHE STRING "")
set(TOKEN_PARSER_FLAGS "${TOKEN_PARSER_COVERAGE_FLAGS} ${TOKEN_PARSER_WARNING_FLAGS} ${TOKEN_PARSER_STANDART_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TOKEN_PARSER_FLAGS}")

add_library(token_parser STATIC ${TOKEN_PARSER_SOURCE})

add_executable(token_parser_tests ${TOKEN_PARSER_SOURCE_TESTS})

target_link_libraries(token_parser_tests
  token_parser
  gtest
  ${TOKEN_PARSER_COVERAGE_LIBS}
)
