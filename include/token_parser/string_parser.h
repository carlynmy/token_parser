/*

USAGE:

#include "token_parser/file_parser.h"
#include "token_parser/stream_parser.h"
#include "token_parser/string_parser.h"

1. Setup settings:
  TokenParser::Settings::TokenIds token_ids;
  token_ids.insert({0, ";"});
  token_ids.insert({1, "("});
  token_ids.insert({2, ")"});
  token_ids.insert({3, "{"});
  token_ids.insert({4, "}"});
  token_ids.insert({5, "int"});
  token_ids.insert({6, "int32_t"});
  token_ids.insert({7, "="});
  TokenParser::Settings settings;
  settings.SetTokenIds(token_ids);
  settings.SetWordDelim(settings.GetWordDelimChars() + ";(){}=");
  settings.SetTokenIdIsFullWord(true);

  TokenParser::Settings::TokenIds token_ids;
  token_ids.insert({0, "sin"});
  token_ids.insert({1, "cos"});
  TokenParser::Settings settings;
  settings.SetTokenIds(token_ids);
  settings.SetTokenIdIsFullWord(false);

2. Create parser
  TokenParser::StringParser string_parser(settings);
  std::string str = "int32_t main() { int a=3.3; }";
  string_parser.SetStr(&str);

  TokenParser::StreamParser stream_parser(settings);
  std::stringstream ss = "sincos";
  stream_parser.SetStream(&ss);

  TokenParser::StreamParser stream_parser(settings);
  std::ifstream fs("filename");
  stream_parser.SetStream(&fs);

  TokenParser::FileParser file_parser(settings);
  file_parser.SetFile("filename");

3. Use by Next* methods. Check if end by IsEnd() method.

  std::string str = "int32_t main() { int a=3.3; }";
  TokenParser::Token token_int32_t = parser.NextId();   // GetId() == 6
  std::string word_main = parser.NextWord();            // word == "main"
  TokenParser::Token token_ob = parser.NextId();        // GetId() == 1
  TokenParser::Token token_cb = parser.NextId();        // GetId() == 2
  TokenParser::Token token_ob2 = parser.NextId();       // GetId() == 3
  TokenParser::Token token_int = parser.NextId();       // GetId() == 5
  std::string word_a = parser.NextWord();               // word == "a"
  TokenParser::Token token_eq = parser.NextId();        // GetId() == 7
  TokenParser::Token token_float = parser.NextFloat();  // GetFloat() == 3.3
  TokenParser::Token token_semicolon = parser.NextId(); // GetId() == 0
  TokenParser::Token token_cb2 = parser.NextId();       // GetId() == 4
  TokenParser::Token token_null = parser.NextId();      // IsNull() == true
  parser.IsEnd()                                        // true

  std::string str = "sincos";
  TokenParser::Token token_sin = parser.NextId();   // GetId() == 0
  TokenParser::Token token_cos = parser.NextId();   // GetId() == 1

*/

#ifndef TOKEN_PARSER_STRING_PARSER_H_
#define TOKEN_PARSER_STRING_PARSER_H_

#include <string>

#include "settings.h"
#include "token.h"

namespace TokenParser {

/// @brief Token parser. Parse string to tokens. token is nothing(null), int,
/// uint, float, id(substring is compared by id).
class StringParser {
 public:
  using size_type = std::string::size_type;

  StringParser();
  StringParser(const std::string* str, size_type i = 0);
  StringParser(const Settings& settings);
  StringParser(const Settings& settings, const std::string* str,
               size_type i = 0);
  StringParser(Settings&& settings);
  StringParser(Settings&& settings, const std::string* str, size_type i = 0);
  StringParser(const StringParser& other) = default;
  StringParser(StringParser&& other) noexcept = default;
  StringParser& operator=(const StringParser& other) = default;
  StringParser& operator=(StringParser&& other) noexcept = default;
  virtual ~StringParser();

  /// @brief Set the string that will be parsed. Sets i = 0.
  void SetStr(const std::string* str);

  /// @brief Set the index from which the next parsing will be performed.
  void SetI(size_type i);

  /// @brief Set settings.
  void SetSettings(const Settings& settings);

  /// @brief set settings.
  void SetSettings(Settings&& settings);

  const std::string* GetStr() const;
  size_type GetI() const;
  const Settings& GetSettings() const;
  Settings& GetSettings();

  /// @brief Check if parsing str is end or contain only space chars
  /// (settings.GetSpaceChars()).
  bool IsEnd() const;

  /// @brief Get the next word. Word is a substring limited by word delim chars
  /// (settings.GetWordDelimChars).
  /// @return Next word or empty string if no word next.
  std::string NextWord();

  /// @brief Get next int-token.
  /// @return Next int-token or null-token if no int next.
  Token NextInt();

  /// @brief Get next unt-token.
  /// @return Next unt-token or null-token if no uint next.
  Token NextUint();

  /// @brief Get next float-token.
  /// @return Next float-token or null-token if no float next.
  Token NextFloat();

  /// @brief Get next id-token.
  /// @return Next id-token or null-token if no id next.
  Token NextId();

  /// @brief Get next this id-token.
  /// @param id this id-token.
  /// @return Next this id-token or null-token if no this id next.
  Token NextThisId(Token::id_type id);

 private:
  struct WordIdx {
    size_type start_;
    size_type len_;
  };

  bool IsSpace(char ch) const;
  bool IsWordDelim(char ch) const;
  bool IsQoute(char ch) const;
  size_type NextParsingStart() const;

  Token::int_type StrToInt(size_type start, size_type& len) const;
  Token::uint_type StrToUint(size_type start, size_type& len) const;
  Token::float_type StrToFloat(size_type start, size_type& len) const;

  bool IsIdNext(size_type i, const std::string& word) const;

  WordIdx NextWordIdx() const;
  WordIdx NextWordIdxQouted(size_type start) const;
  std::string WordIdxToString(const WordIdx& word_idx) const;

  Settings settings_;
  const std::string* str_;
  size_type i_;
};

}  // namespace TokenParser

#endif  // TOKEN_PARSER_STRING_PARSER_H_
