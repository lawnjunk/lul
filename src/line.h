#ifndef LUL_LINE
#define LUL_LINE
#include "tools.h"
#include "buffer.h"
#include "lerr.h"

#define line_t struct line
struct line {
  buffer_t *buffer;
  lerr_t *err; 
  int length; // length of string in buffer
  int size ;  // amount of bytes allocated for buffer
};

// line create and destroy
line_t *line_create(char *text);
line_t *line_free(line_t *line);

// line operations
bool line_is_evil(line_t *line);
char *line_to_string(line_t *line);
char line_read_ch(line_t *line, int offset);
line_t * line_append_ch(line_t *line, char c);
line_t * line_delete_ch(line_t *line, int offset);
line_t * line_insert_ch(line_t *line, int offset, char c);

#endif
