#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>
#include "comment.h"
#include "identifier.h"
#include "keyword.h"
#include "punctuation.h"

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

#endif