#include "tools.h"

/*
 * a line_t should allocate 256 (LINE_WITH) bytes when initialized
 * if its text chars reach LINE_WITH then it should double its size
 */

bool line_is_evil(line_t *line){
  debug("line_is_evil");
  if(is_null(line)) return true;
  return flub_is_evil(line->err);
}

line_t *line_trouble_on(line_t *line, char *msg){
  debug("line_trouble_on");
  flub_trouble_on(line->err, msg);
  return line;
}

char *line_to_string(line_t *line){
  debug("line_to_string");
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
  if(offset > line->length){
    line_trouble_on(line, "out of bounds");
    return '\0';
  }
  return buffer_read_char(line->buffer, offset);
}

line_t *line_append_char(line_t *line, char ch){
  debug("line_append_ch");
  if(line_is_evil(line)) return line;
  if(line->length >= line->size - 1) 
    return line_trouble_on(line, "not enough room");
  buffer_write_char(line->buffer, ch, line->length++);
  return line;
}

line_t *line_insert_char(line_t *line, char ch, unsigned int offset){
  debug("line_insert_ch");
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
  debug("line_delete_char");
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
  debug("line_create");
  if(is_null(text)) text = "";
  line_t *result = (line_t *) malloc(sizeof(line_t));  
  result->buffer = buffer_create(LINE_WITH);
  buffer_write_string(result->buffer, text, 0);
  result->length = strlen(text);
  result->err = flub_create("generic flub error");
  result->size = LINE_WITH;
  return result;
}

line_t *line_free(line_t *line){
  debug("line_free");
  buffer_free(line->buffer);
  flub_free(line->err);
  free(line);
  line = NULL;
  return line;
}

line_t *line_from_cursor(cursor_t *cur, int offset){
  debug("line_from_cursor");
  // check for evil_ness
  if(cursor_is_evil(cur)) return NULL;

  unsigned int x = cur->x;
  unsigned int y =cur->y + offset;
  doc_t *doc = cur->doc;
  // make sure its in a valid location
  // is the line length valid?
  if(y > doc->length){
    cursor_trouble_on(cur, "not a valid line number");
    return NULL;
  }

  // get the line
  line_t *cur_line = (doc->lines)[y];
  // check if the line is evil
  if(line_is_evil(cur_line)){
    cursor_trouble_on(cur, "line was evil");
    return NULL;
  }
  // is the curor posion on the line valid
  if(x > cur_line->length){
    cursor_trouble_on(cur, "not a valid line index");
    return NULL;
  }

  return cur_line;
  // write the char
}

line_t *line_write_line(line_t *dest, line_t *src, unsigned int doffset, unsigned int soffset, unsigned int count){
  debug("line_write_line");
  if(line_is_evil(dest)) return dest;
  if(line_is_evil(src))
    return line_trouble_on(dest, "src was evil");
  if((doffset + count) > dest->size)
    return line_trouble_on(dest, "not enough room");
  if(count > src->length - 1)
    return line_trouble_on(dest, "count two large");
  buffer_t *slice = buffer_slice(src->buffer, soffset, src->length);
  buffer_write_buffer(dest->buffer, slice, doffset, 0, count);
  dest->length = doffset + slice->length;
  l_free(slice, buffer);
  return dest;
}
