#ifndef LUL_CURSOR
#define LUL_CURSOR
#include "tools.h"
#include "doc.h"
#include "line.h"
#include "flub.h"

typedef struct cursor {
  unsigned int x;
  unsigned int y;
  flub_t *err;
  doc_t *doc;
} cursor_t;

cursor_t *cursor_create(doc_t *doc, unsigned int x, unsigned int y);
cursor_t *cursor_free(cursor_t * cur);
cursor_t *cursor_trouble_on(cursor_t * cur, char *msg);
bool cursor_is_evil(cursor_t *cur);

cursor_t *cursor_write_char(cursor_t *cur, char ch);

#endif 
