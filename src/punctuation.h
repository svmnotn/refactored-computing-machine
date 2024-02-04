#ifndef PUNCTUATION_H
#define PUNCTUATION_H

#include "utf8_definitions.h"

#define PUNCTUATION_TABLE(ENTRY) \
  ENTRY(LeftBracket,        '{') \
  ENTRY(RightBracket,       '}') \
  ENTRY(LeftSquareBracket,  '[') \
  ENTRY(RightSquareBracket, ']') \
  ENTRY(LeftParenthesis,    '(') \
  ENTRY(RightParenthesis,   ')') \
  ENTRY(ForwardSlash,       '/') \
  ENTRY(Asterisk,           '*') \
  ENTRY(Minus,              '-') \
  ENTRY(Plus,               '+') \
  ENTRY(Equal,              '=') \
  ENTRY(Percent,            '%') \
  ENTRY(Hashtag,            '#') \
  ENTRY(Semicolon,          ';') \
  ENTRY(Colon,              ':') \
  ENTRY(Comma,              ',') \
  ENTRY(Hat,                '^') \
  ENTRY(Dot,                '.') \
  ENTRY(Ampersand,          '&') \
  ENTRY(LessThan,           '<') \
  ENTRY(GreaterThan,        '>') \
  ENTRY(QuestionMark,       '?') \
  ENTRY(ExclamationMark,    '!') \
  ENTRY(Tilde,              '~') \
  ENTRY(DoubleQuote,        '"') \
  ENTRY(BackTick,           '`') \
  ENTRY(At,                 '@') \
  ENTRY(Dollar,             '$') \
  ENTRY(SingleQuote,        '\'') \
  ENTRY(BackwardSlash,      '\\') \


typedef enum {
#define EXPAND_AS_ENUM(Name, Literal) \
  PunctuationLiteral_##Name,

  PUNCTUATION_TABLE(EXPAND_AS_ENUM)
  // Error
  PunctuationLiteral_Unknown,
} PunctuationLiteral_t;


inline PunctuationLiteral_t get_punctuation_literal_from_codepoint(codepoint_t c) {
#define EXPAND_AS_LITERAL_CASE_RETURNS_NAME(Name, Literal) \
  case Literal: return PunctuationLiteral_##Name;

  switch (c) {
  PUNCTUATION_TABLE(EXPAND_AS_LITERAL_CASE_RETURNS_NAME)
  default: return PunctuationLiteral_Unknown;
  }
}

inline codepoint_t get_codepoint_from_punctuation_literal(PunctuationLiteral_t literal) {
#define EXPAND_AS_NAME_CASE_RETURNS_LITERAL(Name, Literal) \
  case PunctuationLiteral_##Name: return Literal;

  switch (literal) {
  PUNCTUATION_TABLE(EXPAND_AS_NAME_CASE_RETURNS_LITERAL)
  default: return 0;
  }
}

#endif
