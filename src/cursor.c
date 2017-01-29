#include "tools.h"

cursor_t *cursor_create(doc_t *doc, unsigned int x, unsigned int y){
  debug("cursor_create");
  cursor_t *result = (cursor_t *) malloc(sizeof(cursor_t));
  result->x = x;
  result->y = y;
  result->doc = doc; // doc is responsible for it own free
  result->err = flub_create("generic cursor error");
  return result;
}

cursor_t *cursor_free(cursor_t *cur){
  debug("cursor_free");
  flub_free(cur->err);
  free(cur);
  cur = NULL;
  return cur;
}

bool cursor_is_evil(cursor_t *cur){
  debug("cursor_is_evil");
  if(is_null(cur)) return true;
  if(flub_is_evil(cur->err)) return true;
  if(doc_is_evil(cur->doc)){
    cursor_trouble_on(cur, "doc was evil");
    return true;
  }
  return false;
}

cursor_t *cursor_trouble_on(cursor_t *cur, char *msg){
  debug("cursor_trouble_on");
  flub_trouble_on(cur->err, msg);
  return cur;
}

cursor_t *cursor_move_up(cursor_t *cur){
  debug("cursor_move_up");
  if(cursor_is_evil(cur)) return cur;
  if(cur->y > 0) cur->y--;
  return cur;
}

cursor_t *cursor_move_down(cursor_t *cur){
  debug("cursor_move_down");
  if(cursor_is_evil(cur)) return cur;
  if(cur->y < (cur->doc->length)) (cur->y)++;
  return cur;
}

cursor_t *cursor_move_left(cursor_t *cur){
  debug("cursor_move_left");
  if(cursor_is_evil(cur)) return cur;
  if(cur->x > 0) (cur->x)--;
  return cur;
}

cursor_t *cursor_move_right(cursor_t *cur){
  debug("cursor_move_right");
  if(cursor_is_evil(cur)) return cur;
  line_t *cur_line = line_from_cursor(cur);
  if(cursor_is_evil(cur)) return cur;
  if(cur->x < (cur_line->length - 1)) (cur->x)++;
  return cur;
}

cursor_t *cursor_write_char(cursor_t *cur, char ch){
  debug("cursor_write_char");
  // check if curser is evil
  if(cursor_is_evil(cur)) return cur;
  // get line_t from cursor position
  line_t *cur_line = line_from_cursor(cur);
  // check if line is evil
  if(line_is_evil(cur_line)) 
    return cur;
  cur_line = line_insert_char(cur_line, ch, cur->x);
  // check success
  if(line_is_evil(cur_line))
    return cursor_trouble_on(cur, "write not successful");
  return cur;
}
