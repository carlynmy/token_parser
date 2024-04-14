#ifndef TOKEN_PARSER_TOKEN_H_
#define TOKEN_PARSER_TOKEN_H_

#include <cstdint>

namespace TokenParser {

/// @brief Contains one of: nothing(null), int, uint, float, id;
class Token {
 public:
  using int_type = int64_t;
  using uint_type = uint64_t;
  using float_type = double;
  using id_type = int;

  enum Type {
    kTypeNull,
    kTypeInt,
    kTypeUint,
    kTypeFloat,
    kTypeId,
  };

  /// @brief Construct null-token.
  Token();

  /// @brief Construct Token with type.
  Token(Type type);

  /// @brief Construct int-token.
  Token(int_type value);

  /// @brief Construct uint-token.
  Token(uint_type value);

  /// @brief Construct float-token.
  Token(float_type value);

  /// @brief Construct id-token
  Token(id_type id);

  Token(const Token& other) = default;
  Token(Token&& other) noexcept = default;
  Token& operator=(const Token& other) = default;
  Token& operator=(Token&& other) noexcept = default;

  virtual ~Token();

  bool operator==(const Token& other) const;
  bool operator!=(const Token& other) const;

  /// @brief Get Type token
  Type GetType() const;

  /// @brief Get int value that the token contains.
  /// @warning Undefined behavior if IsInt() == false.
  int_type GetInt() const;

  /// @brief Get uint value that the token contains.
  /// @warning Undefined behavior if IsUint() == false.
  uint_type GetUint() const;

  /// @brief Get float value that the token contains.
  /// @warning Undefined behavior if IsFloat() == false.
  float_type GetFloat() const;

  /// @brief Get id value that the token contains.
  /// @warning Undefined behavior if IsId() == false.
  id_type GetId() const;

  /// @brief Set type token.
  void SetType(Type type);

  /// @brief Set int value that the token contains.
  /// @warning Undefined behavior if IsInt() == false.
  void SetInt(int_type value);

  /// @brief Set uint value that the token contains.
  /// @warning Undefined behavior if IsUint() == false.
  void SetUint(uint_type value);

  /// @brief Set float value that the token contains.
  /// @warning Undefined behavior if IsFloat() == false.
  void SetFloat(float_type value);

  /// @brief Set id value that the token contains.
  /// @warning Undefined behavior if IsId() == false.
  void SetId(id_type id);

  bool IsNull() const;
  bool IsInt() const;
  bool IsUint() const;
  bool IsFloat() const;
  bool IsId() const;

 private:
  Type type_;
  union {
    int_type int_;
    uint_type uint_;
    float_type float_;
    id_type id_;
  };
};

}  // namespace TokenParser

#endif  // TOKEN_PARSER_TOKEN_H_
