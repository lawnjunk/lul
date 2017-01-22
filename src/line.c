#include "line.h"
#include "tools.h"

#define LINE_WITH 256

/*
 * a line_t should allocate 256 (LINE_WITH) bytes when initialized
 * if its text chars reach LINE_WITH then it should double its size
 */

char *line_to_string(line_t *line){
  return line->buffer;
}

line_t *line_add_ch(line_t *line, char c){
  line->buffer[line->length++] = c;
  return line;
}

line_t *line_write(line_t *line, char *input){
  char *text = line->buffer;
  strcat(text, input);
  line->length = strlen(text);
  return line;
}

line_t *line_insert(line_t *line, int offset, char *input){
  char *result = (char *) malloc(sizeof(char) * LINE_WITH);
  strncpy(result, line->buffer, offset);
  strcat(result, input);
  strcat(result, (line->buffer) + offset);
  free(line->buffer);
  line->buffer = result;
  line->length = strlen(line->buffer);
  return line;
};


//   2  3
//  123456
// "HELLO"
//   o  c
//   

line_t *line_remove(line_t *line, int offset, int count){
  char *result = (char *) malloc(sizeof(char) * LINE_WITH);
  if (offset > line->length) offset = line->length; 
  strncpy(result, line->buffer, offset);  // copy upto the offset
  int end = offset + count;
  if (end < line->size)
    strcat(result, line->buffer + end); // copy from end on 
  free(line->buffer); // free the old line
  line->buffer = result;
  line->length = strlen(line->buffer);
  return line;
}

line_t *line_replace(line_t *line, int offset, char *input){
  char *result = (char *) malloc(sizeof(char) * LINE_WITH);
  int input_lenth = strlen(input);
  strncpy(result, line->buffer, offset);
  strcat(result, input);
  strcat(result, (line->buffer) + input_lenth + offset);
  line->buffer = result;
  line->length = strlen(line->buffer);
  return line;
};

line_t *line_new(){
  line_t *result = (line_t *) malloc(sizeof(line_t));  
  result->buffer = (char*) malloc(sizeof(char) * LINE_WITH);
  result->buffer[0] = '\0';
  result->size = LINE_WITH;
  result->length = 0;
  return result;
}

line_t *line_from_string(char *text){
  line_t *result = line_new();
  return line_write(line, text);
}
