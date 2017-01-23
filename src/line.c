#include "tools.h"
#include "line.h"
#include "buffer.h"

#define LINE_WITH 256

/*
 * a line_t should allocate 256 (LINE_WITH) bytes when initialized
 * if its text chars reach LINE_WITH then it should double its size
 */

char *line_to_string(line_t *line){
  char *result = (char *) malloc(sizeof(char) * (line->length + 1)) ;
  for(int i=0; i<line->length; i++){
    result[i] = buffer_read_char(line->buffer, i);
  }
  result[i] = '\0'
  return result;
}

line_t *line_append_ch(line_t *line, char c){
  if(line->length == line->size) {
    err_trouble_on(line->err, "not enough room");
    return line;
  }
  buffer_write_char(line->buffer, c, line->length++);
  return line;
}

line_t *line_insert_ch(line_t *line, char ch, int offset){

};


//   2  3
//  123456
// "HELLO"
//   o  c
//   

line_t *line_create(char *text){
  line_t *result = (line_t *) malloc(sizeof(line_t));  
  result->buffer = buffer_create(LINE_WITH);
  int i=0;
  while(text[i] != '\0'){
    buffer_write_char(result->buffer, text[i], i);
    i++;
  }
  result->length = strlen(i);
  result->size = LINE_WITH;
  return result;
}
