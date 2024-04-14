cmake_minimum_required(VERSION 3.5)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/token_parser
)

set(TOKEN_PARSER_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/include/token_parser/string_parser.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/token_parser/token.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/token_parser/settings.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/string_parser.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/token.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/settings.cc
)

set(TOKEN_PARSER_SOURCE_TESTS
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.h
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/token_seq_test.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/next_token_test.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/token_test.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/settings_test.cc
)

SET(TOKEN_PARSER_COVERAGE_LIBS "" CACHE STRING "")
SET(TOKEN_PARSER_COVERAGE_FLAGS "" CACHE STRING "")
SET(TOKEN_PARSER_WARNING_FLAGS "-Wall -Werror -Wextra" CACHE STRING "")
SET(TOKEN_PARSER_STANDART_FLAGS "-std=c++17" CACHE STRING "")
SET(TOKEN_PARSER_FLAGS "${TOKEN_PARSER_COVERAGE_FLAGS} ${TOKEN_PARSER_WARNING_FLAGS} ${TOKEN_PARSER_STANDART_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TOKEN_PARSER_FLAGS}")

add_library(token_parser STATIC ${TOKEN_PARSER_SOURCE})

add_executable(token_parser_tests ${TOKEN_PARSER_SOURCE_TESTS})

target_link_libraries(
  token_parser_tests
  token_parser
  gtest
  ${TOKEN_PARSER_COVERAGE_LIBS}
)
