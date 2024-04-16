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

#ifndef TOKEN_PARSER_STREAM_PARSER_H_
#define TOKEN_PARSER_STREAM_PARSER_H_

#include <istream>
#include <string>

#include "settings.h"
#include "string_parser.h"
#include "token.h"

namespace TokenParser {

/// @brief Stream parser. Parse stream to tokens. token is nothing(null), int,
/// uint, float, id(substring is compared by id).
template <typename CharT = char>
class StreamParser {
 public:
  using size_type = StringParser::size_type;
  using char_type = CharT;
  using stream_type = std::basic_istream<char_type>;

  StreamParser();
  StreamParser(const Settings& settings);
  StreamParser(Settings&& settings);
  StreamParser(stream_type* stream);
  StreamParser(const Settings& settings, stream_type* stream);
  StreamParser(Settings&& settings, stream_type* stream);
  StreamParser(const StreamParser& other) = default;
  StreamParser(StreamParser&& other) noexcept = default;
  StreamParser& operator=(const StreamParser& other) = default;
  StreamParser& operator=(StreamParser&& other) noexcept = default;
  virtual ~StreamParser();

  /// @brief Set the string that will be parsed.
  void SetStream(stream_type* str);

  /// @brief Set settings.
  void SetSettings(const Settings& settings);

  /// @brief set settings.
  void SetSettings(Settings&& settings);

  stream_type* GetStream() const;

  /// @brief Get current buffered-string from stream.
  const std::string* GetStr() const;

  /// @brief Get index current buffered-string from stream.
  size_type GetI() const;

  const Settings& GetSettings() const;
  Settings& GetSettings();

  /// @brief Check if stream is end or contain only space chars
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
  using WordIdx = StringParser::WordIdx;

  /// @brief true if we can parse further, false if all end.
  bool CheckBuffOrUpdate();
  void UpdateBuff(char_type delim);
  void AppendBuff(char_type delim);

  bool HasChar(size_type start, char_type ch) const;

  std::string NextWordQouted(size_type start);
  Token NextIdQouted(size_type start);
  Token NextThisIdQouted(size_type start, Token::id_type id);

  StringParser string_parser_;
  std::basic_istream<char_type>* stream_;
  std::string buff_;
};

}  // namespace TokenParser

#include "../../src/stream_parser.inc"

#endif  // TOKEN_PARSER_STREAM_PARSER_H_
