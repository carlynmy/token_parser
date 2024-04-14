
#include "../include/token_parser/settings.h"

#include <map>
#include <string>
#include <utility>

namespace TokenParser {

Settings::Settings()
    : space_chars_(kDefaultSpaceChars_),
      word_delim_chars_(kDefaultWordDelimChars_),
      token_id_is_full_word_(true) {}

Settings::~Settings() {}

void Settings::SetTokenIds(const TokenIds& token_ids) {
  token_ids_ = token_ids;
}

void Settings::SetTokenIds(TokenIds&& token_ids) {
  token_ids_ = std::move(token_ids);
}

void Settings::SetSpaceChars(const std::string& space_chars) {
  space_chars_ = space_chars;
}

void Settings::SetSpaceChars(std::string&& space_chars) {
  space_chars_ = std::move(space_chars);
}

void Settings::SetWordDelim(const std::string& word_delim_chars) {
  word_delim_chars_ = word_delim_chars;
}

void Settings::SetWordDelim(std::string&& word_delim_chars) {
  word_delim_chars_ = std::move(word_delim_chars);
}

void Settings::SetTokenIdIsFullWord(bool token_id_is_full_word) {
  token_id_is_full_word_ = token_id_is_full_word;
}

Settings::TokenIds& Settings::GetTokenIds() { return token_ids_; }

std::string& Settings::GetSpaceChars() { return space_chars_; }

std::string& Settings::GetWordDelimChars() { return word_delim_chars_; }

const Settings::TokenIds& Settings::GetTokenIds() const { return token_ids_; }

const std::string& Settings::GetSpaceChars() const { return space_chars_; }

const std::string& Settings::GetWordDelimChars() const {
  return word_delim_chars_;
}

bool Settings::GetTokenIdIsFullWord() const { return token_id_is_full_word_; }

const std::string Settings::kDefaultSpaceChars_ = " \f\n\r\t\v";
const std::string Settings::kDefaultWordDelimChars_ = " \f\n\r\t\v";

}  // namespace TokenParser
