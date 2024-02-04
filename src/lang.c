#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#define NOB_IMPLEMENTATION

/**
 * TODO: Switch to the following,
 *
 * *done* Lex: u8 -> utf8 -> Identifier|Punctuation
 * Parse: Identifier|Punctuation -> AST? | Maybe some other array before that?
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "punctuation.h"
#include "token.h"

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
  Tokens_t tokens = lex(&sb);

  nob_log(NOB_INFO, "Lexed [");
  for (size_t i = 0; i < tokens.count; i++) {
    Nob_String_View sv = { 0 };
    switch (tokens.items[i].type) {
    case TokenType_Identifier:
      sv.count = tokens.items[i].length;
      sv.data = tokens.items[i].identifier;
      nob_log(NOB_INFO, "\tIdentifier  { text: '"SV_Fmt"', length: %zu, line: %zu, column: %zu, byte: %zu },",
        SV_Arg(sv), tokens.items[i].length, tokens.items[i].line, tokens.items[i].start_column, tokens.items[i].start_byte);
      break;
    case TokenType_Punctuation:
      nob_log(NOB_INFO, "\tPunctuation { literal: '%c', line: %zu, column: %zu, byte: %zu },",
        get_codepoint_from_punctuation_literal(tokens.items[i].punctuation), tokens.items[i].line, tokens.items[i].start_column, tokens.items[i].start_byte);
      break;
    }
  }
  nob_log(NOB_INFO, "]");

  return 0;
}
