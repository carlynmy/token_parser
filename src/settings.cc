
#include "../include/token_parser/settings.h"

#include <map>
#include <string>
#include <utility>

namespace TokenParser {

Settings::Settings()
    : token_ids_(kDefaultTokenIds_),
      space_chars_(kDefaultSpaceChars_),
      word_delim_chars_(kDefaultWordDelimChars_),
      token_id_is_full_word_(kDefaultTokenIdIsFullWord_),
      word_may_surrounded_by_qoutes_(kDefaultWordMaySurroundedByQoutes_),
      appropriate_quotes_(kDefaultAppropriateQuotes_) {}

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

void Settings::SetWordMaySurrondedByQoutes(bool word_may_surrounded_by_qoutes) {
  word_may_surrounded_by_qoutes_ = word_may_surrounded_by_qoutes;
}

void Settings::SetAppropriateQuotes(
    const AppropriateQuotes& appropriate_quotes) {
  appropriate_quotes_ = appropriate_quotes;
}

void Settings::SetAppropriateQuotes(AppropriateQuotes&& appropriate_quotes) {
  appropriate_quotes_ = std::move(appropriate_quotes);
}

Settings::TokenIds& Settings::GetTokenIds() { return token_ids_; }

std::string& Settings::GetSpaceChars() { return space_chars_; }

std::string& Settings::GetWordDelimChars() { return word_delim_chars_; }

Settings::AppropriateQuotes& Settings::GetAppropriateQuotes() {
  return appropriate_quotes_;
}

const Settings::TokenIds& Settings::GetTokenIds() const { return token_ids_; }

const std::string& Settings::GetSpaceChars() const { return space_chars_; }

const std::string& Settings::GetWordDelimChars() const {
  return word_delim_chars_;
}

bool Settings::GetTokenIdIsFullWord() const { return token_id_is_full_word_; }

bool Settings::GetWordMaySurrondedByQoutes() const {
  return word_may_surrounded_by_qoutes_;
}

const Settings::AppropriateQuotes& Settings::GetAppropriateQuotes() const {
  return appropriate_quotes_;
}

const Settings::TokenIds Settings::kDefaultTokenIds_ = {};
const std::string Settings::kDefaultSpaceChars_ = "\n \f\r\t\v";
const std::string Settings::kDefaultWordDelimChars_ = "\n \f\r\t\v";
const bool Settings::kDefaultTokenIdIsFullWord_ = true;
const bool Settings::kDefaultWordMaySurroundedByQoutes_ = false;
const Settings::AppropriateQuotes Settings::kDefaultAppropriateQuotes_ = {
    {'"', '"'}, {'\'', '\''}};

}  // namespace TokenParser
