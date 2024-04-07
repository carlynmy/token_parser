#include <gtest/gtest.h>

#include "../include/token_parser/token_parser.h"

using TokenParser::Settings;

bool TokenIdsEq(const Settings::TokenIds& a, const Settings::TokenIds& b) {
  if (a.size() != b.size()) return false;

  auto ia = a.begin(), ib = b.begin();
  while (ia != a.end()) {
    if (ia->first != ib->first || ia->second != ib->second) return false;

    ++ia;
    ++ib;
  }

  return true;
}

TEST(Settings, Common) {
  Settings settings;
  Settings::TokenIds tokens = {{0, "a"}};
  Settings::TokenIds tokens2 = tokens;
  settings.SetTokenIds(tokens);
  settings.SetTokenIds(std::move(tokens2));

  std::string w = "aaa", b = "bbb";
  std::string cw = w, cb = b;
  settings.SetSpaceChars(w);
  settings.SetWordDelim(b);
  settings.SetSpaceChars(std::move(cw));
  settings.SetWordDelim(std::move(cb));
  settings.SetTokenIdIsFullWord(false);

  ASSERT_EQ(settings.GetSpaceChars(), w);
  ASSERT_EQ(settings.GetWordDelimChars(), b);
  ASSERT_TRUE(!settings.GetTokenIdIsFullWord());
  ASSERT_TRUE(TokenIdsEq(settings.GetTokenIds(), tokens));
  const Settings& setr = settings;
  ASSERT_TRUE(TokenIdsEq(setr.GetTokenIds(), tokens));

  Settings s2(settings);
  ASSERT_EQ(s2.GetSpaceChars(), w);
  ASSERT_EQ(s2.GetWordDelimChars(), b);
  ASSERT_TRUE(!s2.GetTokenIdIsFullWord());
  ASSERT_TRUE(TokenIdsEq(s2.GetTokenIds(), tokens));

  Settings s3;
  s3 = s2;
  ASSERT_EQ(s3.GetSpaceChars(), w);
  ASSERT_EQ(s3.GetWordDelimChars(), b);
  ASSERT_TRUE(!s3.GetTokenIdIsFullWord());
  ASSERT_TRUE(TokenIdsEq(s3.GetTokenIds(), tokens));

  Settings s4(std::move(s3));
  ASSERT_EQ(s4.GetSpaceChars(), w);
  ASSERT_EQ(s4.GetWordDelimChars(), b);
  ASSERT_TRUE(!s4.GetTokenIdIsFullWord());
  ASSERT_TRUE(TokenIdsEq(s4.GetTokenIds(), tokens));

  Settings s5;
  s5 = std::move(s4);
  ASSERT_EQ(s5.GetSpaceChars(), w);
  ASSERT_EQ(s5.GetWordDelimChars(), b);
  ASSERT_TRUE(!s5.GetTokenIdIsFullWord());
  ASSERT_TRUE(TokenIdsEq(s5.GetTokenIds(), tokens));
}
