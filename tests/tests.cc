#include "tests.h"

#include <gtest/gtest.h>

#include "../include/token_parser/file_parser.h"
#include "../include/token_parser/stream_parser.h"
#include "../include/token_parser/string_parser.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

bool SettingsTokenIdsEq(const TokenParser::Settings::TokenIds& a,
                        const TokenParser::Settings::TokenIds& b) {
  if (a.size() != b.size()) return false;

  auto ia = a.begin(), ib = b.begin();
  while (ia != a.end()) {
    if (ia->first != ib->first || ia->second != ib->second) return false;

    ++ia;
    ++ib;
  }

  return true;
}

bool SettingsAppropriateQoutesEq(
    const TokenParser::Settings::AppropriateQuotes& a,
    const TokenParser::Settings::AppropriateQuotes& b) {
  if (a.size() != b.size()) return false;

  auto ia = a.begin(), ib = b.begin();
  while (ia != a.end()) {
    if (ia->first != ib->first || ia->second != ib->second) return false;

    ++ia;
    ++ib;
  }

  return true;
}

bool SettingsEq(const TokenParser::Settings& a,
                const TokenParser::Settings& b) {
  if (!SettingsTokenIdsEq(a.GetTokenIds(), b.GetTokenIds())) return false;
  if (!SettingsAppropriateQoutesEq(a.GetAppropriateQuotes(),
                                   b.GetAppropriateQuotes()))
    return false;
  if (a.GetSpaceChars() != b.GetSpaceChars()) return false;
  if (a.GetWordDelimChars() != b.GetWordDelimChars()) return false;
  if (a.GetTokenIdIsFullWord() != b.GetTokenIdIsFullWord()) return false;
  if (a.GetWordMaySurrondedByQoutes() != b.GetWordMaySurrondedByQoutes())
    return false;
  return true;
}

void TestTokenParser::SetUpTestSuite() {
  TokenParser::Settings::TokenIds token_ids;
  TokenParser::Settings settings;
  TokenParser::StringParser parser;

  token_ids.clear();
  token_ids.insert({0, ";"});
  token_ids.insert({1, "("});
  token_ids.insert({2, ")"});
  token_ids.insert({3, "{"});
  token_ids.insert({4, "}"});
  token_ids.insert({5, "int"});
  token_ids.insert({6, "int32_t"});
  token_ids.insert({7, "="});
  settings.SetTokenIds(token_ids);
  settings.SetWordDelim(settings.GetWordDelimChars() + ";(){}=");
  settings.SetTokenIdIsFullWord(true);
  parser.SetSettings(settings);
  parsers_.push_back(parser);

  token_ids.clear();
  token_ids.insert({0, "sin"});
  token_ids.insert({1, "cos"});
  settings.SetTokenIds(token_ids);
  settings.SetTokenIdIsFullWord(false);
  parser.SetSettings(settings);
  parsers_.push_back(parser);

  token_ids.clear();
  token_ids.insert({0, ";"});
  token_ids.insert({1, "("});
  token_ids.insert({2, ")"});
  token_ids.insert({3, "{"});
  token_ids.insert({4, "}"});
  token_ids.insert({5, "c"});
  token_ids.insert({6, "int32_t"});
  token_ids.insert({7, "="});
  settings.SetTokenIds(token_ids);
  settings.SetWordDelim(settings.GetWordDelimChars() + ";(){}=");
  settings.SetTokenIdIsFullWord(true);
  parser.SetSettings(settings);
  parsers_.push_back(parser);

  token_ids.clear();
  token_ids.insert({0, ";"});
  token_ids.insert({1, "("});
  token_ids.insert({2, ")"});
  token_ids.insert({3, "{"});
  token_ids.insert({4, "}"});
  token_ids.insert({5, "c"});
  token_ids.insert({6, "int32_t"});
  token_ids.insert({7, "="});
  settings.SetTokenIds(token_ids);
  settings.SetWordDelim(settings.GetWordDelimChars() + ";(){}=");
  settings.SetTokenIdIsFullWord(false);
  parser.SetSettings(settings);
  parsers_.push_back(parser);

  token_ids.clear();
  token_ids.insert({0, ";"});
  token_ids.insert({1, "("});
  token_ids.insert({2, ")"});
  token_ids.insert({3, "{"});
  token_ids.insert({4, "}"});
  token_ids.insert({5, "c"});
  token_ids.insert({6, "int32_t"});
  token_ids.insert({7, "="});
  token_ids.insert({8, "'token with space'"});
  token_ids.insert({9, "\"token with space\""});
  token_ids.insert({10, "<token with space>"});
  token_ids.insert({11, "include"});
  token_ids.insert({12, "#"});
  settings.SetTokenIds(token_ids);
  settings.SetWordDelim(settings.GetWordDelimChars() + "#;(){}='\"<>");
  settings.SetTokenIdIsFullWord(true);
  settings.SetWordMaySurrondedByQoutes(true);
  settings.SetAppropriateQuotes({{'"', '"'}, {'\'', '\''}, {'<', '>'}});
  parser.SetSettings(settings);
  parsers_.push_back(parser);
}

std::vector<TokenParser::StringParser> TestTokenParser::parsers_{};

std::vector<std::string> TestTokenParser::strs_ = {
    "int32_t main() { int a=3.3; }",
    "sincos",

    "-4",
    "4",
    "4.4e+3",
    "int32_t",
    "c",
    "=",
    "main",
    "\t  -4 \n \n",
    "\t  4 \n \n",
    "\t  4.4e+3 \n \n",
    "\t  int32_t \n \n",
    "\t  c \n \n",
    "\t  = \n \n",
    "\t  main \n \n",

    "-4 4",
    "-134 0.1",
    "-4 int32_t",
    "-4 c",
    "-4   =",
    "-4 main",
    "  \t-4\t4",  // 22
    "-134.1  ",
    "-4int32_t",
    " -4c",
    " -4=",
    " -4main",

    "4 -4",
    "134 0.1",
    "4 int32_t",
    "4 c",
    "4   =",
    "4 main",
    "  \t4\t-4",
    "134.1  ",
    "4int32_t",
    " 4c",
    " 4=",
    " 4main",

    "-1.1 -2",
    "-1.1 2",
    "-1.1 -2.1",
    "-1.1 int32_t",
    "-1.1 c",
    "-1.1 =",
    "-1.1 main",
    "  -1.1\t-2",
    "  -1.1\t2",
    "  -1.1\t-2.1",
    "  -1.1int32_t",
    "  -1.1c",
    "  -1.1=",
    "  -1.1main",

    "int32_t -2",
    "int32_t 2",
    "int32_t -2.2",
    "int32_t int32_t",
    "int32_t c",
    "int32_t =",
    "int32_t main",
    "int32_t-2",
    "int32_t2",
    "int32_t-2.2",
    "int32_tint32_t",
    "int32_tc",
    "int32_t=",
    "int32_tmain",

    "c -2",
    "c 2",
    "c -2.2",
    "c int32_t",
    "c c",
    "c =",
    "c main",
    "c-2",
    "c2",
    "c-2.2",
    "cint32_t",
    "cc",
    "c=",
    "cmain",

    "= -2",
    "= 2",
    "= -2.2",
    "= int32_t",
    "= c",
    "= =",
    "= main",
    "=-2",
    "=2",
    "=-2.2",
    "=int32_t",
    "=c",
    "==",
    "=main",

    "main -2",
    "main 2",
    "main -2.2",
    "main int32_t",
    "main c",
    "main =",
    "main main",
    "main-2",
    "main2",
    "main-2.2",
    "mainint32_t",
    "mainc",
    "main=",
    "mainmain",

    "# include <main> 345\n\"token with space\" \'word with 123 space\'",
    "   ' word with \" qoutes \" <> <> qoitiis '  ",

};
