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
  using AppropriateQuotes = std::map<char, char>;

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
  /// @warning For correct work, it is recommended to add all quotes (if
  /// GetWordMaySurrondedByQoutes() == true) and space chars here.
  /// @param word_delim_chars default is "\n \f\r\t\v"
  void SetWordDelim(const std::string& word_delim_chars);

  /// @brief Сhars that limit words.
  /// @warning For correct work, it is recommended to add all quotes (if
  /// GetWordMaySurrondedByQoutes() == true) and space chars here.
  /// @param word_delim_chars default is "\n \f\r\t\v"
  void SetWordDelim(std::string&& word_delim_chars);

  /// @brief Flag indicating that the TokenId is a whole word.
  /// @param token_id_is_full_word default is true.
  void SetTokenIdIsFullWord(bool token_id_is_full_word);

  /// @brief Flag indicating that the word may by surronded by qoutes.
  /// @brief Example: str = "word = 'word with spaces' ", with GetI() == 5,
  /// NextWord() == "'word with spaces'".
  /// @param word_may_surrounded_by_qoutes default is false.
  void SetWordMaySurrondedByQoutes(bool word_may_surrounded_by_qoutes);

  /// @brief Map - open quote and appropriate close qoute. Use to take word
  /// surronded by qoutes, if GetWordMaySurrondedByQoutes() == true.
  /// @param appropriate_quotes default is {{'"', '"'}, {'\''. '\''}}.
  void SetAppropriateQuotes(const AppropriateQuotes& appropriate_quotes);

  /// @brief Map - open quote and appropriate close qoute. Use to take word
  /// surronded by qoutes, if GetWordMaySurrondedByQoutes() == true.
  /// @param appropriate_quotes default is {{'"', '"'}, {'\''. '\''}}.
  void SetAppropriateQuotes(AppropriateQuotes&& appropriate_quotes);

  TokenIds& GetTokenIds();
  std::string& GetSpaceChars();
  std::string& GetWordDelimChars();
  AppropriateQuotes& GetAppropriateQuotes();

  const TokenIds& GetTokenIds() const;
  const std::string& GetSpaceChars() const;
  const std::string& GetWordDelimChars() const;
  bool GetTokenIdIsFullWord() const;
  bool GetWordMaySurrondedByQoutes() const;
  const AppropriateQuotes& GetAppropriateQuotes() const;

 private:
  static const TokenIds kDefaultTokenIds_;
  static const std::string kDefaultSpaceChars_;
  static const std::string kDefaultWordDelimChars_;
  static const bool kDefaultTokenIdIsFullWord_;
  static const bool kDefaultWordMaySurroundedByQoutes_;
  static const AppropriateQuotes kDefaultAppropriateQuotes_;

  TokenIds token_ids_;
  std::string space_chars_;
  std::string word_delim_chars_;
  bool token_id_is_full_word_;
  bool word_may_surrounded_by_qoutes_;
  AppropriateQuotes appropriate_quotes_;
};

}  // namespace TokenParser

#endif  // TOKEN_PARSER_SETTINGS_H_
