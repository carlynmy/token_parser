#include <gtest/gtest.h>

#include <string>

#include "../include/token_parser/string_parser.h"

TEST(NextTokenNoStr, NextWord) {
  TokenParser::StringParser parser(nullptr);
  std::string str = parser.NextWord();
  ASSERT_EQ("", str);
}

TEST(NextTokenNoStr, NextInt) {
  TokenParser::StringParser parser(nullptr);
  TokenParser::Token tok = parser.NextInt();
  ASSERT_TRUE(tok.IsNull());
}
TEST(NextTokenNoStr, NextUint) {
  TokenParser::StringParser parser(nullptr);
  TokenParser::Token tok = parser.NextUint();
  ASSERT_TRUE(tok.IsNull());
}
TEST(NextTokenNoStr, NextFloat) {
  TokenParser::StringParser parser(nullptr);
  TokenParser::Token tok = parser.NextFloat();
  ASSERT_TRUE(tok.IsNull());
}

TEST(NextTokenNoStr, NextToken) {
  TokenParser::Settings::TokenIds ids = {{0, "ada"}, {0, "bobbb"}};
  TokenParser::Settings settings;
  settings.SetTokenIds(ids);
  TokenParser::StringParser parser(settings, nullptr);
  TokenParser::Token tok = parser.NextId();
  ASSERT_TRUE(tok.IsNull());
}

TEST(NextTokenEndLen, NextWord) {
  std::string parsing_str = "it is string";
  TokenParser::StringParser parser(&parsing_str);
  parser.SetI(13);
  std::string str = parser.NextWord();
  ASSERT_TRUE(str.empty());
  parser.SetI(550);
  str = parser.NextWord();
  ASSERT_TRUE(str.empty());
}

TEST(NextTokenEndLen, NextInt) {
  std::string parsing_str = "it is string";
  TokenParser::StringParser parser(&parsing_str);
  parser.SetI(13);
  TokenParser::Token tok = parser.NextInt();
  ASSERT_TRUE(tok.IsNull());
  parser.SetI(550);
  tok = parser.NextInt();
  ASSERT_TRUE(tok.IsNull());
}

TEST(NextTokenEndLen, NextUint) {
  std::string parsing_str = "it is string";
  TokenParser::StringParser parser(&parsing_str);
  parser.SetI(13);
  TokenParser::Token tok = parser.NextUint();
  ASSERT_TRUE(tok.IsNull());
  parser.SetI(550);
  tok = parser.NextUint();
  ASSERT_TRUE(tok.IsNull());
}

TEST(NextTokenEndLen, NextFloat) {
  std::string parsing_str = "it is string";
  TokenParser::StringParser parser(&parsing_str);
  parser.SetI(13);
  TokenParser::Token tok = parser.NextFloat();
  ASSERT_TRUE(tok.IsNull());
  parser.SetI(550);
  tok = parser.NextFloat();
  ASSERT_TRUE(tok.IsNull());
}

TEST(NextTokenEndLen, NextId) {
  std::string parsing_str = "it is string";
  TokenParser::Settings::TokenIds ids = {{0, "ada"}, {0, "bobbb"}};
  TokenParser::Settings settings;
  settings.SetTokenIds(ids);
  TokenParser::StringParser parser(settings, &parsing_str);

  parser.SetI(13);
  TokenParser::Token tok = parser.NextId();
  ASSERT_TRUE(tok.IsNull());
  parser.SetI(550);
  tok = parser.NextId();
  ASSERT_TRUE(tok.IsNull());
}
TEST(NextTokenEndSpaces, NextInt) {
  std::string parsing_str = "it is string\t\t   \t  \n  ";
  TokenParser::StringParser parser(&parsing_str);
  parser.SetI(13);
  TokenParser::Token tok = parser.NextInt();
  ASSERT_TRUE(tok.IsNull());
}

TEST(NextTokenEndSpaces, NextUint) {
  std::string parsing_str = "it is string\t\t   \t  \n  ";
  TokenParser::StringParser parser(&parsing_str);
  parser.SetI(13);
  TokenParser::Token tok = parser.NextUint();
  ASSERT_TRUE(tok.IsNull());
}

TEST(NextTokenEndSpaces, NextFloat) {
  std::string parsing_str = "it is string\t\t   \t  \n  ";
  TokenParser::StringParser parser(&parsing_str);
  parser.SetI(13);
  TokenParser::Token tok = parser.NextFloat();
  ASSERT_TRUE(tok.IsNull());
}

TEST(NextTokenEndSpaces, NextId) {
  std::string parsing_str = "it is string\t\t   \t  \n  ";
  TokenParser::Settings::TokenIds ids = {{0, "ada"}, {0, "bobbb"}};
  TokenParser::Settings settings;
  settings.SetTokenIds(ids);
  TokenParser::StringParser parser(settings, &parsing_str);

  parser.SetI(13);
  TokenParser::Token tok = parser.NextId();
  ASSERT_TRUE(tok.IsNull());
}

TEST(IsEnd, Common) {
  std::string parsing_str = "is is striiiii   \t\t\n\n\n";

  TokenParser::StringParser parser(nullptr);
  ASSERT_TRUE(parser.IsEnd());
  parser.SetStr(&parsing_str);

  ASSERT_TRUE(!parser.IsEnd());
  parser.SetI(5);
  ASSERT_TRUE(!parser.IsEnd());
  parser.SetI(14);
  ASSERT_TRUE(parser.IsEnd());
  parser.SetI(41421);
  ASSERT_TRUE(parser.IsEnd());
  parser.SetI(12);
  parser.GetSettings().SetSpaceChars(" \t\ni");
  ASSERT_TRUE(parser.IsEnd());
}

TEST(NextWord, WordIsWordDelim) {
  std::string parsing_str = "word==word == word = = word= =word";
  TokenParser::Settings settings;
  settings.SetWordDelim(settings.GetWordDelimChars() + "=");
  TokenParser::StringParser parser(settings, &parsing_str);

  std::string word = "word", eq = "=";
  ASSERT_EQ(parser.NextWord(), word);
  ASSERT_EQ(parser.NextWord(), eq);
  ASSERT_EQ(parser.NextWord(), eq);
  ASSERT_EQ(parser.NextWord(), word);
  ASSERT_EQ(parser.NextWord(), eq);
  ASSERT_EQ(parser.NextWord(), eq);
  ASSERT_EQ(parser.NextWord(), word);
  ASSERT_EQ(parser.NextWord(), eq);
  ASSERT_EQ(parser.NextWord(), eq);
  ASSERT_EQ(parser.NextWord(), word);
  ASSERT_EQ(parser.NextWord(), eq);
  ASSERT_EQ(parser.NextWord(), eq);
  ASSERT_EQ(parser.NextWord(), word);
}

TEST(Delims, NoWordDelimNoSpace) {
  TokenParser::Settings settings;
  settings.SetWordDelim("");
  settings.SetSpaceChars("");

  std::string parsing_str = "342 322";
  TokenParser::StringParser parser(settings, &parsing_str);

  std::string space = " 322";
  ASSERT_EQ(parser.NextInt().GetInt(), 342);
  ASSERT_EQ(parser.NextWord(), space);
}

TEST(Delims, NoSpace) {
  TokenParser::Settings settings;
  settings.SetWordDelim(" ");
  settings.SetSpaceChars("");

  std::string parsing_str = "342 322";
  TokenParser::StringParser parser(settings, &parsing_str);

  std::string space = " ";
  ASSERT_EQ(parser.NextInt().GetInt(), 342);
  ASSERT_EQ(parser.NextWord(), space);
  ASSERT_EQ(parser.NextInt().GetInt(), 322);
}

TEST(Delims, SpaceNotWordDelim) {
  TokenParser::Settings settings;
  settings.SetWordDelim("");
  settings.SetSpaceChars(" ");

  std::string parsing_str = "342 322";
  TokenParser::StringParser parser(settings, &parsing_str);

  ASSERT_EQ(parser.NextInt().GetInt(), 342);
  ASSERT_EQ(parser.NextInt().GetInt(), 322);
}

TEST(NextThisId, Common) {
  TokenParser::Settings::TokenIds tokens = {{0, "int"}, {1, "int32_t"}};
  TokenParser::Settings settings;
  settings.SetTokenIds(tokens);

  std::string parsing_str = "int32_t bro";
  TokenParser::StringParser parser(settings, nullptr);

  ASSERT_TRUE(parser.NextThisId(TokenParser::Token::id_type(1)).IsNull());
  parser.SetStr(&parsing_str);
  parser.SetI(1515);
  ASSERT_TRUE(parser.NextThisId(TokenParser::Token::id_type(1)).IsNull());

  parser.SetI(0);
  ASSERT_TRUE(parser.NextThisId(TokenParser::Token::id_type(3)).IsNull());
  ASSERT_EQ(parser.NextThisId(TokenParser::Token::id_type(1)).GetId(),
            TokenParser::Token::id_type(1));
  parser.SetI(0);
  ASSERT_EQ(parser.NextThisId(TokenParser::Token::id_type(0)).GetId(),
            TokenParser::Token::id_type(0));
  parser.GetSettings().SetTokenIdIsFullWord(false);
  parser.SetI(0);
  ASSERT_EQ(parser.NextThisId(TokenParser::Token::id_type(1)).GetId(),
            TokenParser::Token::id_type(1));
  parser.SetI(0);
  ASSERT_EQ(parser.NextThisId(TokenParser::Token::id_type(0)).GetId(),
            TokenParser::Token::id_type(0));
}
