
#include <istream>
#include <string>
#include <utility>

#include "../include/token_parser/settings.h"
#include "../include/token_parser/stream_parser.h"
#include "../include/token_parser/string_parser.h"
#include "../include/token_parser/token.h"

namespace TokenParser {

template <typename CharT>
StreamParser<CharT>::StreamParser() : StreamParser(Settings(), nullptr) {}

template <typename CharT>
StreamParser<CharT>::StreamParser(const Settings& settings)
    : StreamParser(settings, nullptr) {}

template <typename CharT>
StreamParser<CharT>::StreamParser(Settings&& settings)
    : StreamParser(std::move(settings), nullptr) {}

template <typename CharT>
StreamParser<CharT>::StreamParser(stream_type* stream)
    : StreamParser(Settings(), stream) {}

template <typename CharT>
StreamParser<CharT>::StreamParser(const Settings& settings, stream_type* stream)
    : string_parser_(StringParser(settings)),
      stream_(stream),
      buff_(std::string()) {}

template <typename CharT>
StreamParser<CharT>::StreamParser(Settings&& settings, stream_type* stream)
    : string_parser_(StringParser(std::move(settings))),
      stream_(stream),
      buff_(std::string()) {}

template <typename CharT>
StreamParser<CharT>::~StreamParser() {}

template <typename CharT>
void StreamParser<CharT>::SetStream(stream_type* str) {
  string_parser_.SetStr(nullptr);
  stream_ = str;
  buff_.clear();
}

template <typename CharT>
void StreamParser<CharT>::SetSettings(const Settings& settings) {
  string_parser_.SetSettings(settings);
}

template <typename CharT>
void StreamParser<CharT>::SetSettings(Settings&& settings) {
  string_parser_.SetSettings(std::move(settings));
}

template <typename CharT>
typename StreamParser<CharT>::stream_type* StreamParser<CharT>::GetStream()
    const {
  return stream_;
}

template <typename CharT>
const std::string* StreamParser<CharT>::GetStr() const {
  return &buff_;
}

template <typename CharT>
typename StreamParser<CharT>::size_type StreamParser<CharT>::GetI() const {
  return string_parser_.GetI();
}

template <typename CharT>
const Settings& StreamParser<CharT>::GetSettings() const {
  return string_parser_.GetSettings();
}

template <typename CharT>
Settings& StreamParser<CharT>::GetSettings() {
  return string_parser_.GetSettings();
}

template <typename CharT>
bool StreamParser<CharT>::IsEnd() const {
  if (!string_parser_.IsEnd()) return false;
  if (stream_ == nullptr) return true;
  if (stream_->eof()) return true;
  return false;
}

template <typename CharT>
std::string StreamParser<CharT>::NextWord() {
  CheckBuffOrUpdate();
  return string_parser_.NextWord();
}

template <typename CharT>
Token StreamParser<CharT>::NextInt() {
  CheckBuffOrUpdate();
  return string_parser_.NextInt();
}

template <typename CharT>
Token StreamParser<CharT>::NextUint() {
  CheckBuffOrUpdate();
  return string_parser_.NextUint();
}

template <typename CharT>
Token StreamParser<CharT>::NextFloat() {
  CheckBuffOrUpdate();
  return string_parser_.NextFloat();
}

template <typename CharT>
Token StreamParser<CharT>::NextId() {
  CheckBuffOrUpdate();
  return string_parser_.NextId();
}

template <typename CharT>
Token StreamParser<CharT>::NextThisId(Token::id_type id) {
  CheckBuffOrUpdate();
  return string_parser_.NextThisId(id);
}

template <typename CharT>
bool StreamParser<CharT>::CheckBuffOrUpdate() {
  if (!string_parser_.IsEnd()) return true;
  if (stream_ == nullptr) return false;
  if (stream_->eof()) return false;

  char delim = '\0';
  if (!GetSettings().GetWordDelimChars().empty())
    delim = GetSettings().GetWordDelimChars()[0];

  while (string_parser_.IsEnd() && !stream_->eof()) UpdateBuff(delim);

  return !string_parser_.IsEnd();
}

template <typename CharT>
void StreamParser<CharT>::UpdateBuff(char_type delim) {
  std::getline(*stream_, buff_, delim);
  if (!stream_->eof()) buff_.push_back(delim);
  string_parser_.SetStr(&buff_);
}

}  // namespace TokenParser
