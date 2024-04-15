#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../include/token_parser/file_parser.h"
#include "../include/token_parser/stream_parser.h"
#include "../include/token_parser/string_parser.h"

class TestTokenParser : public testing::TestWithParam<int> {
 public:
  static void SetUpTestSuite();

  static std::vector<TokenParser::StringParser> parsers_;
  static std::vector<std::string> strs_;
};

bool SettingsTokenIdsEq(const TokenParser::Settings::TokenIds& a,
                        const TokenParser::Settings::TokenIds& b);
bool SettingsAppropriateQoutesEq(
    const TokenParser::Settings::AppropriateQuotes& a,
    const TokenParser::Settings::AppropriateQuotes& b);
bool SettingsEq(const TokenParser::Settings& a, const TokenParser::Settings& b);
