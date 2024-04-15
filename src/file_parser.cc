
#include "../include/token_parser/file_parser.h"

#include <fstream>
#include <string>
#include <utility>

#include "../include/token_parser/settings.h"
#include "../include/token_parser/stream_parser.h"
#include "../include/token_parser/token.h"

namespace TokenParser {

FileParser::FileParser() : FileParser(Settings(), std::string()) {}

FileParser::FileParser(const Settings& settings)
    : FileParser(settings, std::string()) {}

FileParser::FileParser(Settings&& settings)
    : FileParser(std::move(settings), std::string()) {}

FileParser::FileParser(const std::string& filename)
    : FileParser(Settings(), filename) {}

FileParser::FileParser(const Settings& settings, const std::string& filename)
    : stream_parser_(settings), file_(std::ifstream()) {
  SetFile(filename);
}

FileParser::FileParser(Settings&& settings, const std::string& filename)
    : stream_parser_(std::move(settings)), file_(std::ifstream()) {
  SetFile(filename);
}

FileParser::~FileParser() {}

void FileParser::SetFile(const std::string& filename) {
  file_.close();
  file_.open(filename);
  if (file_.fail())
    stream_parser_.SetStream(nullptr);
  else
    stream_parser_.SetStream(&file_);
}

void FileParser::SetSettings(const Settings& settings) {
  stream_parser_.SetSettings(settings);
}

void FileParser::SetSettings(Settings&& settings) {
  stream_parser_.SetSettings(std::move(settings));
}

const std::string* FileParser::GetStr() const {
  return stream_parser_.GetStr();
}

FileParser::size_type FileParser::GetI() const { return stream_parser_.GetI(); }

const Settings& FileParser::GetSettings() const {
  return stream_parser_.GetSettings();
}

Settings& FileParser::GetSettings() { return stream_parser_.GetSettings(); }

bool FileParser::IsEnd() const { return stream_parser_.IsEnd(); }

std::string FileParser::NextWord() { return stream_parser_.NextWord(); }

Token FileParser::NextInt() { return stream_parser_.NextInt(); }

Token FileParser::NextUint() { return stream_parser_.NextUint(); }

Token FileParser::NextFloat() { return stream_parser_.NextFloat(); }

Token FileParser::NextId() { return stream_parser_.NextId(); }

Token FileParser::NextThisId(Token::id_type id) {
  return stream_parser_.NextThisId(id);
}

}  // namespace TokenParser
