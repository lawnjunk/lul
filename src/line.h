#ifndef LUL_LINE
#define LUL_LINE

#include <ncurses.h>
#include "lul_types.h"

#define line_t struct line

struct line {
  char *buffer;
  int length;
  int next;
};

// default line_t width is 256ch
line_t *line_new(void);
char *line_to_string(line_t *line);
int line_write(line_t *line, char *input);
int line_insert(line_t *line, int offset, char *input);
int line_delete(line_t *line, int offset, int count);
int line_replace(line_t *line, int offset, char *input);

#endif