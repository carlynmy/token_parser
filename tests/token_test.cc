#include <gtest/gtest.h>

#include "../include/token_parser/token_parser.h"

using TokenParser::Token;

TEST(Token, Common) {
  Token token;
  Token token_int(Token::int_type(1));
  Token token_uint(Token::uint_type(2));
  Token token_float(Token::float_type(3));
  Token token_id(Token::id_type(4));

  ASSERT_EQ(token_int.GetType(), Token::Type::kTypeInt);
  ASSERT_EQ(token_uint.GetType(), Token::Type::kTypeUint);
  ASSERT_EQ(token_float.GetType(), Token::Type::kTypeFloat);
  ASSERT_EQ(token_id.GetType(), Token::Type::kTypeId);

  ASSERT_EQ(token_int.GetInt(), Token::int_type(1));
  ASSERT_EQ(token_uint.GetUint(), Token::uint_type(2));
  ASSERT_EQ(token_float.GetFloat(), Token::float_type(3));
  ASSERT_EQ(token_id.GetId(), Token::id_type(4));

  ASSERT_TRUE(token_int.IsInt());
  ASSERT_TRUE(token_uint.IsUint());
  ASSERT_TRUE(token_float.IsFloat());
  ASSERT_TRUE(token_id.IsId());
  ASSERT_TRUE(token.IsNull());

  ASSERT_TRUE(token_int == Token(Token::int_type(1)));
  ASSERT_TRUE(token_uint == Token(Token::uint_type(2)));
  ASSERT_TRUE(token_float == Token(Token::float_type(3)));
  ASSERT_TRUE(token_id == Token(Token::id_type(4)));
  ASSERT_TRUE(token_int != Token(Token::int_type(2)));
  ASSERT_TRUE(token_uint != Token(Token::uint_type(3)));
  ASSERT_TRUE(token_float != Token(Token::float_type(4)));
  ASSERT_TRUE(token_id != Token(Token::id_type(5)));
  ASSERT_TRUE(token_id != token_int);
  ASSERT_TRUE(token == Token(Token::kTypeNull));

  token.SetType(Token::kTypeInt);
  token.SetInt(Token::int_type(5));
  ASSERT_EQ(token.GetType(), Token::Type::kTypeInt);
  ASSERT_EQ(token.GetInt(), Token::int_type(5));
  token.SetType(Token::kTypeUint);
  token.SetUint(Token::uint_type(5));
  ASSERT_EQ(token.GetType(), Token::Type::kTypeUint);
  ASSERT_EQ(token.GetUint(), Token::uint_type(5));
  token.SetType(Token::kTypeFloat);
  token.SetFloat(Token::float_type(5));
  ASSERT_EQ(token.GetType(), Token::Type::kTypeFloat);
  ASSERT_EQ(token.GetFloat(), Token::float_type(5));
  token.SetType(Token::kTypeId);
  token.SetId(Token::id_type(5));
  ASSERT_EQ(token.GetType(), Token::Type::kTypeId);
  ASSERT_EQ(token.GetId(), Token::id_type(5));

  Token a(Token::int_type(9)), b(Token::uint_type(10));
  Token c(a);
  ASSERT_EQ(c.GetType(), Token::Type::kTypeInt);
  ASSERT_EQ(c.GetInt(), Token::int_type(9));
  c = b;
  ASSERT_EQ(c.GetType(), Token::Type::kTypeUint);
  ASSERT_EQ(c.GetUint(), Token::uint_type(10));
  c = std::move(a);
  ASSERT_EQ(c.GetType(), Token::Type::kTypeInt);
  ASSERT_EQ(c.GetInt(), Token::int_type(9));

  Token d(std::move(b));
  ASSERT_EQ(d.GetType(), Token::Type::kTypeUint);
  ASSERT_EQ(d.GetUint(), Token::uint_type(10));
}
