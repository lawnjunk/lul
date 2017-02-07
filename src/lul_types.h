#ifndef LUL_TYPES
#define LUL_TYPES
#include "tools.h"

#define flub_t struct flub
struct flub {
  char *msg;
  bool trouble;
};

#define buffer_t struct buffer
struct buffer {
  uint8_t *data;
  size_t length;
  flub_t err;
  bool is_slice; // necessary for buffer_free
};

#define line_t struct line
struct line {
  buffer_t *buffer;
  flub_t err; 
  unsigned int length; // length of string in buffer
  unsigned int size ;  // amount of bytes allocated for buffer
};

#define doc_t struct doc
struct doc {
  line_t **lines;
  flub_t err;
  unsigned int length; // number of lines
  unsigned int size;   // amount allocated
};

#define cursor_t struct cursor
struct cursor {
  unsigned int x;
  unsigned int y;
  flub_t err;
  doc_t *doc;
};
#endif
