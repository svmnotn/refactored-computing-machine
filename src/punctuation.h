#ifndef PUNCTUATION_H
#define PUNCTUATION_H

#include <stddef.h>

typedef enum {
  PunctuationLiteral_LeftBracket,
  PunctuationLiteral_RightBracket,
  PunctuationLiteral_LeftSquareBracket,
  PunctuationLiteral_RightSquareBracket,
  PunctuationLiteral_LeftParenthesis,
  PunctuationLiteral_RightParenthesis,
  PunctuationLiteral_BackwardSlash,
  PunctuationLiteral_ForwardSlash,
  PunctuationLiteral_Asterisk,
  PunctuationLiteral_Minus,
  PunctuationLiteral_Plus,
  PunctuationLiteral_Equal,
  PunctuationLiteral_Percent,
  PunctuationLiteral_Hashtag,
  PunctuationLiteral_Semicolon,
  PunctuationLiteral_Colon,
  PunctuationLiteral_Comma,
  PunctuationLiteral_Hat,
  PunctuationLiteral_Dot,
  PunctuationLiteral_Ampersand,
  PunctuationLiteral_LessThan,
  PunctuationLiteral_GreaterThan,
  PunctuationLiteral_QuestionMark,
  PunctuationLiteral_ExclamationMark,
  PunctuationLiteral_Tilde,
  PunctuationLiteral_SingleQuote,
  PunctuationLiteral_DoubleQuote,
  PunctuationLiteral_BackTick,
  // Error
  PunctuationLiteral_Unknown,
} PunctuationLiteral_t;

typedef struct {
  size_t start_byte;
  size_t line;
  size_t column;
  PunctuationLiteral_t literal;
} Punctuation_t;

static inline PunctuationLiteral_t get_punctuation_literal_from_char(char c) {
  switch (c) {
  case '{':  return PunctuationLiteral_LeftBracket;
  case '}':  return PunctuationLiteral_RightBracket;
  case '[':  return PunctuationLiteral_LeftSquareBracket;
  case ']':  return PunctuationLiteral_RightSquareBracket;
  case '(':  return PunctuationLiteral_LeftParenthesis;
  case ')':  return PunctuationLiteral_RightParenthesis;
  case '\\': return PunctuationLiteral_BackwardSlash;
  case '/':  return PunctuationLiteral_ForwardSlash;
  case '*':  return PunctuationLiteral_Asterisk;
  case '-':  return PunctuationLiteral_Minus;
  case '+':  return PunctuationLiteral_Plus;
  case '=':  return PunctuationLiteral_Equal;
  case '%':  return PunctuationLiteral_Percent;
  case '#':  return PunctuationLiteral_Hashtag;
  case ';':  return PunctuationLiteral_Semicolon;
  case ':':  return PunctuationLiteral_Colon;
  case ',':  return PunctuationLiteral_Comma;
  case '^':  return PunctuationLiteral_Hat;
  case '.':  return PunctuationLiteral_Dot;
  case '&':  return PunctuationLiteral_Ampersand;
  case '<':  return PunctuationLiteral_LessThan;
  case '>':  return PunctuationLiteral_GreaterThan;
  case '?':  return PunctuationLiteral_QuestionMark;
  case '!':  return PunctuationLiteral_ExclamationMark;
  case '~':  return PunctuationLiteral_Tilde;
  case '\'': return PunctuationLiteral_SingleQuote;
  case '"':  return PunctuationLiteral_DoubleQuote;
  case '`':  return PunctuationLiteral_BackTick;
  default:   return PunctuationLiteral_Unknown;
  }
}

static inline char get_char_from_punctuation_literal(PunctuationLiteral_t literal) {
  switch (literal) {
  case PunctuationLiteral_LeftBracket:        return '{';
  case PunctuationLiteral_RightBracket:       return '}';
  case PunctuationLiteral_LeftSquareBracket:  return '[';
  case PunctuationLiteral_RightSquareBracket: return ']';
  case PunctuationLiteral_LeftParenthesis:    return '(';
  case PunctuationLiteral_RightParenthesis:   return ')';
  case PunctuationLiteral_BackwardSlash:      return '\\';
  case PunctuationLiteral_ForwardSlash:       return '/';
  case PunctuationLiteral_Asterisk:           return '*';
  case PunctuationLiteral_Minus:              return '-';
  case PunctuationLiteral_Plus:               return '+';
  case PunctuationLiteral_Equal:              return '=';
  case PunctuationLiteral_Percent:            return '%';
  case PunctuationLiteral_Hashtag:            return '#';
  case PunctuationLiteral_Semicolon:          return ';';
  case PunctuationLiteral_Colon:              return ':';
  case PunctuationLiteral_Comma:              return ',';
  case PunctuationLiteral_Hat:                return '^';
  case PunctuationLiteral_Dot:                return '.';
  case PunctuationLiteral_Ampersand:          return '&';
  case PunctuationLiteral_LessThan:           return '<';
  case PunctuationLiteral_GreaterThan:        return '>';
  case PunctuationLiteral_QuestionMark:       return '?';
  case PunctuationLiteral_ExclamationMark:    return '!';
  case PunctuationLiteral_Tilde:              return '~';
  case PunctuationLiteral_SingleQuote:        return '\'';
  case PunctuationLiteral_DoubleQuote:        return '"';
  case PunctuationLiteral_BackTick:           return '`';
  default:                                    return 0;
  }
}

#endif
