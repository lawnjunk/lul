#ifndef LUL_LINE
#define LUL_LINE
#include "tools.h"
#include "buffer.h"
#include "flub.h"

#define LINE_WITH 1000

#define line_t struct line
struct line {
  buffer_t *buffer;
  flub_t *err; 
  unsigned int length; // length of string in buffer
  unsigned int size ;  // amount of bytes allocated for buffer
};

// line create and destroy
line_t *line_create(char *text);
line_t *line_free(line_t *line);
line_t *line_trouble_on(line_t *line, char *msg);

// line operations
bool line_is_evil(line_t *line);
char *line_to_string(line_t *line);
char line_read_char(line_t *line, unsigned int offset);
line_t * line_append_char(line_t *line, char ch);
line_t * line_delete_char(line_t *line, unsigned int offset);
line_t * line_insert_char(line_t *line, char ch, unsigned int offset);
#endif
