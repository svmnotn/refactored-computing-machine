#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define NOB_IMPLEMENTATION
#include "nob.h"
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

int32_t lexer_next_codepoint(Lexer_t* lexer) {
  int32_t codepoint = 0;
  lexer->current_char = utf8ncodepoint(
    lexer->current_char,
    lexer->final_char - lexer->current_char,
    &codepoint);
  lexer->current_column++;
  return codepoint;
}

int32_t lexer_peek_next_codepoint(Lexer_t* lexer) {
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

void lexer_increment_line(Lexer_t* lexer) {
  lexer->current_line_index++;
  lexer->current_column = 0;
  lexer->current_line = lexer->current_char + 1;
}

void skip_whitespace(Lexer_t* lexer, int32_t* codepoint) {
  while (*codepoint != 0 && isspace(*codepoint)) {
    if (*codepoint == '\n') lexer_increment_line(lexer);
    *codepoint = lexer_next_codepoint(lexer);
  }
}

void process_punctuation(Lexer_t* lexer, int32_t* codepoint) {
  PunctuationLiteral_t punct = get_punctuation_literal_from_char(codepoint);
  while (*codepoint != 0 && punct != PunctuationLiteral_Unknown) {
    Token_t token = { 0 };
    token.type = TokenType_Punctuation;
    token.punctuation.start_byte = lexer->current_char - lexer->text_start;
    token.punctuation.line = lexer->current_line_index;
    token.punctuation.column = 1 + (lexer->current_char - lexer->current_line);
    token.punctuation.literal = punct;
    nob_da_append(&lexer->tokens, token);

    *codepoint = lexer_next_codepoint(lexer);
    punct = get_punctuation_literal_from_char(codepoint);
  }
}

bool token_matches(Token_t a, Token_t b) {
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

bool lexer_token_at_index_matches(Lexer_t* lexer, size_t index, Token_t needle) {
  if (lexer->tokens.count < index) return false;
  Token_t haystack = lexer->tokens.items[index];
  return token_matches(needle, haystack);
}

bool lexer_rtoken_at_index_matches(Lexer_t* lexer, size_t reversedIndex, Token_t needle) {
  if (lexer->tokens.count < reversedIndex) return false;
  size_t index = lexer->tokens.count - 1 - reversedIndex;
  Token_t haystack = lexer->tokens.items[index];
  return token_matches(needle, haystack);
}

bool is_line_doc_comment(Lexer_t* lexer) {
  if (lexer->tokens.count < 3) return false;

  return lexer_rtoken_at_index_matches(
    lexer,
    0,
    (Token_t) {
    .type = TokenType_Punctuation,
      .punctuation = {
        .literal = PunctuationLiteral_ForwardSlash
    }
  }) &&
    lexer_rtoken_at_index_matches(
      lexer,
      1,
      (Token_t) {
      .type = TokenType_Punctuation,
        .punctuation = {
          .literal = PunctuationLiteral_ForwardSlash
      }
    }) &&
      lexer_rtoken_at_index_matches(
        lexer,
        2,
        (Token_t) {
        .type = TokenType_Punctuation,
          .punctuation = {
            .literal = PunctuationLiteral_ForwardSlash
        }
      });
}

bool is_multiline_doc_comment(Lexer_t* lexer) {
  if (lexer->tokens.count < 3) return false;

  return lexer_rtoken_at_index_matches(
    lexer,
    0,
    (Token_t) {
    .type = TokenType_Punctuation,
      .punctuation = {
        .literal = PunctuationLiteral_Asterisk
    }
  }) &&
    lexer_rtoken_at_index_matches(
      lexer,
      1,
      (Token_t) {
      .type = TokenType_Punctuation,
        .punctuation = {
          .literal = PunctuationLiteral_Asterisk
      }
    }) &&
      lexer_rtoken_at_index_matches(
        lexer,
        2,
        (Token_t) {
        .type = TokenType_Punctuation,
          .punctuation = {
            .literal = PunctuationLiteral_ForwardSlash
        }
      });
}

bool is_line_comment(Lexer_t* lexer) {
  if (lexer->tokens.count < 2) return false;

  return lexer_rtoken_at_index_matches(
    lexer,
    0,
    (Token_t) {
    .type = TokenType_Punctuation,
      .punctuation = {
        .literal = PunctuationLiteral_ForwardSlash
    }
  }) &&
    lexer_rtoken_at_index_matches(
      lexer,
      1,
      (Token_t) {
      .type = TokenType_Punctuation,
        .punctuation = {
          .literal = PunctuationLiteral_ForwardSlash
      }
    });
}

bool is_multiline_comment(Lexer_t* lexer) {
  if (lexer->tokens.count < 2) return false;

  return lexer_rtoken_at_index_matches(
    lexer,
    0,
    (Token_t) {
    .type = TokenType_Punctuation,
      .punctuation = {
        .literal = PunctuationLiteral_Asterisk
    }
  }) &&
    lexer_rtoken_at_index_matches(
      lexer,
      1,
      (Token_t) {
      .type = TokenType_Punctuation,
        .punctuation = {
          .literal = PunctuationLiteral_ForwardSlash
      }
    });
}

void process_comments(Lexer_t* lexer, int32_t* codepoint) {
  if (lexer->tokens.count < 2) return;
  bool line_doc_comment = is_line_doc_comment(lexer);
  bool doc_comment = is_multiline_doc_comment(lexer);
  bool line_comment = is_line_comment(lexer);
  bool comment = is_multiline_comment(lexer);
  bool is_doc_comment = line_doc_comment || doc_comment;
  bool is_comment = is_doc_comment || line_comment || comment;

  if (!is_comment) return;

  lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };
  lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };

  if (!is_doc_comment) {
    int32_t next_codepoint;
#ifdef _WIN32
    while (line_comment && *codepoint != 0 && *codepoint != '\r' && next_codepoint != '\n')
#else
    while (line_comment && *codepoint != 0 && *codepoint != '\n')
#endif
    {
      *codepoint = lexer_next_codepoint(lexer);
#ifdef _WIN32
      next_codepoint = lexer_peek_next_codepoint(lexer);
#endif
    }

    while (comment &&
      *codepoint != 0 &&
      get_punctuation_literal_from_char(*codepoint) != PunctuationLiteral_Asterisk &&
      get_punctuation_literal_from_char(next_codepoint) != PunctuationLiteral_ForwardSlash) {
      *codepoint = lexer_next_codepoint(lexer);
      next_codepoint = lexer_peek_next_codepoint(lexer);
    }

    return;
  }

  lexer->tokens.items[lexer->tokens.count - 1].type = TokenType_Comment;
  size_t start_byte = lexer->tokens.items[lexer->tokens.count - 1].punctuation.start_byte + 3;
  size_t line = lexer->tokens.items[lexer->tokens.count - 1].punctuation.line;
  size_t column = lexer->tokens.items[lexer->tokens.count - 1].punctuation.column + 3;
  lexer->tokens.items[lexer->tokens.count - 1].comment.start_byte = start_byte;
  lexer->tokens.items[lexer->tokens.count - 1].comment.line = line;
  lexer->tokens.items[lexer->tokens.count - 1].comment.start_column = 1 + column;
  lexer->tokens.items[lexer->tokens.count - 1].comment.text = lexer->text_start + start_byte;

  if (isspace(*lexer->tokens.items[lexer->tokens.count - 1].comment.text)) {
    lexer->tokens.items[lexer->tokens.count - 1].comment.start_byte++;
    lexer->tokens.items[lexer->tokens.count - 1].comment.text++;
  }

  int32_t next_codepoint;
#ifdef _WIN32
  while (line_doc_comment && *codepoint != 0 && *codepoint != '\r' && next_codepoint != '\n')
#else
  while (line_doc_comment && *codepoint != 0 && *codepoint != '\n')
#endif
  {
    *codepoint = lexer_next_codepoint(lexer);
#ifdef _WIN32
    next_codepoint = lexer_peek_next_codepoint(lexer);
#endif
  }

  while (doc_comment &&
    *codepoint != 0 &&
    get_punctuation_literal_from_char(*codepoint) != PunctuationLiteral_Asterisk &&
    get_punctuation_literal_from_char(next_codepoint) != PunctuationLiteral_ForwardSlash) {
    *codepoint = lexer_next_codepoint(lexer);
    next_codepoint = lexer_peek_next_codepoint(lexer);
  }

  lexer->tokens.items[lexer->tokens.count - 1].comment.length = lexer->current_char - lexer->tokens.items[lexer->tokens.count - 1].comment.text;

  if (doc_comment) {
    *codepoint = lexer_next_codepoint(lexer);
    *codepoint = lexer_next_codepoint(lexer);
  }
}

void process_keywords(Lexer_t* lexer) {
  KeywordLiteral_t keyword = get_next_keyword_literal(lexer->current_char, lexer->final_char - lexer->current_char);
  while (lexer_peek_next_codepoint(lexer) != 0 && keyword != KeywordLiteral_Unknown) {
    Token_t token = { 0 };
    token.type = TokenType_Keyword;
    token.keyword.start_byte = lexer->current_char - lexer->text_start;
    token.keyword.line = lexer->current_line_index;
    token.keyword.start_column = 1 + (lexer->current_char - lexer->current_line);
    token.keyword.literal = keyword;
    token.keyword.length = get_keyword_literal_length(keyword);
    nob_da_append(&lexer->tokens, token);
    lexer->current_char += token.keyword.length;
    keyword = get_next_keyword_literal(lexer->current_char, lexer->final_char - lexer->current_char);
  }
}

void tokenize(Lexer_t* lexer)
{
  int32_t codepoint = lexer_next_codepoint(lexer);
  if (codepoint == 0) return;

  skip_whitespace(lexer, &codepoint);
  if (codepoint == 0) return;

  process_punctuation(lexer, &codepoint);
  if (codepoint == 0) return;

  process_comments(lexer, &codepoint);
  if (codepoint == 0) return;

  process_keywords(lexer);
  codepoint = lexer_next_codepoint(lexer);
  if (codepoint == 0) return;

  if (is_valid_identifier_char(codepoint)) {
    Token_t token = { 0 };
    token.type = TokenType_Identifier;
    token.identifier.start_byte = lexer->current_char - lexer->text_start;
    token.identifier.start_column = 1 + (lexer->current_char - lexer->current_line);
    token.identifier.line = lexer->current_line_index;
    token.identifier.text = lexer->current_char;
    codepoint = lexer_next_codepoint(lexer);
    while (codepoint != 0 && is_valid_identifier_char(codepoint)) codepoint = lexer_next_codepoint(lexer);
    lexer->current_char -= utf8codepointsize(codepoint);
    token.identifier.length = lexer->current_char - token.identifier.text;
    nob_da_append(&lexer->tokens, token);
  }
}

int main(int argc, char** argv)
{
  const char* program = nob_shift_args(&argc, &argv);
  if (argc == 0) {
    printf("Usage: %s <file>", program);
    return 1;
  }
  const char* file = nob_shift_args(&argc, &argv);

  Nob_String_Builder sb = { 0 };
  if (!nob_read_entire_file(file, &sb)) return 1;
  nob_log(NOB_INFO, "Lexing %s", file);

  Lexer_t lexer = {
    .text_start = sb.items,
    .current_char = sb.items,
    .current_line = sb.items,
    .current_line_index = 1,
    .final_char = sb.items + sb.count,
    .tokens = { 0 }
  };

  while (lexer.current_char < lexer.final_char) {
    tokenize(&lexer);
  }

  nob_log(NOB_INFO, "Lexed [");
  for (size_t i = 0; i < lexer.tokens.count; i++) {
    Nob_String_View sv = { 0 };
    switch (lexer.tokens.items[i].type) {
    case TokenType_Comment:
      sv.count = lexer.tokens.items[i].comment.length;
      sv.data = lexer.tokens.items[i].comment.text;
      nob_log(NOB_INFO, "\tComment     { text: '"SV_Fmt"', length: %zu, line: %zu, column: %zu, byte: %zu },",
        SV_Arg(sv), lexer.tokens.items[i].comment.length, lexer.tokens.items[i].comment.line, lexer.tokens.items[i].comment.start_column, lexer.tokens.items[i].comment.start_byte);
      break;
    case TokenType_Identifier:
      sv.count = lexer.tokens.items[i].identifier.length;
      sv.data = lexer.tokens.items[i].identifier.text;
      nob_log(NOB_INFO, "\tIdentifier  { text: '"SV_Fmt"', length: %zu, line: %zu, column: %zu, byte: %zu },",
        SV_Arg(sv), lexer.tokens.items[i].identifier.length, lexer.tokens.items[i].identifier.line, lexer.tokens.items[i].identifier.start_column, lexer.tokens.items[i].identifier.start_byte);
      break;
    case TokenType_Keyword:
      nob_log(NOB_INFO, "\tKeyword     { literal: '%s', length: %zu, line: %zu, column: %zu, byte: %zu },",
        get_keyword_literal_text(lexer.tokens.items[i].keyword.literal), lexer.tokens.items[i].keyword.length, lexer.tokens.items[i].keyword.line, lexer.tokens.items[i].keyword.start_column, lexer.tokens.items[i].keyword.start_byte);
      break;
    case TokenType_Punctuation:
      nob_log(NOB_INFO, "\tPunctuation { literal: '%c', line: %zu, column: %zu, byte: %zu },",
        get_char_from_punctuation_literal(lexer.tokens.items[i].punctuation.literal), lexer.tokens.items[i].punctuation.line, lexer.tokens.items[i].punctuation.column, lexer.tokens.items[i].punctuation.start_byte);
      break;
    }
  }
  nob_log(NOB_INFO, "]");

  return 0;
}
