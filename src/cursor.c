#include "doc.h"
#include "line.h"
#include "flub.h"
#include "cursor.h"

cursor_t *cursor_create(doc_t *doc, unsigned int x, unsigned int y){
  dlog("cursor_create");
  cursor_t *result = (cursor_t *) malloc(sizeof(cursor_t));
  result->x = x;
  result->y = y;
  result->doc = doc; // doc is responsible for it own free
  result->err = flub_create("generic cursor error");
  return result;
}

cursor_t *cursor_free(cursor_t *cur){
  dlog("cursor_free");
  flub_free(cur->err);
  free(cur);
  cur = NULL;
  return cur;
}

bool cursor_is_evil(cursor_t *cur){
  dlog("cursor_is_evil");
  if(is_null(cur)) return true;
  return flub_is_evil(cur->err);
}

cursor_t *cursor_trouble_on(cursor_t *cur, char *msg){
  flub_trouble_on(cur->err, msg);
  return cur; 
}

cursor_t *cursor_write_char(cursor_t *cur, char ch){
  unsigned int x = cur->x;
  unsigned int y =cur->y;
  doc_t *doc = cur->doc;
  // check for evil_ness
  if(cursor_is_evil(cur)) return cur;
  if(doc_is_evil(doc)) 
    return cursor_trouble_on(cur, "doc was evil");
  // make sure its in a valid location
  // is the line length valid?
  if(y > doc->length)
    return cursor_trouble_on(cur, "not a valid line number");
  // get the line
  line_t *cur_line = (doc->lines)[y];
  // check if the line is evil
  if(line_is_evil(cur_line))
    return cursor_trouble_on(cur, "line was evil");
  // is the curor posion on the line valid
  if(x > cur_line->length)
    return cursor_trouble_on(cur, "not a valid line index");
  // write the char
  line_insert_char(cur_line, ch, x);
  // check success
  if(line_is_evil(cur_line))
    return cursor_trouble_on(cur, "write not successful");
  return cur;
}
