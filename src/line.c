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
  if(is_null(line)) return true;
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

  if(line->length == 0){
    result[0] = '\0';
    return result;
  }

  memcpy(result, line->buffer->data, line->length);
  result[line->length] = '\0';
  return result;
}

char line_read_char(line_t *line, unsigned int offset){
  return buffer_read_char(line->buffer, offset);
}

line_t *line_append_char(line_t *line, char ch){
  dlog("line_append_ch");
  if(line_is_evil(line)) return line;
  if(line->length >= line->size - 1) 
    return line_trouble_on(line, "not enough room");
  buffer_write_char(line->buffer, ch, line->length++);
  return line;
}

line_t *line_insert_char(line_t *line, char ch, unsigned int offset){
  dlog("line_insert_ch");
  if(line_is_evil(line)) return line;
  if(line->length >= line->size) 
    return line_trouble_on(line, "not enough room");
  if(offset > line->length)
    return line_trouble_on(line, "out of bounds");
  memmove(line->buffer->data + offset + 1, line->buffer->data + offset, line->length - offset + 1);
  buffer_write_char(line->buffer, ch, offset);
  line->length++;
  return line;
};

   /*o */
/*012345*/
/*hellox*/

line_t *line_delete_char(line_t *line, unsigned int offset){
  dlog("line_delete_char");
  if(line_is_evil(line)) return line;
  if(line->length == 0)
    return line_trouble_on(line, "can not delete nothing");
  if(offset > line->length - 1)
    return line_trouble_on(line, "out of bounds");
  memmove(line->buffer->data + offset, line->buffer->data + offset + 1, line->length - offset + 1);

  if (line->length > 0)
    line->length--;
  return line;
}

//   2  3
//  123456
// "HELLO"
//   o  c
//   

line_t *line_create(char *text){
  dlog("line_create");
  line_t *result = (line_t *) malloc(sizeof(line_t));  
  result->buffer = buffer_create(LINE_WITH);
  buffer_write_string(result->buffer, text, 0);
  result->length = strlen(text);
  result->err = flub_create("generic flub error");
  result->size = LINE_WITH;
  return result;
}

line_t *line_free(line_t *line){
  dlog("line_free");
  buffer_free(line->buffer);
  flub_free(line->err);
  free(line);
  line = NULL;
  return line;
}
