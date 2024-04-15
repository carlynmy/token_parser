#include <gtest/gtest.h>

#include "../include/token_parser/string_parser.h"
#include "tests.h"

using TokenParser::Settings;

TEST(Settings, Common) {
  Settings::TokenIds token_ids = {{0, "aad"}};
  Settings::TokenIds token_ids2 = {{0, "aad"}};
  std::string space_chars = "asdas";
  std::string space_chars2 = "asdas";
  std::string word_delim_chars = "asdasbbb";
  std::string word_delim_chars2 = "asdasbbb";
  bool token_id_is_full_word = false;
  bool word_may_surrounded_by_qoutes = true;
  Settings::AppropriateQuotes appropriate_quotes = {{'a', 'b'}};
  Settings::AppropriateQuotes appropriate_quotes2 = {{'a', 'b'}};

  Settings a, b, c;
  a.SetTokenIds(token_ids);
  a.SetSpaceChars(space_chars);
  a.SetWordDelim(word_delim_chars);
  a.SetTokenIdIsFullWord(token_id_is_full_word);
  a.SetWordMaySurrondedByQoutes(word_may_surrounded_by_qoutes);
  a.SetAppropriateQuotes(appropriate_quotes);
  b.SetTokenIds(std::move(token_ids2));
  b.SetSpaceChars(std::move(space_chars2));
  b.SetWordDelim(std::move(word_delim_chars2));
  b.SetTokenIdIsFullWord(token_id_is_full_word);
  b.SetWordMaySurrondedByQoutes(word_may_surrounded_by_qoutes);
  b.SetAppropriateQuotes(std::move(appropriate_quotes2));
  c.GetTokenIds() = token_ids;
  c.GetSpaceChars() = space_chars;
  c.GetWordDelimChars() = word_delim_chars;
  c.SetTokenIdIsFullWord(token_id_is_full_word);
  c.SetWordMaySurrondedByQoutes(word_may_surrounded_by_qoutes);
  c.GetAppropriateQuotes() = appropriate_quotes;

  ASSERT_TRUE(SettingsEq(a, b));
  ASSERT_TRUE(SettingsEq(a, c));

  Settings scopy(a);
  Settings smove(std::move(b));
  Settings ocopy, omove;
  ocopy = a;
  omove = std::move(c);

  ASSERT_TRUE(SettingsEq(a, scopy));
  ASSERT_TRUE(SettingsEq(a, ocopy));
  ASSERT_TRUE(SettingsEq(a, smove));
  ASSERT_TRUE(SettingsEq(a, omove));
}
