#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stddef.h>
#include "token.h"
#include "utf8.h"

typedef struct
{
  Tokens_t tokens;
  const char* const text_start;
  const char* const final_char;
  size_t current_line_index;
  size_t current_column;
  const char* current_line;
  const char* current_char;
} Lexer_t;

inline int32_t lexer_next_codepoint(Lexer_t* lexer) {
  int32_t codepoint = 0;
  lexer->current_char = utf8ncodepoint(
    lexer->current_char,
    lexer->final_char - lexer->current_char,
    &codepoint);
  lexer->current_column++;
  return codepoint;
}

inline void lexer_skip_n_codepoints(Lexer_t* lexer, size_t n) {
  for (size_t i = 0; i < n; i++) {
    lexer_next_codepoint(lexer);
  }
}

inline int32_t lexer_peek_next_codepoint(Lexer_t* lexer) {
  int32_t codepoint = 0;
  char* next = utf8ncodepoint(
    lexer->current_char,
    lexer->final_char - lexer->current_char,
    &codepoint);
  utf8ncodepoint(
    next,
    lexer->final_char - next,
    &codepoint);
  return codepoint;
}

inline void lexer_increment_line(Lexer_t* lexer) {
  lexer->current_line_index++;
  lexer->current_column = 0;
  lexer->current_line = lexer->current_char + 1;
}

inline bool lexer_token_at_index_matches(Lexer_t* lexer, size_t index, Token_t needle) {
  if (lexer->tokens.count < index) return false;
  Token_t haystack = lexer->tokens.items[index];
  return token_matches(needle, haystack);
}

inline bool lexer_rtoken_at_index_matches(Lexer_t* lexer, size_t reversedIndex, Token_t needle) {
  if (lexer->tokens.count < reversedIndex) return false;
  size_t index = lexer->tokens.count - 1 - reversedIndex;
  Token_t haystack = lexer->tokens.items[index];
  return token_matches(needle, haystack);
}

#endif
