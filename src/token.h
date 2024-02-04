#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include <stddef.h>
#include "identifier.h"
#include "punctuation.h"
#include "utf8_definitions.h"

typedef enum {
  TokenType_Identifier,
  TokenType_Punctuation,
} TokenType_t;

typedef struct {
  size_t start_byte;
  size_t line;
  size_t start_column;
  size_t length;

  union {
    bytes_t identifier;
    PunctuationLiteral_t punctuation;
  };
  TokenType_t type;
} Token_t;

typedef struct {
  Token_t* items;
  size_t count;
  size_t capacity;
} Tokens_t;

inline bool token_matches(Token_t a, Token_t b) {
  if (b.type != a.type) return false;

  switch (a.type) {
  case TokenType_Punctuation: return a.punctuation == b.punctuation;
  case TokenType_Identifier:  return utf8ncasecmp(a.identifier, b.identifier, a.length) == 0;
  }
}

#endif
