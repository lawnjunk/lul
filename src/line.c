#include "tools.h"
#include "line.h"
#include "flub.h"
#include "buffer.h"

/*
 * a line_t should allocate 256 (LINE_WITH) bytes when initialized
 * if its text chars reach LINE_WITH then it should double its size
 */

bool line_is_evil(line_t *line){
  dlog("line_is_evil");
  return flub_is_evil(line->err);
}

static line_t *line_trouble_on(line_t *line, char *msg){
  dlog("line_trouble_on");
  flub_trouble_on(line->err, msg);
  return line;
}

char *line_to_string(line_t *line){
  dlog("line_to_string");
  char *result = (char *) malloc(sizeof(char) * line->length) ;
  memcpy(result, line->buffer->data, line->length);
  result[line->length] = '\0';
  return result;
}

line_t *line_append_ch(line_t *line, char ch){
  dlog("line_append_ch");
  if(line_is_evil(line)) return line;
  if(line->length >= line->size) 
    return line_trouble_on(line, "not enough room");
  buffer_write_char(line->buffer, ch, line->length++);
  return line;
}

line_t *line_insert_ch(line_t *line, char ch, int offset){
  dlog("line_insert_ch");
  if(line_is_evil(line)) return line;
  if(line->length >= line->size) 
    return line_trouble_on(line, "not enough room");
  memmove(line->buffer + offset + 1, line->buffer + offset, line->length - offset + 1);
  buffer_write_char(line->buffer, ch, offset);
  line->length++;
  return line;
};

   /*o */
/*012345*/
/*hellox*/

line_t *line_delete_ch(line_t *line, int offset){
  dlog("line_delete_ch");
  if(line_is_evil(line)) return line;
  memmove(line->buffer + offset, line->buffer + offset + 1, line->length - offset + 1);
  line->length--;
  return line;
}

//   2  3
//  123456
// "HELLO"
//   o  c
//   

line_t *line_birth(char *text){
  dlog("line_birth");
  line_t *result = (line_t *) malloc(sizeof(line_t));  
  result->buffer = buffer_birth(LINE_WITH);
  buffer_write_string(result->buffer, text, 0);
  result->length = strlen(text);
  result->err = flub_birth("generic flub error");
  result->size = LINE_WITH;
  return result;
}

line_t *line_nuke(line_t *line){
  dlog("line_nuke");
  buffer_nuke(line->buffer);
  flub_nuke(line->err);
  free(line);
  line = NULL;
  return line;
}
