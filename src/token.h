#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include <stddef.h>
#include "comment.h"
#include "identifier.h"
#include "keyword.h"
#include "punctuation.h"
#include "utf8.h"

typedef enum
{
  TokenType_Comment,
  TokenType_Keyword,
  TokenType_Identifier,
  TokenType_Punctuation,
} TokenType_t;

typedef struct
{
  union
  {
    Comment_t comment;
    Keyword_t keyword;
    Identifier_t identifier;
    Punctuation_t punctuation;
  };
  TokenType_t type;
} Token_t;

typedef struct
{
  Token_t *items;
  size_t count;
  size_t capacity;
} Tokens_t;

inline bool token_matches(Token_t a, Token_t b) {
  if (b.type != a.type) return false;

  switch (a.type) {
  case TokenType_Punctuation:
    return a.punctuation.literal == b.punctuation.literal;
  case TokenType_Keyword:
    return a.keyword.literal == b.keyword.literal;
  case TokenType_Identifier:
    return utf8ncasecmp(a.identifier.text, b.identifier.text, a.identifier.length) == 0;
  case TokenType_Comment:
    return utf8ncasecmp(a.comment.text, b.comment.text, a.comment.length) == 0;
  }
}

#endif
