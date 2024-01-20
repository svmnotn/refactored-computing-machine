#ifndef COMMENT_H
#define COMMENT_H

#include <stddef.h>

typedef struct {
  size_t start_byte;
  size_t line;
  size_t start_column;
  size_t length;
  const char* text;
} Comment_t;

bool get_next_comment(Comment_t* comment) {
}

#endif