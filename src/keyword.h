#ifndef KEYWORD_H
#define KEYWORD_H

#include <stddef.h>
#include <string.h>

typedef enum {
  KeywordLiteral_Fn,
  KeywordLiteral_If,
  KeywordLiteral_For,
  KeywordLiteral_Pub,
  KeywordLiteral_Mut,
  KeywordLiteral_Use,
  KeywordLiteral_Enum,
  KeywordLiteral_Trust,
  KeywordLiteral_Union,
  KeywordLiteral_Return,
  KeywordLiteral_Static,
  KeywordLiteral_Struct,
  KeywordLiteral_Volatile,
  // Error
  KeywordLiteral_Unknown,
} KeywordLiteral_t;

typedef struct {
  size_t start_byte;
  size_t line;
  size_t start_column;
  size_t length;
  KeywordLiteral_t literal;
} Keyword_t;

inline size_t get_keyword_literal_length(KeywordLiteral_t literal) {
  switch (literal) {
    case KeywordLiteral_Fn:
    case KeywordLiteral_If:
      return 2;
    case KeywordLiteral_For:
    case KeywordLiteral_Pub:
    case KeywordLiteral_Mut:
    case KeywordLiteral_Use:
      return 3;
    case KeywordLiteral_Enum:
      return 4;
    case KeywordLiteral_Trust:
    case KeywordLiteral_Union:
      return 5;
    case KeywordLiteral_Return:
    case KeywordLiteral_Static:
    case KeywordLiteral_Struct:
      return 6;
    case KeywordLiteral_Volatile:
      return 8;
    default:
      return 0;
  }
}

inline char *get_keyword_literal_text(KeywordLiteral_t literal) {
  switch (literal) {
    case KeywordLiteral_Fn:       return "fn";
    case KeywordLiteral_If:       return "if";
    case KeywordLiteral_For:      return "for";
    case KeywordLiteral_Pub:      return "pub";
    case KeywordLiteral_Mut:      return "mut";
    case KeywordLiteral_Use:      return "use";
    case KeywordLiteral_Enum:     return "enum";
    case KeywordLiteral_Trust:    return "trust";
    case KeywordLiteral_Union:    return "union";
    case KeywordLiteral_Return:   return "return";
    case KeywordLiteral_Static:   return "static";
    case KeywordLiteral_Struct:   return "struct";
    case KeywordLiteral_Volatile: return "volatile";
    default:                      return NULL;
  }
}

#define compare(text, length_left, literal) \
  if ((length_left) >= get_keyword_literal_length((literal)) && !strncmp((text), get_keyword_literal_text((literal)), get_keyword_literal_length((literal)))) return (literal)

inline KeywordLiteral_t get_next_keyword_literal(const char* text, size_t length_left) {
  compare(text, length_left, KeywordLiteral_Fn);
  compare(text, length_left, KeywordLiteral_If);
  compare(text, length_left, KeywordLiteral_For);
  compare(text, length_left, KeywordLiteral_Pub);
  compare(text, length_left, KeywordLiteral_Mut);
  compare(text, length_left, KeywordLiteral_Use);
  compare(text, length_left, KeywordLiteral_Enum);
  compare(text, length_left, KeywordLiteral_Trust);
  compare(text, length_left, KeywordLiteral_Union);
  compare(text, length_left, KeywordLiteral_Return);
  compare(text, length_left, KeywordLiteral_Static);
  compare(text, length_left, KeywordLiteral_Struct);
  compare(text, length_left, KeywordLiteral_Volatile);
  return KeywordLiteral_Unknown;
}

#endif
