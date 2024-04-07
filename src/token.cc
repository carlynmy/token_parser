#include "token.h"

namespace TokenParser {

Token::Token() : Token(Type::kTypeNull) {}

Token::Token(Type type) {
  type_ = type;
  int_ = int_type(0);
}

Token::Token(int_type value) : Token(Type::kTypeInt) { int_ = value; }

Token::Token(uint_type value) : Token(Type::kTypeUint) { uint_ = value; }

Token::Token(float_type value) : Token(Type::kTypeFloat) { float_ = value; }

Token::Token(id_type id) : Token(Type::kTypeId) { id_ = id; }

Token::~Token() {}

bool Token::operator==(const Token& other) const {
  if (GetType() != other.GetType()) return false;

  switch (GetType()) {
    case Type::kTypeInt:
      return GetInt() == other.GetInt();
      break;
    case Type::kTypeUint:
      return GetUint() == other.GetUint();
      break;
    case Type::kTypeFloat:
      return GetFloat() == other.GetFloat();
      break;
    case Type::kTypeId:
      return GetId() == other.GetId();
      break;
    default:
      break;
  }

  return true;
}

bool Token::operator!=(const Token& other) const {
  return !this->operator==(other);
}

Token::Type Token::GetType() const { return type_; }

Token::int_type Token::GetInt() const { return int_; }

Token::uint_type Token::GetUint() const { return uint_; }

Token::float_type Token::GetFloat() const { return float_; }

Token::id_type Token::GetId() const { return id_; }

void Token::SetType(Type type) { type_ = type; }

void Token::SetInt(int_type value) { int_ = value; }

void Token::SetUint(uint_type value) { uint_ = value; }

void Token::SetFloat(float_type value) { float_ = value; }

void Token::SetId(id_type id) { id_ = id; }

bool Token::IsNull() const { return GetType() == Type::kTypeNull; }

bool Token::IsInt() const { return GetType() == Type::kTypeInt; }

bool Token::IsUint() const { return GetType() == Type::kTypeUint; }

bool Token::IsFloat() const { return GetType() == Type::kTypeFloat; }

bool Token::IsId() const { return GetType() == Type::kTypeId; }

}  // namespace TokenParser
