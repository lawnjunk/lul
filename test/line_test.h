#include "test.h"

MU_TEST(line_t_test) {
  describe("line_create"){
    it("should create a line"){
      line_t *line = line_create("hello world");
      ok(line->length, eq_int, 11);
      check(line, !line_is_evil);
      ok(line->size, eq_uint, LINE_WITH);
      ok(line->buffer->length, eq_size, LINE_WITH);
      l_free(line, line);
    }

    it("should not freek wit null"){
      line_t *line = line_create(NULL);
      ok(line->length, eq_int, 0);
      check(line, !line_is_evil);
      ok(line->size, eq_uint, LINE_WITH);
      ok(line->buffer->length, eq_size, LINE_WITH);
      l_free(line, line);
    }
  }

  describe("line_free"){
    it("should return null"){
      line_t *line = line_create("");
      l_free(line, line);
      check(line, is_null);
    }
  }

  describe("line_is_evil"){
    line_t *line = line_create("");

    it("should return false if its flub is not in trouble"){
      check(line, !line_is_evil);
    }

    it("should return ture if its flub is in trouble"){
      flub_trouble_on(line->err, "");
      check(line, line_is_evil);
    }

    l_free(line, line);
  }

  describe("line_read_char"){
    line_t *line = line_create("hello");

    it("should return the correct char at a valid offset"){
      ok(line_read_char(line, 0), eq_char, 'h');
      ok(line_read_char(line, 1), eq_char, 'e');
      ok(line_read_char(line, 2), eq_char, 'l');
      ok(line_read_char(line, 3), eq_char, 'l');
      ok(line_read_char(line, 4), eq_char, 'o');
    }

    it("should return '\\0' and make line evil for invalid offset"){
      ok(line_read_char(line, 6), eq_char, '\0');
      check(line, line_is_evil);
    }
    l_free(line, line);
  }

  describe("line_to_string"){
    it("should return lulwat"){
      line_t *line = line_create("lulwat");
      char *lul = line_to_string(line);
      ok(lul, eq_str, "lulwat");
      free(lul);
      l_free(line, line);
    }

    it("should return an empty string from a NULL line"){
      line_t *empty = line_create(NULL);
      char* lul = line_to_string(empty);
      ok(lul, eq_str, "");
      free(lul);
      l_free(empty, line);
    }
  }

  describe("line_append_char"){
    line_t *line = line_create("sha");

    it("should append a char"){
      ok(line->length, eq_uint, 3);
      char *str;
      ok((str = line_to_string(line)), eq_str, "sha");
      free(str);
      line_append_char(line, 'r');
      ok((str = line_to_string(line)), eq_str, "shar");
      free(str);
      line_append_char(line, 'k');
      ok((str = line_to_string(line)), eq_str, "shark");
      free(str);
      ok(line->length, eq_uint, 5);
      check(line, !line_is_evil)
    }

    it("should not apped if the line is full"){
      line->length = LINE_WITH - 1 ;
      line_append_char(line, 'k');
      ok(line_to_string(line), eq_str, "shark");
      check(line, line_is_evil);
    }

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

    it("should copy '123' to the second offset of 1"){
      line_write_line(dest, src, 2, 0, 3);
      p_s(line_to_string(dest));
      ok(line_to_string(dest), eq_str, "aa123");
    }
  }

}
