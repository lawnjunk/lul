#include "test.h"

MU_TEST(line_t_test) {
  describe("line_create"){
    line_t *line = line_create("hello world");
    okay(line, "have a length of 11", (line->length == 11));
    okay(line, "have a flub", !flub_is_evil(line->err));
    okay(line, "have a size of line_with", (line->size == LINE_WITH));
    okay(line, "have a buffer with length 1000", (line->buffer->length == LINE_WITH));
    l_free(line, line); 
  }

  describe("line_free"){
    line_t *line = line_create("");
    l_free(line, line);
    should("line should be null", line == NULL);
  }

  describe("line_is_evil"){
    line_t *line = line_create("");

    okay(line, "should not be evil", !line_is_evil(line));

    flub_trouble_on(line->err, "");
    okay(line, "line should be evil", line_is_evil(line));
    l_free(line, line);
  }

  describe("line_read_char"){
    line_t *line = line_create("hello");

    char ch = line_read_char(line, 0);
    okay( ch, "should be 'h'", ch == 'h');

    ch = line_read_char(line, 4);
    okay( ch, "should be 'o'", ch == 'o');

    ch = line_read_char(line, 6);
    okay( ch, "should be '\\0'", ch == '\0');

    l_free(line, line);
  }

  describe("line_to_string"){
    line_t *line = line_create("lulwat");
    
    char *lul = line_to_string(line);
    okay(lul, "should equal 'lulwat'", eq_str(lul, "lulwat"));
    free(lul);

    line_t *empty = line_create("");
    lul = line_to_string(empty);
    okay(lul, "should equal ''", eq_str(lul, ""));
    free(lul);

    l_free(line, line);
    l_free(empty, line);
  }



  describe("line_append_char"){
    line_t *line = line_create("sha");

    okay(line->length, "should equal 3", line->length == 3);  
    line_append_char(line, 'r');
    char ch = line_read_char(line, line->length - 1);
    okay(ch , "should equal 'r'", ch == 'r');
    okay(line->length, "should equal 4", line->length == 4);  
    okay(line, "should not be evil", !line_is_evil(line));

    line->length = LINE_WITH - 1 ;
    line_append_char(line, 'k');
    okay(line, "should be evil", line_is_evil(line));
    l_free(line, line);
  }

  describe("line_delete_char"){
    line_t *line = line_create("abc");
    okay(line->length, "should equal 3", line->length == 3);  

    line_delete_char(line, 0);
    char *result = line_to_string(line);
    okay(line, "should be able to delete first index", eq_str(result, "bc"));
    okay(line->length, "should shrink on delete", line->length == 2);  
    okay(line, "should not be evil after delete", !line_is_evil(line));

    line_delete_char(line, 1);
    result = line_to_string(line);
    okay(line->length, "should equal 1", line->length == 1);  
    okay(line, "should be 'b'", eq_str(result, "b"));
    okay(line, "should not be evil", !line_is_evil(line));

    line_delete_char(line, 0);
    result = line_to_string(line);
    okay(line->length, "should equal 0", line->length == 0);  
    okay(line, "should be ''", eq_str(result, ""));

    okay(wat, "cmp '' ''", eq_str("", ""));
    okay(line, "should not be evil", !line_is_evil(line));

    line_delete_char(line, 0);
    okay(line, "should be evil", line_is_evil(line));
    okay(line->length, "should equal 0", line->length == 0);  
    line_delete_char(line, 10);
    okay(line, "should be evil", line_is_evil(line));
    okay(line->length, "should equal 0", line->length == 0);  
    free(result);
    l_free(line, line);
  }

  describe("line_insert_char"){
    line_t *line = line_create("booya!");

    line_insert_char(line, '!', 0);
    char *text = line_to_string(line);
    okay(line, "can insert at 0", eq_str(text, "!booya!"));

    line_insert_char(line, '!', 2);
    text = line_to_string(line);
    okay(line, "can insert at 2", eq_str(text, "!b!ooya!"));

    line_insert_char(line, 'a', line->length );
    text = line_to_string(line);
    okay(line, "can insert at line length", eq_str(text, "!b!ooya!a"));
    okay(line, "should not be evil", !line_is_evil(line));

    line_insert_char(line, 'a', line->length  + 1);
    okay(line, "will be evil if try to insert past line length",
        line_is_evil(line));

    line_insert_char(line, 'a', 0);
    text = line_to_string(line);
    okay(line, "will not change the string for evil operations",
        eq_str(text, "!b!ooya!a"));
    free(text);

    line_t *no_room = line_create("hello");
    no_room->size=5;
    line_insert_char(no_room, 'a', 0);
    text = line_to_string(no_room);
    okay(no_room, "will not right to a full string",
        eq_str(text, "hello"));
    okay(no_room, "will be evil on insert to full buffer",
        line_is_evil(no_room));
    free(text);

    l_free(line, line);
    l_free(no_room, line);
  }

  describe("line_write_line"){
    line_t *src = line_create("1234");
    line_t *dest = line_create("aaa");
    
    if("should copy '123' to the second offset of 1"){
      line_write_line(dest, src, 2, 0, 3);
      p_s(line_to_string(dest));
      ok(line_to_string(dest), eq_str, "aa123");
    }
  }

}
