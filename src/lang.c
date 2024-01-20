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

int32_t lexer_next_codepoint(Lexer_t *lexer) {
  int32_t codepoint = 0;
  lexer->current_char = utf8codepoint(lexer->current_char, &codepoint);
  lexer->current_column++;
  return codepoint;
}

void skip_whitespace(Lexer_t *lexer) {
  while (lexer->current_char < lexer->final_char && 
          isspace(*lexer->current_char)) {
    if (*lexer->current_char == '\n') {
      lexer->current_line_index++;
      lexer->current_line = lexer->current_char + 1;
    }

    lexer->current_char += utf8codepointcalcsize(lexer->current_char);
  }
}

void tokenize(Lexer_t *lexer)
{
  skip_whitespace(lexer);

  PunctuationLiteral_t punct = get_punctuation_literal_from_char(*lexer->current_char);
  while (lexer->current_char < lexer->final_char && punct != PunctuationLiteral_Unknown) {
    Token_t token = { 0 };
    token.type = TokenType_Punctuation;
    token.punctuation.start_byte = lexer->current_char - lexer->text_start;
    token.punctuation.line = lexer->current_line_index;
    token.punctuation.column = 1 + (lexer->current_char - lexer->current_line);
    token.punctuation.literal = punct;
    nob_da_append(&lexer->tokens, token);

    lexer->current_char += utf8codepointcalcsize(lexer->current_char);
    punct = get_punctuation_literal_from_char(*lexer->current_char);
  }

  if (lexer->tokens.count >= 3 &&
        lexer->tokens.items[lexer->tokens.count - 1].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 1].punctuation.literal == PunctuationLiteral_ForwardSlash &&
        lexer->tokens.items[lexer->tokens.count - 2].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 2].punctuation.literal == PunctuationLiteral_ForwardSlash &&
        lexer->tokens.items[lexer->tokens.count - 3].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 3].punctuation.literal == PunctuationLiteral_ForwardSlash) {
      lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };
      lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };
      /// ... Doc Comment ...
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

      for (;lexer->current_char < lexer->final_char && 
            *lexer->current_char != '\n';
            lexer->current_char++);
      lexer->tokens.items[lexer->tokens.count - 1].comment.length = lexer->current_char - lexer->tokens.items[lexer->tokens.count - 1].comment.text;
#ifdef _WIN32
      lexer->tokens.items[lexer->tokens.count - 1].comment.length--;
#endif
    } else if (lexer->tokens.count >= 3 &&
        lexer->tokens.items[lexer->tokens.count - 1].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 1].punctuation.literal == PunctuationLiteral_Asterisk &&
        lexer->tokens.items[lexer->tokens.count - 2].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 2].punctuation.literal == PunctuationLiteral_Asterisk &&
        lexer->tokens.items[lexer->tokens.count - 3].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 3].punctuation.literal == PunctuationLiteral_ForwardSlash) {
      lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };
      lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };
      // /** multiline doc comment */
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

      for(; lexer->current_char < lexer->final_char - 1 && 
            get_punctuation_literal_from_char(*lexer->current_char) != PunctuationLiteral_Asterisk && 
            get_punctuation_literal_from_char(*(lexer->current_char + 1)) != PunctuationLiteral_ForwardSlash; 
            lexer->current_char++) {
        if (*lexer->current_char == '\n') {
          lexer->current_line_index++;
          lexer->current_line = lexer->current_char;
        }
      }
      lexer->tokens.items[lexer->tokens.count - 1].comment.length = lexer->current_char - 1 - lexer->tokens.items[lexer->tokens.count - 1].comment.text;
      lexer->current_char++;
      lexer->current_char++;
    } else if (lexer->tokens.count >= 2 &&
        lexer->tokens.items[lexer->tokens.count - 1].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 1].punctuation.literal == PunctuationLiteral_ForwardSlash && 
        lexer->tokens.items[lexer->tokens.count - 2].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 2].punctuation.literal == PunctuationLiteral_ForwardSlash) {
      lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };
      lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };
      // ... Comment ... this won't be a token
      for (;lexer->current_char < lexer->final_char && 
            *lexer->current_char != '\n'; 
            lexer->current_char++);
    } else if (lexer->tokens.count >= 2 &&
        lexer->tokens.items[lexer->tokens.count - 1].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 1].punctuation.literal == PunctuationLiteral_Asterisk &&
        lexer->tokens.items[lexer->tokens.count - 2].type == TokenType_Punctuation &&
        lexer->tokens.items[lexer->tokens.count - 2].punctuation.literal == PunctuationLiteral_ForwardSlash) {
      lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };
      lexer->tokens.items[--lexer->tokens.count] = (Token_t){ 0 };
      // /* multiline comment */
      for(; lexer->current_char < lexer->final_char - 1 && 
            get_punctuation_literal_from_char(*lexer->current_char) != PunctuationLiteral_Asterisk && 
            get_punctuation_literal_from_char(*(lexer->current_char + 1)) != PunctuationLiteral_ForwardSlash; 
            lexer->current_char++) {
        if (*lexer->current_char == '\n') {
          lexer->current_line_index++;
          lexer->current_line = lexer->current_char;
        }
      }
      lexer->current_char++;
      lexer->current_char++;
    }

  KeywordLiteral_t keyword = get_next_keyword_literal(lexer->current_char, lexer->final_char - lexer->current_char);
  while (lexer->current_char < lexer->final_char && keyword != KeywordLiteral_Unknown) {
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

  int32_t code;
  utf8codepoint(lexer->current_char, &code);
  if (lexer->current_char < lexer->final_char && is_valid_identifier_char(code)) {
    Token_t token = { 0 };
    token.type = TokenType_Identifier;
    token.identifier.start_byte = lexer->current_char - lexer->text_start;
    token.identifier.start_column = 1 + (lexer->current_char - lexer->current_line);
    token.identifier.line = lexer->current_line_index;
    token.identifier.text = lexer->current_char;
    lexer->current_char = utf8codepoint(lexer->current_char, &code);
    while (lexer->current_char < lexer->final_char && is_valid_identifier_char(code)) {
      lexer->current_char = utf8codepoint(lexer->current_char, &code);
    }
    lexer->current_char--;
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
    Nob_String_View sv = {0};
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
