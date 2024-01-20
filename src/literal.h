#ifndef LITERAL_H
#define LITERAL_H

typedef struct {
  size_t start_byte;
  size_t line;
  size_t start_column;
  size_t length;
  const char* text;
} NumberLiteral_t;

NumberLiteral_t get_next_number_literal(const char* text, size_t* length, size_t* line) {
}

typedef struct {
  size_t start_byte;
  size_t line;
  size_t start_column;
  size_t length;
  const char* text;
} StringLiteral_t;

StringLiteral_t get_next_str_literal(const char* text, size_t* length, size_t* line) {
}

typedef struct {
  size_t start_byte;
  size_t line;
  size_t column;
  char literal;
} CharacterLiteral_t;

CharacterLiteral_t get_next_cha_literal(const char* text, size_t* length, size_t* line) {
}

typedef enum {
  LiteralType_Number,
  LiteralType_String,
  LiteralType_Character,
} LiteralType_t;

typedef struct {
  union {
    NumberLiteral_t num;
    StringLiteral_t str;
    CharacterLiteral_t cha;
  };
  LiteralType_t type;
} Literal_t;

#endif