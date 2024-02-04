#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stddef.h>
#define NOB_IMPLEMENTATION
#include "nob.h"
#include "token.h"
#include "utf8_definitions.h"

typedef struct {
    const bytes_t text_start;
    const bytes_t final_byte;
    bytes_t current_byte;
    size_t current_line_index;
    size_t current_column;
} LexerState_t;

inline codepoint_t next_codepoint(bytes_t* bytes) {
    codepoint_t codepoint;
    *bytes = utf8codepoint(*bytes, &codepoint);
    return codepoint;
}

inline codepoint_t peek_next_codepoint(const bytes_t bytes) {
    codepoint_t codepoint;
    utf8codepoint(bytes, &codepoint);
    return codepoint;
}

inline bool codepoint_is_new_line(codepoint_t codepoint, bytes_t bytes) {
    return codepoint == '\n' || (codepoint == '\r' && peek_next_codepoint(bytes) == '\n');
}

inline uint8_t newline_length() {
#ifdef _WIN32
    return 2;
#else
    return 1;
#endif
}

typedef enum {
    OptionVariant_None,
    OptionVariant_Some,
} OptionVariant_t;

typedef struct {
    OptionVariant_t variant;
    union {
        Token_t some;
    };
} OptionToken_t;

inline bool input_is_not_over(LexerState_t* state) {
    if (state->final_byte > state->text_start) {
        return state->current_byte < state->final_byte;
    }
    else if (state->final_byte < state->text_start) {
        return state->current_byte > state->final_byte;
    }
    else {
        return false;
    }
}

inline void skip_new_lines(LexerState_t* state, codepoint_t* codepoint) {
    while (input_is_not_over(state) && codepoint_is_new_line(*codepoint, state->current_byte)) {
        if (newline_length() > 1) {
            // skip the \r
            next_codepoint(&state->current_byte);
        }
        *codepoint = next_codepoint(&state->current_byte);
        state->current_line_index++;
        state->current_column = 1;
    }
}

inline void skip_space(LexerState_t* state, codepoint_t* codepoint) {
    while (input_is_not_over(state) && isspace(*codepoint)) {
        *codepoint = next_codepoint(&state->current_byte);
        state->current_column++;
    }
}

inline OptionToken_t next_token(LexerState_t* state) {
    codepoint_t codepoint = next_codepoint(&state->current_byte);
    state->current_column++;
    skip_new_lines(state, &codepoint);
    skip_space(state, &codepoint);
    if (!input_is_not_over(state)) return (OptionToken_t) { 0 };

    PunctuationLiteral_t punct = get_punctuation_literal_from_codepoint(codepoint);
    if (punct != PunctuationLiteral_Unknown) {
        return (OptionToken_t) {
            .variant = OptionVariant_Some,
                .some = {
                .type = TokenType_Punctuation,
                .punctuation = punct,
                .length = 1,
                .line = state->current_line_index,
                .start_column = state->current_column,
                .start_byte = state->current_byte - state->text_start,
            }
        };
    }

    const bytes_t start = state->current_byte - utf8codepointsize(codepoint);
    size_t start_column = state->current_column;
    while (input_is_not_over(state) && is_valid_identifier_codepoint(codepoint)) {
        codepoint = next_codepoint(&state->current_byte);
        state->current_column++;
    }

    if (start != state->current_byte) {
        state->current_byte -= utf8codepointsize(codepoint);
        return (OptionToken_t) {
            .variant = OptionVariant_Some,
                .some = {
                .type = TokenType_Identifier,
                .identifier = start,
                .length = state->current_byte - start,
                .line = state->current_line_index,
                .start_column = start_column,
                .start_byte = start - state->text_start,
            }
        };
    }

    return (OptionToken_t) { 0 };
}

inline Tokens_t lex(const Nob_String_Builder* sb) {
    LexerState_t lexer_state = {
      .text_start = sb->items,
      .current_byte = sb->items,
      .current_line_index = 1,
      .final_byte = sb->items + sb->count,
    };

    Tokens_t tokens = { 0 };
    while (input_is_not_over(&lexer_state)) {
        OptionToken_t maybe_token = next_token(&lexer_state);
        if (maybe_token.variant == OptionVariant_Some) {
            nob_da_append(&tokens, maybe_token.some);
        }
    }

    return tokens;
}

#endif
