#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <string>

#include "../include/token_parser/file_parser.h"
#include "../include/token_parser/stream_parser.h"
#include "../include/token_parser/string_parser.h"

template <typename T>
class TokenParserTestTyped : public testing::Test {
 public:
  static void* SetupParser(T& parser, const std::string& str);
  static void EndupParser(T& parser, void* mem);

  static const std::string kTmpFilename_;
};

template <typename T>
const std::string TokenParserTestTyped<T>::kTmpFilename_ =
    ".tmp_token_parser_test_token_parser_test_typed.txtx";

template <typename T>
void* TokenParserTestTyped<T>::SetupParser(T& parser, const std::string& str) {
  (void)parser;
  (void)str;
  return nullptr;
}

template <typename T>
void TokenParserTestTyped<T>::EndupParser(T& parser, void* mem) {
  (void)parser;
  (void)mem;
}

template <>
void* TokenParserTestTyped<TokenParser::StringParser>::SetupParser(
    TokenParser::StringParser& parser, const std::string& str) {
  parser.SetStr(&str);
  return nullptr;
}

template <>
void TokenParserTestTyped<TokenParser::StringParser>::EndupParser(
    TokenParser::StringParser& parser, void* mem) {
  (void)parser;
  (void)mem;
}

template <>
void* TokenParserTestTyped<TokenParser::StreamParser<char>>::SetupParser(
    TokenParser::StreamParser<char>& parser, const std::string& str) {
  const std::string& filename = TokenParserTestTyped::kTmpFilename_;
  std::ofstream file(filename);
  file << str;
  file.close();

  std::ifstream ifile(filename);
  std::stringstream* ss = new std::stringstream;
  *ss << ifile.rdbuf();
  parser.SetStream(ss);
  return ss;
}

template <>
void TokenParserTestTyped<TokenParser::StreamParser<char>>::EndupParser(
    TokenParser::StreamParser<char>& parser, void* mem) {
  (void)parser;
  const std::string& filename = TokenParserTestTyped::kTmpFilename_;
  std::remove(filename.c_str());
  delete reinterpret_cast<std::stringstream*>(mem);
}

template <>
void* TokenParserTestTyped<TokenParser::FileParser>::SetupParser(
    TokenParser::FileParser& parser, const std::string& str) {
  const std::string& filename = TokenParserTestTyped::kTmpFilename_;
  std::ofstream file(filename);
  file << str;
  file.close();
  parser.SetFile(filename);
  return nullptr;
}

template <>
void TokenParserTestTyped<TokenParser::FileParser>::EndupParser(
    TokenParser::FileParser& parser, void* mem) {
  (void)parser;
  (void)mem;
  const std::string& filename = TokenParserTestTyped::kTmpFilename_;
  std::remove(filename.c_str());
}

template <typename T>
class NextTokenNoStr : public TokenParserTestTyped<T> {};
template <typename T>
class NextTokenEndLen : public TokenParserTestTyped<T> {};
template <typename T>
class NextTokenEndSpaces : public TokenParserTestTyped<T> {};
template <typename T>
class IsEnd : public TokenParserTestTyped<T> {};
template <typename T>
class NextWord : public TokenParserTestTyped<T> {};
template <typename T>
class Delims : public TokenParserTestTyped<T> {};
template <typename T>
class NextThisId : public TokenParserTestTyped<T> {};

using TokenParserTestTypedTypes =
    testing::Types<TokenParser::StringParser, TokenParser::StreamParser<char>,
                   TokenParser::FileParser>;

TYPED_TEST_SUITE(NextTokenNoStr, TokenParserTestTypedTypes);
TYPED_TEST_SUITE(NextTokenEndLen, TokenParserTestTypedTypes);
TYPED_TEST_SUITE(NextTokenEndSpaces, TokenParserTestTypedTypes);
TYPED_TEST_SUITE(IsEnd, TokenParserTestTypedTypes);
TYPED_TEST_SUITE(NextWord, TokenParserTestTypedTypes);
TYPED_TEST_SUITE(Delims, TokenParserTestTypedTypes);
TYPED_TEST_SUITE(NextThisId, TokenParserTestTypedTypes);

TYPED_TEST(NextTokenNoStr, NextWord) {
  TypeParam parser;
  std::string str = parser.NextWord();
  ASSERT_EQ("", str);
}

TYPED_TEST(NextTokenNoStr, NextInt) {
  TypeParam parser;
  TokenParser::Token tok = parser.NextInt();
  ASSERT_TRUE(tok.IsNull());
}
TYPED_TEST(NextTokenNoStr, NextUint) {
  TypeParam parser;
  TokenParser::Token tok = parser.NextUint();
  ASSERT_TRUE(tok.IsNull());
}
TYPED_TEST(NextTokenNoStr, NextFloat) {
  TypeParam parser;
  TokenParser::Token tok = parser.NextFloat();
  ASSERT_TRUE(tok.IsNull());
}

TYPED_TEST(NextTokenNoStr, NextToken) {
  TokenParser::Settings::TokenIds ids = {{0, "ada"}, {0, "bobbb"}};
  TokenParser::Settings settings;
  settings.SetTokenIds(ids);
  TypeParam parser(settings);
  TokenParser::Token tok = parser.NextId();
  ASSERT_TRUE(tok.IsNull());
}

TEST(NextTokenEndLen, NextWord_) {
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

TYPED_TEST(NextWord, WordIsWordDelim) {
  std::string parsing_str = "word==word == word = = word= =word";
  TokenParser::Settings settings;
  settings.SetWordDelim(settings.GetWordDelimChars() + "=");
  TypeParam parser(settings);
  void* mem = NextWord<TypeParam>::SetupParser(parser, parsing_str);

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
  NextWord<TypeParam>::EndupParser(parser, mem);
}

TYPED_TEST(Delims, NoWordDelimNoSpace) {
  TokenParser::Settings settings;
  settings.SetWordDelim("");
  settings.SetSpaceChars("");

  std::string parsing_str = "342 322";
  TypeParam parser(settings);
  void* mem = Delims<TypeParam>::SetupParser(parser, parsing_str);

  std::string space = " 322";
  ASSERT_EQ(parser.NextInt().GetInt(), 342);
  ASSERT_EQ(parser.NextWord(), space);
  Delims<TypeParam>::EndupParser(parser, mem);
}

TYPED_TEST(Delims, NoSpace) {
  TokenParser::Settings settings;
  settings.SetWordDelim(" ");
  settings.SetSpaceChars("");

  std::string parsing_str = "342 322";
  TypeParam parser(settings);
  void* mem = Delims<TypeParam>::SetupParser(parser, parsing_str);

  std::string space = " ";
  ASSERT_EQ(parser.NextInt().GetInt(), 342);
  ASSERT_EQ(parser.NextWord(), space);
  ASSERT_EQ(parser.NextInt().GetInt(), 322);
  Delims<TypeParam>::EndupParser(parser, mem);
}

TYPED_TEST(Delims, SpaceNotWordDelim) {
  TokenParser::Settings settings;
  settings.SetWordDelim("");
  settings.SetSpaceChars(" ");

  std::string parsing_str = "342 322 main main";
  TypeParam parser(settings);
  void* mem = Delims<TypeParam>::SetupParser(parser, parsing_str);

  ASSERT_EQ(parser.NextInt().GetInt(), 342);
  ASSERT_EQ(parser.NextInt().GetInt(), 322);
  ASSERT_EQ(parser.NextWord(), "main main");
  Delims<TypeParam>::EndupParser(parser, mem);
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
