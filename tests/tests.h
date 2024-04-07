#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../include/token_parser/token_parser.h"

class TestTokenParser : public testing::TestWithParam<int> {
 public:
  static void SetUpTestSuite();

  static std::vector<TokenParser::Parser> parsers_;
  static std::vector<std::string> strs_;
};
