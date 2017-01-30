#include "tools.h"

#define DOC_START_SIZE 100

doc_t *doc_create(){
  debug("doc_create");
  doc_t *result = (doc_t *) malloc(sizeof(doc_t));
  result->lines = (line_t **) calloc(sizeof(line_t *), DOC_START_SIZE);
  result->err = flub_create("generic doc error");
  result->size = DOC_START_SIZE;
  range(i, 0 , result->size){
    (result->lines)[i] = line_create("");
  }
  result->length = 0;
  return result;
}

doc_t *doc_free(doc_t *doc){
  debug("doc_free");
  range(i, 0, doc->size){
    // free each line then free lines
    line_free((doc->lines)[i]);
  }

  free(doc->lines);

  // free err
  flub_free(doc->err);
  // free line
  free(doc); doc = NULL;
  return doc;
}

bool doc_is_evil(doc_t *doc){
  if(is_null(doc)) return true;
  return flub_is_evil(doc->err);
}

doc_t *doc_trouble_on(doc_t *doc, char *msg){
  flub_trouble_on(doc->err, msg);
  return doc;
}

/*aaaa*/
/*bbbb*/
/*cccc*/
/*dddd*/

doc_t *doc_insert_new_line(doc_t *doc, cursor_t *cur){
  if(doc_is_evil(doc)) return doc;
  line_t *cur_line = line_from_cursor(cur, 0);
  line_t *next = line_from_cursor(cur, 1);
  l_free(doc->lines[doc->length], line);
  range_down(i, doc->length, cur->y + 1)
    doc->lines[i] = doc->lines[i-1];

  line_insert_char(cur_line, '\n', cur->x);
  cur_line->length = cur->x;
  next->length = cur_line->length - cur->x;
  line_write_line(next, cur_line, 0, cur->x, next->length);
  l_free(next, line);
  doc->lines[cur->y + 1] = line_create("");
  return doc;
}
