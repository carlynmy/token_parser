#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../include/token_parser/string_parser.h"

class TestTokenParser : public testing::TestWithParam<int> {
 public:
  static void SetUpTestSuite();

  static std::vector<TokenParser::StringParser> parsers_;
  static std::vector<std::string> strs_;
};
