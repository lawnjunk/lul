#ifndef LUL_LINE
#define LUL_LINE

#include <ncurses.h>
#include "lul_types.h"

#define line_t struct line

#undef this
#define this line_t *self
struct line {
  chtype *buffer;
  int length;
  int next;
  chtype (*to_string)(this);
  bool (*write)(this, int offset, char *input);
  bool (*insert)(this, int offset, char *input);
  bool (*delete)(this, int offset, int count);
  bool (*replace)(this, int offset, char *input);
};
#undef this

// default line_t width is 256ch
line_t *new_line(void)

#endif
