#ifndef TOKEN_PARSER_SETTINGS_H_
#define TOKEN_PARSER_SETTINGS_H_

#include <map>
#include <string>

#include "token.h"

namespace TokenParser {

class Settings {
 public:
  using id_type = Token::id_type;
  using TokenIds = std::map<id_type, std::string>;

  Settings();
  Settings(const Settings& other) = default;
  Settings(Settings&& other) noexcept = default;
  Settings& operator=(const Settings& other) = default;
  Settings& operator=(Settings&& other) noexcept = default;
  virtual ~Settings();

  /// @brief Map - string and id is compared.
  void SetTokenIds(const TokenIds& token_ids);

  /// @brief Map - string and id is compared.
  void SetTokenIds(TokenIds&& token_ids);

  /// @brief Chars that will be skipped before the next Token.
  /// @param space_chars default is " \f\n\r\t\v"
  void SetSpaceChars(const std::string& space_chars);

  /// @brief Chars that will be skipped before the next Token.
  /// @param space_chars default is " \f\n\r\t\v"
  void SetSpaceChars(std::string&& space_chars);

  /// @brief Сhars that limit words.
  /// @param word_delim_chars default is " \f\n\r\t\v"
  void SetWordDelim(const std::string& word_delim_chars);

  /// @brief Сhars that limit words.
  /// @param word_delim_chars default is " \f\n\r\t\v"
  void SetWordDelim(std::string&& word_delim_chars);

  /// @brief Flag indicating that the TokenId is a whole word.
  /// @param token_id_is_full_word default is true.
  void SetTokenIdIsFullWord(bool token_id_is_full_word);

  TokenIds& GetTokenIds();
  std::string& GetSpaceChars();
  std::string& GetWordDelimChars();

  const TokenIds& GetTokenIds() const;
  const std::string& GetSpaceChars() const;
  const std::string& GetWordDelimChars() const;
  bool GetTokenIdIsFullWord() const;

 private:
  static const std::string kDefaultSpaceChars_;
  static const std::string kDefaultWordDelimChars_;

  TokenIds token_ids_;
  std::string space_chars_;
  std::string word_delim_chars_;
  bool token_id_is_full_word_;
};

}  // namespace TokenParser

#endif  // TOKEN_PARSER_SETTINGS_H_
