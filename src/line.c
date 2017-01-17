#include <ncurses.h>
#include <gc.h>
#include "line.h"
#include "tools.h"
#include "lul_types.h"
#include <string.h>

#define LINE_WITH 256

char *line_to_string(line_t *line){
  return line->buffer;
}

int line_write(line_t *line, char *input){
  char *text = line->buffer;
  int i;
  int length = strlen(input);
  for(i=0; i<length && (line->next) < LINE_WITH; i++, line->next++){
    text[line->next] = (chtype) input[i];
  }
  return i;
}

int line_replace(line_t *line, int offset, char *input){
  /*chtype *text = line->buffer;*/
  return 0;
};

line_t *line_new(){
  line_t *result = (line_t *) GC_MALLOC(sizeof(line_t));  
  result->buffer = (char*) GC_MALLOC(sizeof(char) * LINE_WITH);
  result->length = LINE_WITH;
  result->next = 0;
  return result;
}
