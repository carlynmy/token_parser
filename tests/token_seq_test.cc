#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/token_parser/file_parser.h"
#include "../include/token_parser/stream_parser.h"
#include "../include/token_parser/string_parser.h"
#include "tests.h"

using TokenParser::Settings;
using TokenParser::StringParser;
using TokenParser::Token;

struct TestTokenParserTokenSeqDataNextRes {
  bool is_token_;
  std::string str_;
  TokenParser::Token token_;
};

struct TestTokenParserTokenSeqData {
  using Seq = std::vector<TestTokenParserTokenSeqDataNextRes>;

  int parser_idx_;
  int parsing_str_idx_;
  TokenParser::StringParser::size_type i_;
  int seq_idx_;

  static std::vector<Seq> seqs_;
};

std::vector<TestTokenParserTokenSeqData::Seq>
    TestTokenParserTokenSeqData::seqs_ = {
        {
            {true, "", Token(Token::id_type(6))},
            {false, "main", Token()},
            {true, "", Token(Token::id_type(1))},
            {true, "", Token(Token::id_type(2))},
            {true, "", Token(Token::id_type(3))},
            {true, "", Token(Token::id_type(5))},
            {false, "a", Token()},
            {true, "", Token(Token::id_type(7))},
            {true, "", Token(Token::float_type(3.3))},
            {true, "", Token(Token::id_type(0))},
            {true, "", Token(Token::id_type(4))},
        },
        {
            {true, "", Token(Token::id_type(0))},
            {true, "", Token(Token::id_type(1))},
        },
        {
            {true, "", Token(Token::int_type(-4))},
        },
        {
            {true, "", Token(Token::uint_type(4))},
        },
        {
            {true, "", Token(Token::float_type(4.4e+3))},
        },
        {
            {true, "", Token(Token::id_type(6))},
        },
        {
            {true, "", Token(Token::id_type(5))},
        },
        {
            {true, "", Token(Token::id_type(7))},
        },
        {
            {false, "main", Token()},
        },
        {
            {true, "", Token(Token::int_type(-4))},
            {true, "", Token(Token::uint_type(4))},
        },
        {
            {true, "", Token(Token::int_type(-134))},
            {true, "", Token(Token::float_type(0.1))},
        },
        {
            {true, "", Token(Token::int_type(-4))},
            {true, "", Token(Token::id_type(6))},
        },
        {
            {true, "", Token(Token::int_type(-4))},
            {true, "", Token(Token::id_type(5))},
        },
        {
            {true, "", Token(Token::int_type(-4))},
            {true, "", Token(Token::id_type(7))},
        },
        {
            {true, "", Token(Token::int_type(-4))},
            {false, "main", Token()},
        },
        {
            {true, "", Token(Token::uint_type(4))},
            {true, "", Token(Token::int_type(-4))},
        },
        {
            {true, "", Token(Token::uint_type(134))},
            {true, "", Token(Token::float_type(0.1))},
        },
        {
            {true, "", Token(Token::uint_type(4))},
            {true, "", Token(Token::id_type(6))},
        },
        {
            {true, "", Token(Token::uint_type(4))},
            {true, "", Token(Token::id_type(5))},
        },
        {
            {true, "", Token(Token::uint_type(4))},
            {true, "", Token(Token::id_type(7))},
        },
        {
            {true, "", Token(Token::uint_type(4))},
            {false, "main", Token()},
        },
        {
            {true, "", Token(Token::float_type(-1.1))},
            {true, "", Token(Token::int_type(-2))},
        },
        {
            {true, "", Token(Token::float_type(-1.1))},
            {true, "", Token(Token::uint_type(2))},
        },
        {
            {true, "", Token(Token::float_type(-1.1))},
            {true, "", Token(Token::float_type(-2.1))},
        },
        {
            {true, "", Token(Token::float_type(-1.1))},
            {true, "", Token(Token::id_type(6))},
        },
        {
            {true, "", Token(Token::float_type(-1.1))},
            {true, "", Token(Token::id_type(5))},
        },
        {
            {true, "", Token(Token::float_type(-1.1))},
            {true, "", Token(Token::id_type(7))},
        },
        {
            {true, "", Token(Token::float_type(-1.1))},
            {false, "main", Token()},
        },

        {
            {true, "", Token(Token::id_type(6))},
            {true, "", Token(Token::int_type(-2))},
        },
        {
            {true, "", Token(Token::id_type(6))},
            {true, "", Token(Token::uint_type(2))},
        },
        {
            {true, "", Token(Token::id_type(6))},
            {true, "", Token(Token::float_type(-2.2))},
        },
        {
            {true, "", Token(Token::id_type(6))},
            {true, "", Token(Token::id_type(6))},
        },
        {
            {true, "", Token(Token::id_type(6))},
            {true, "", Token(Token::id_type(5))},
        },
        {
            {true, "", Token(Token::id_type(6))},
            {true, "", Token(Token::id_type(7))},
        },
        {
            {true, "", Token(Token::id_type(6))},
            {false, "main", Token()},
        },
        {
            {true, "", Token(Token::kTypeNull)},
        },

        {
            {true, "", Token(Token::id_type(5))},
            {true, "", Token(Token::int_type(-2))},
        },
        {
            {true, "", Token(Token::id_type(5))},
            {true, "", Token(Token::uint_type(2))},
        },
        {
            {true, "", Token(Token::id_type(5))},
            {true, "", Token(Token::float_type(-2.2))},
        },
        {
            {true, "", Token(Token::id_type(5))},
            {true, "", Token(Token::id_type(6))},
        },
        {
            {true, "", Token(Token::id_type(5))},
            {true, "", Token(Token::id_type(5))},
        },
        {
            {true, "", Token(Token::id_type(5))},
            {true, "", Token(Token::id_type(7))},
        },
        {
            {true, "", Token(Token::id_type(5))},
            {false, "main", Token()},
        },
        {
            {true, "", Token(Token::kTypeNull)},
        },

        {
            {true, "", Token(Token::id_type(7))},
            {true, "", Token(Token::int_type(-2))},
        },
        {
            {true, "", Token(Token::id_type(7))},
            {true, "", Token(Token::uint_type(2))},
        },
        {
            {true, "", Token(Token::id_type(7))},
            {true, "", Token(Token::float_type(-2.2))},
        },
        {
            {true, "", Token(Token::id_type(7))},
            {true, "", Token(Token::id_type(6))},
        },
        {
            {true, "", Token(Token::id_type(7))},
            {true, "", Token(Token::id_type(5))},
        },
        {
            {true, "", Token(Token::id_type(7))},
            {true, "", Token(Token::id_type(7))},
        },
        {
            {true, "", Token(Token::id_type(7))},
            {false, "main", Token()},
        },

        {
            {false, "main", Token()},
            {true, "", Token(Token::int_type(-2))},
        },
        {
            {false, "main", Token()},
            {true, "", Token(Token::uint_type(2))},
        },
        {
            {false, "main", Token()},
            {true, "", Token(Token::float_type(-2.2))},
        },
        {
            {false, "main", Token()},
            {true, "", Token(Token::id_type(6))},
        },
        {
            {false, "main", Token()},
            {true, "", Token(Token::id_type(5))},
        },
        {
            {false, "main", Token()},
            {true, "", Token(Token::id_type(7))},
        },
        {
            {false, "main", Token()},
            {false, "main", Token()},
        },
        {
            {false, "main-2", Token()},
        },
        {
            {false, "main2", Token()},
        },
        {
            {false, "main-2.2", Token()},
        },
        {
            {false, "mainint32_t", Token()},
        },
        {
            {false, "mainc", Token()},
        },
        {
            {false, "main", Token()},
            {true, "", Token(Token::id_type(7))},
        },
        {
            {false, "mainmain", Token()},
        },

        {
            {true, "", Token(Token::id_type(12))},
            {true, "", Token(Token::id_type(11))},
            {false, "<main>", Token()},
            {true, "", Token(Token::int_type(345))},
            {true, "", Token(Token::id_type(9))},
            {false, "\'word with 123 space\'", Token()},
        },
        {
            {false, "' word with \" qoutes \" <> <> qoitiis '", Token()},
        },
        {
            {true, "", Token(Token::id_type(12))},
            {true, "", Token(Token::id_type(11))},
            {false, "<ma\nin>", Token()},
            {true, "", Token(Token::int_type(345))},
            {true, "", Token(Token::id_type(13))},
            {false, "\'word \nwith 123 space\'", Token()},
        },
        {
            {true, "", Token(Token::id_type(12))},
            {true, "", Token(Token::id_type(11))},
            {false, "<ma\n\nin>", Token()},
            {true, "", Token(Token::int_type(345))},
            {true, "", Token(Token::id_type(14))},
            {false, "\'word \nwith 123 \nspace\'", Token()},
        },
        {
            {true, "", Token(Token::id_type(11))},
            {true, "", Token(Token::id_type(7))},
            {false, "'word\nwith\nno\n\nend bracket", Token()},
        },

};

class TestTokenParserTokenSeq : public TestTokenParser {
 public:
  static int count_;
  static std::vector<TestTokenParserTokenSeqData> test_data_;
};

std::vector<TestTokenParserTokenSeqData> TestTokenParserTokenSeq::test_data_ = {
    {0, 0, 0, 0},    {1, 1, 0, 1},

    {2, 2, 0, 2},    {2, 3, 0, 3},    {2, 4, 0, 4},    {2, 5, 0, 5},
    {2, 6, 0, 6},    {2, 7, 0, 7},    {2, 8, 0, 8},    {2, 9, 0, 2},
    {2, 10, 0, 3},   {2, 11, 0, 4},   {2, 12, 0, 5},   {2, 13, 0, 6},
    {2, 14, 0, 7},   {2, 15, 0, 8},   {3, 2, 0, 2},    {3, 3, 0, 3},
    {3, 4, 0, 4},    {3, 5, 0, 5},    {3, 6, 0, 6},    {3, 7, 0, 7},
    {3, 8, 0, 8},    {3, 9, 0, 2},    {3, 10, 0, 3},   {3, 11, 0, 4},
    {3, 12, 0, 5},   {3, 13, 0, 6},   {3, 14, 0, 7},   {3, 15, 0, 8},

    {2, 16, 0, 9},   {2, 17, 0, 10},  {2, 18, 0, 11},  {2, 19, 0, 12},
    {2, 20, 0, 13},  {2, 21, 0, 14},  {2, 22, 0, 9},   {2, 23, 0, 10},
    {2, 24, 0, 11},  {2, 25, 0, 12},  {2, 26, 0, 13},  {2, 27, 0, 14},
    {3, 16, 0, 9},   {3, 17, 0, 10},  {3, 18, 0, 11},  {3, 19, 0, 12},
    {3, 20, 0, 13},  {3, 21, 0, 14},  {3, 22, 0, 9},   {3, 23, 0, 10},
    {3, 24, 0, 11},  {3, 25, 0, 12},  {3, 26, 0, 13},  {3, 27, 0, 14},

    {2, 28, 0, 15},  {2, 29, 0, 16},  {2, 30, 0, 17},  {2, 31, 0, 18},
    {2, 32, 0, 19},  {2, 33, 0, 20},  {2, 34, 0, 15},  {2, 35, 0, 16},
    {2, 36, 0, 17},  {2, 37, 0, 18},  {2, 38, 0, 19},  {2, 39, 0, 20},
    {3, 28, 0, 15},  {3, 29, 0, 16},  {3, 30, 0, 17},  {3, 31, 0, 18},
    {3, 32, 0, 19},  {3, 33, 0, 20},  {3, 34, 0, 15},  {3, 35, 0, 16},
    {3, 36, 0, 17},  {3, 37, 0, 18},  {3, 38, 0, 19},  {3, 39, 0, 20},

    {2, 40, 0, 21},  {2, 41, 0, 22},  {2, 42, 0, 23},  {2, 43, 0, 24},
    {2, 44, 0, 25},  {2, 45, 0, 26},  {2, 46, 0, 27},  {2, 47, 0, 21},
    {2, 48, 0, 22},  {2, 49, 0, 23},  {2, 50, 0, 24},  {2, 51, 0, 25},
    {2, 52, 0, 26},  {2, 53, 0, 27},  {3, 40, 0, 21},  {3, 41, 0, 22},
    {3, 42, 0, 23},  {3, 43, 0, 24},  {3, 44, 0, 25},  {3, 45, 0, 26},
    {3, 46, 0, 27},  {3, 47, 0, 21},  {3, 48, 0, 22},  {3, 49, 0, 23},
    {3, 50, 0, 24},  {3, 51, 0, 25},  {3, 52, 0, 26},  {3, 53, 0, 27},

    {2, 54, 0, 28},  {2, 55, 0, 29},  {2, 56, 0, 30},  {2, 57, 0, 31},
    {2, 58, 0, 32},  {2, 59, 0, 33},  {2, 60, 0, 34},  {2, 61, 0, 35},
    {2, 62, 0, 35},  {2, 63, 0, 35},  {2, 64, 0, 35},  {2, 65, 0, 35},
    {2, 66, 0, 33},  {2, 67, 0, 35},  {3, 54, 0, 28},  {3, 55, 0, 29},
    {3, 56, 0, 30},  {3, 57, 0, 31},  {3, 58, 0, 32},  {3, 59, 0, 33},
    {3, 60, 0, 34},  {3, 61, 0, 28},  {3, 62, 0, 29},  {3, 63, 0, 30},
    {3, 64, 0, 31},  {3, 65, 0, 32},  {3, 66, 0, 33},  {3, 67, 0, 34},

    {2, 68, 0, 36},  {2, 69, 0, 37},  {2, 70, 0, 38},  {2, 71, 0, 39},
    {2, 72, 0, 40},  {2, 73, 0, 41},  {2, 74, 0, 42},  {2, 75, 0, 35},
    {2, 76, 0, 35},  {2, 77, 0, 35},  {2, 78, 0, 43},  {2, 79, 0, 43},
    {2, 80, 0, 41},  {2, 81, 0, 43},  {3, 68, 0, 36},  {3, 69, 0, 37},
    {3, 70, 0, 38},  {3, 71, 0, 39},  {3, 72, 0, 40},  {3, 73, 0, 41},
    {3, 74, 0, 42},  {3, 75, 0, 36},  {3, 76, 0, 37},  {3, 77, 0, 38},
    {3, 78, 0, 39},  {3, 79, 0, 40},  {3, 80, 0, 41},  {3, 81, 0, 42},

    {2, 82, 0, 44},  {2, 83, 0, 45},  {2, 84, 0, 46},  {2, 85, 0, 47},
    {2, 86, 0, 48},  {2, 87, 0, 49},  {2, 88, 0, 50},  {2, 89, 0, 44},
    {2, 90, 0, 45},  {2, 91, 0, 46},  {2, 92, 0, 47},  {2, 93, 0, 48},
    {2, 94, 0, 49},  {2, 95, 0, 50},  {3, 82, 0, 44},  {3, 83, 0, 45},
    {3, 84, 0, 46},  {3, 85, 0, 47},  {3, 86, 0, 48},  {3, 87, 0, 49},
    {3, 88, 0, 50},  {3, 89, 0, 44},  {3, 90, 0, 45},  {3, 91, 0, 46},
    {3, 92, 0, 47},  {3, 93, 0, 48},  {3, 94, 0, 49},  {3, 95, 0, 50},

    {2, 96, 0, 51},  {2, 97, 0, 52},  {2, 98, 0, 53},  {2, 99, 0, 54},
    {2, 100, 0, 55}, {2, 101, 0, 56}, {2, 102, 0, 57}, {2, 103, 0, 58},
    {2, 104, 0, 59}, {2, 105, 0, 60}, {2, 106, 0, 61}, {2, 107, 0, 62},
    {2, 108, 0, 63}, {2, 109, 0, 64}, {3, 96, 0, 51},  {3, 97, 0, 52},
    {3, 98, 0, 53},  {3, 99, 0, 54},  {3, 100, 0, 55}, {3, 101, 0, 56},
    {3, 102, 0, 57}, {3, 103, 0, 58}, {3, 104, 0, 59}, {3, 105, 0, 60},
    {3, 106, 0, 61}, {3, 107, 0, 62}, {3, 108, 0, 63}, {3, 109, 0, 64},

    {4, 110, 0, 65}, {4, 111, 0, 66}, {4, 112, 0, 67}, {4, 113, 0, 68},
    {4, 114, 0, 69},

};

int TestTokenParserTokenSeq::count_ =
    TestTokenParserTokenSeq::test_data_.size();

TEST_P(TestTokenParserTokenSeq, Common) {
  int num_test = this->GetParam();
  TestTokenParserTokenSeqData& test_data =
      TestTokenParserTokenSeq::test_data_[num_test];

  TokenParser::StringParser parser(
      TestTokenParser::parsers_[test_data.parser_idx_]);
  parser.SetStr(&TestTokenParser::strs_[test_data.parsing_str_idx_]);
  parser.SetI(test_data.i_);

  TestTokenParserTokenSeqData::Seq seq =
      TestTokenParserTokenSeqData::seqs_[test_data.seq_idx_];

  for (auto i : seq) {
    if (!i.is_token_) {
      std::string res = parser.NextWord();
      ASSERT_EQ(res, i.str_);
      continue;
    }

    TokenParser::Token token;
    if (i.token_.IsInt())
      token = parser.NextInt();
    else if (i.token_.IsUint())
      token = parser.NextUint();
    else if (i.token_.IsFloat())
      token = parser.NextFloat();
    else
      token = parser.NextId();

    ASSERT_EQ(token, i.token_);
  }
}

TEST_P(TestTokenParserTokenSeq, FileParser) {
  int num_test = this->GetParam();
  TestTokenParserTokenSeqData& test_data =
      TestTokenParserTokenSeq::test_data_[num_test];

  const std::string kTmpFilename = ".tmp_token_parser_token_seq_test.txt";
  std::ofstream file(kTmpFilename);
  file << TestTokenParser::strs_[test_data.parsing_str_idx_];
  file.close();
  TokenParser::FileParser parser;
  parser.SetSettings(
      TestTokenParser::parsers_[test_data.parser_idx_].GetSettings());
  parser.SetFile(kTmpFilename);

  TestTokenParserTokenSeqData::Seq seq =
      TestTokenParserTokenSeqData::seqs_[test_data.seq_idx_];

  for (auto i : seq) {
    if (!i.is_token_) {
      std::string res = parser.NextWord();
      ASSERT_EQ(res, i.str_);
      continue;
    }

    TokenParser::Token token;
    if (i.token_.IsInt())
      token = parser.NextInt();
    else if (i.token_.IsUint())
      token = parser.NextUint();
    else if (i.token_.IsFloat())
      token = parser.NextFloat();
    else
      token = parser.NextId();

    ASSERT_EQ(token, i.token_);
  }

  std::remove(kTmpFilename.c_str());
}

TEST_P(TestTokenParserTokenSeq, FileParserNextThisId) {
  int num_test = this->GetParam();
  TestTokenParserTokenSeqData& test_data =
      TestTokenParserTokenSeq::test_data_[num_test];

  const std::string kTmpFilename = ".tmp_token_parser_token_seq_test.txt";
  std::ofstream file(kTmpFilename);
  file << TestTokenParser::strs_[test_data.parsing_str_idx_];
  file.close();
  TokenParser::FileParser parser;
  parser.SetSettings(
      TestTokenParser::parsers_[test_data.parser_idx_].GetSettings());
  parser.SetFile(kTmpFilename);

  TestTokenParserTokenSeqData::Seq seq =
      TestTokenParserTokenSeqData::seqs_[test_data.seq_idx_];

  for (auto i : seq) {
    if (!i.is_token_) {
      std::string res = parser.NextWord();
      ASSERT_EQ(res, i.str_);
      continue;
    }

    TokenParser::Token token;
    if (i.token_.IsInt())
      token = parser.NextInt();
    else if (i.token_.IsUint())
      token = parser.NextUint();
    else if (i.token_.IsFloat())
      token = parser.NextFloat();
    else
      token = parser.NextThisId(i.token_.GetId());

    ASSERT_EQ(token, i.token_);
  }

  std::remove(kTmpFilename.c_str());
}

TEST_P(TestTokenParserTokenSeq, StreamParserIfstream) {
  int num_test = this->GetParam();
  TestTokenParserTokenSeqData& test_data =
      TestTokenParserTokenSeq::test_data_[num_test];

  int tmp = 0;
  if (num_test == 220)
    tmp++;
  else if (num_test == 221)
    tmp++;
  else if (num_test == 222)
    tmp++;

  const std::string kTmpFilename = ".tmp_token_parser_token_seq_test.txt";
  std::ofstream file(kTmpFilename);
  file << TestTokenParser::strs_[test_data.parsing_str_idx_];
  file.close();

  const TokenParser::Settings& sett =
      TestTokenParser::parsers_[test_data.parser_idx_].GetSettings();

  std::ifstream ifile(kTmpFilename);
  TokenParser::StreamParser parser(sett, &ifile);

  TestTokenParserTokenSeqData::Seq seq =
      TestTokenParserTokenSeqData::seqs_[test_data.seq_idx_];

  for (auto i : seq) {
    if (!i.is_token_) {
      std::string res = parser.NextWord();
      ASSERT_EQ(res, i.str_);
      continue;
    }

    TokenParser::Token token;
    if (i.token_.IsInt())
      token = parser.NextInt();
    else if (i.token_.IsUint())
      token = parser.NextUint();
    else if (i.token_.IsFloat())
      token = parser.NextFloat();
    else
      token = parser.NextId();

    ASSERT_EQ(token, i.token_);
  }

  std::remove(kTmpFilename.c_str());
}

TEST_P(TestTokenParserTokenSeq, StreamParserStringstream) {
  int num_test = this->GetParam();
  TestTokenParserTokenSeqData& test_data =
      TestTokenParserTokenSeq::test_data_[num_test];

  const std::string kTmpFilename = ".tmp_token_parser_token_seq_test.txt";
  std::ofstream file(kTmpFilename);
  file << TestTokenParser::strs_[test_data.parsing_str_idx_];
  file.close();

  const TokenParser::Settings& sett =
      TestTokenParser::parsers_[test_data.parser_idx_].GetSettings();

  std::ifstream ifile(kTmpFilename);
  std::stringstream ss;
  ss << ifile.rdbuf();
  TokenParser::StreamParser parser(&ss);
  parser.SetSettings(sett);

  TestTokenParserTokenSeqData::Seq seq =
      TestTokenParserTokenSeqData::seqs_[test_data.seq_idx_];

  for (auto i : seq) {
    if (!i.is_token_) {
      std::string res = parser.NextWord();
      ASSERT_EQ(res, i.str_);
      continue;
    }

    TokenParser::Token token;
    if (i.token_.IsInt())
      token = parser.NextInt();
    else if (i.token_.IsUint())
      token = parser.NextUint();
    else if (i.token_.IsFloat())
      token = parser.NextFloat();
    else
      token = parser.NextId();

    ASSERT_EQ(token, i.token_);
  }

  std::remove(kTmpFilename.c_str());
}

INSTANTIATE_TEST_SUITE_P(My, TestTokenParserTokenSeq,
                         testing::Range(0, TestTokenParserTokenSeq::count_));