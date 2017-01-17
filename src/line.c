#include <ncurses.h>
#include <gc.h>
#include "line.h"
#include "tools.h"
#include "lul_types.h"
#include <string.h>

#define LINE_WITH 256

int chtype_length(chtype *input){
  int i;
  chtype c;
  for(i=0; (c=input[i]) != '\0'; i++);
  return i;
}

chtype *line_to_string(line_t *self){
  return self->buffer;
}

int line_write(line_t *self, char *input){
  chtype *text = self->buffer;
  int i;
  int length = strlen(input);
  for(i=0 i<length && (self->next) < LINE_WITH; i++, self->next++){
    text[self->next] = (chtype) input[i];
  }
  return i;
}

bool line_replace(line_t *self, int offset, char *input){
  chtype *text = self->buffer;
    
};

line_t new_line(){
  line_t *result = (line_t *) GC_MALLOC(sizeof(line_t));  
  result->buffer = (chtype *) GC_MALLOC(sizeof(chtype) * LINE_WITH);
  result->length = LINE_WITH;
  result->next = 0;
  result->to_string = &line_to_string;
  
}
