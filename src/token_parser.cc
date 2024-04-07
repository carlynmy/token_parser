#include "../include/token_parser/token_parser.h"

#include <cstdlib>
#include <string>
#include <utility>

#include "settings.h"
#include "token.h"

namespace TokenParser {

Parser::Parser() : Parser(Settings(), nullptr, size_type(0)) {}

Parser::Parser(const Settings& settings)
    : Parser(settings, nullptr, size_type(0)) {}

Parser::Parser(Settings&& settings)
    : Parser(std::move(settings), nullptr, size_type(0)) {}

Parser::Parser(const std::string* str, size_type i)
    : Parser(Settings(), str, i) {}

Parser::Parser(const Settings& settings, const std::string* str, size_type i)
    : settings_(settings), str_(str), i_(i) {}

Parser::Parser(Settings&& settings, const std::string* str, size_type i)
    : settings_(std::move(settings)), str_(str), i_(i) {}

Parser::~Parser() {}

void Parser::SetStr(const std::string* str) { str_ = str; }

void Parser::SetI(size_type i) { i_ = i; }

void Parser::SetSettings(const Settings& settings) { settings_ = settings; }

void Parser::SetSettings(Settings&& settings) {
  settings_ = std::move(settings);
}

const std::string* Parser::GetStr() const { return str_; }

Parser::size_type Parser::GetI() const { return i_; }

const Settings& Parser::GetSettings() const { return settings_; }

Settings& Parser::GetSettings() { return settings_; }

bool Parser::IsEnd() const {
  if (str_ == nullptr) return true;
  size_type i = NextParsingStart();
  if (i >= str_->length()) return true;
  return false;
}

std::string Parser::NextWord() {
  if (str_ == nullptr) return "";
  WordIdx word_idx = NextWordIdx();
  i_ = word_idx.start_ + word_idx.len_;
  return WordIdxToString(word_idx);
}

Token Parser::NextInt() {
  if (str_ == nullptr) return Token(Token::Type::kTypeNull);
  size_type i = NextParsingStart();
  if (i >= str_->length()) return Token(Token::Type::kTypeNull);

  size_type len;
  Token::int_type value = StrToInt(i, len);
  if (len == size_type(0)) return Token(Token::Type::kTypeNull);

  i_ = i + len;
  return Token(value);
}

Token Parser::NextUint() {
  if (str_ == nullptr) return Token(Token::Type::kTypeNull);
  size_type i = NextParsingStart();
  if (i >= str_->length()) return Token(Token::Type::kTypeNull);

  size_type len;
  Token::uint_type value = StrToUint(i, len);
  if (len == size_type(0)) return Token(Token::Type::kTypeNull);

  i_ = i + len;
  return Token(value);
}

Token Parser::NextFloat() {
  if (str_ == nullptr) return Token(Token::Type::kTypeNull);
  size_type i = NextParsingStart();
  if (i >= str_->length()) return Token(Token::Type::kTypeNull);

  size_type len;
  Token::float_type value = StrToFloat(i, len);
  if (len == size_type(0)) return Token(Token::Type::kTypeNull);

  i_ = i + len;
  return Token(value);
}

Token Parser::NextId() {
  if (str_ == nullptr) return Token(Token::Type::kTypeNull);
  size_type i = NextParsingStart();
  if (i >= str_->length()) return Token(Token::Type::kTypeNull);

  for (auto token_id : settings_.GetTokenIds()) {
    if (IsIdNext(i, token_id.second)) {
      i_ = i + token_id.second.length();
      return Token(token_id.first);
    }
  }

  return Token(Token::Type::kTypeNull);
}

Token Parser::NextThisId(Token::id_type id) {
  if (str_ == nullptr) return Token(Token::Type::kTypeNull);
  size_type i = NextParsingStart();
  if (i >= str_->length()) return Token(Token::Type::kTypeNull);

  auto iter = settings_.GetTokenIds().find(id);
  if (iter == settings_.GetTokenIds().end())
    return Token(Token::Type::kTypeNull);

  if (IsIdNext(i, iter->second)) {
    i_ = i + iter->second.length();
    return Token(iter->first);
  }

  return Token(Token::Type::kTypeNull);
}

bool Parser::IsSpace(char ch) const {
  for (auto i : settings_.GetSpaceChars())
    if (ch == i) return true;
  return false;
}

bool Parser::IsWordDelim(char ch) const {
  for (auto i : settings_.GetWordDelimChars())
    if (ch == i) return true;
  return false;
}

Parser::size_type Parser::NextParsingStart() const {
  size_type i = i_;
  while (i < str_->length() && IsSpace((*str_)[i])) ++i;
  return i;
}

Token::int_type Parser::StrToInt(size_type start, size_type& len) const {
  const char* pstart = str_->c_str() + start;
  char* pend;
  long long ans = std::strtoll(pstart, &pend, 10);

  len = pend - pstart;
  return static_cast<Token::int_type>(ans);
}

Token::uint_type Parser::StrToUint(size_type start, size_type& len) const {
  const char* pstart = str_->c_str() + start;
  char* pend;
  unsigned long long ans = std::strtoull(pstart, &pend, 10);

  len = pend - pstart;
  return static_cast<Token::uint_type>(ans);
}

Token::float_type Parser::StrToFloat(size_type start, size_type& len) const {
  const char* pstart = str_->c_str() + start;
  char* pend;
  long double ans = std::strtold(pstart, &pend);

  len = pend - pstart;
  return static_cast<Token::float_type>(ans);
}

bool Parser::IsIdNext(size_type i, const std::string& word) const {
  if (word.length() == 1 && IsWordDelim(word[0]) && word[0] == (*str_)[i]) {
    return true;
  }

  size_type stri = i;
  size_type wordi = 0;
  while (stri < str_->length() && wordi < word.length()) {
    if ((*str_)[stri] != word[wordi]) return false;

    ++stri;
    ++wordi;
  }

  if (stri >= str_->length() && wordi >= word.length()) return true;
  if (stri >= str_->length()) return false;
  if (settings_.GetTokenIdIsFullWord() && !IsWordDelim((*str_)[stri]))
    return false;
  return true;
}

Parser::WordIdx Parser::NextWordIdx() const {
  size_type start = NextParsingStart();
  size_type len = size_type(0);
  if (start >= str_->length()) return WordIdx{(size_type(0)), (size_type(0))};
  if (IsWordDelim((*str_)[start])) {
    return WordIdx{start, len + 1};
  }

  while (start + len < str_->length() && !IsWordDelim((*str_)[start + len]))
    ++len;
  return WordIdx{start, len};
}

std::string Parser::WordIdxToString(const WordIdx& word_idx) const {
  return str_->substr(word_idx.start_, word_idx.len_);
}

}  // namespace TokenParser
