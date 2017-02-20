#include "test.h"

MU_TEST(line_t_test) {
  describe("line_create"){
    it("should create a line"){
      line_t *line = line_create("hello world");
      ok(line->length, eq_int, 11);
      check(line, !line_is_evil);
      ok(line->size, eq_uint, LINE_WITH);
      ok(line->buffer.length, eq_size, LINE_WITH);
      l_free(line, line);
    }

    it("should not freek wit null"){
      line_t *line = line_create(NULL);
      ok(line->length, eq_int, 0);
      check(line, !line_is_evil);
      ok(line->size, eq_uint, LINE_WITH);
      ok(line->buffer.length, eq_size, LINE_WITH);
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
      flub_trouble_on(&line->err, "");
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
      ok((str = line_to_string(line)), eq_str, "sha"); free(str);
      line_append_char(line, 'r');
      ok((str = line_to_string(line)), eq_str, "shar"); free(str);
      line_append_char(line, 'k');
      ok((str = line_to_string(line)), eq_str, "shark"); free(str);
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
    char *result;

    it("should not delete from an empy line"){
    }

    it("should delete a char at a valid offset"){
      ok((result = line_to_string(line)), eq_str, "abc"); free(result);

      line_delete_char(line, 0);
      ok((result = line_to_string(line)), eq_str, "bc"); free(result);

      line_delete_char(line, 1);
      ok((result = line_to_string(line)), eq_str, "b"); free(result);

      line_delete_char(line, 0);
      ok((result = line_to_string(line)), eq_str, ""); free(result);

      check(line, !line_is_evil);
    }

    it("should return an evil line if deleteing from an empty line"){
      line_delete_char(line, 0);
      ok((result = line_to_string(line)), eq_str, ""); free(result);
      check(line, line_is_evil);
    }

    l_free(line, line);
  }

  describe("line_insert_char"){
    line_t *line = line_create("booya!");
    char *text;
    it("should insert a char at a vaild index"){
      ok((text = line_to_string(line)), eq_str, "booya!"); free(text);
      line_insert_char(line, '!', 0);
      ok((text = line_to_string(line)), eq_str, "!booya!"); free(text);
      line_insert_char(line, '!', 4);
      ok((text = line_to_string(line)), eq_str, "!boo!ya!"); free(text);
      check(line, !line_is_evil);
    }

    it("should not write to a invalid index"){
      line_insert_char(line, '!', 100);
      ok((text = line_to_string(line)), eq_str, "!boo!ya!"); free(text);
      check(line, line_is_evil);
    }

    it("should not write to an evil string"){
      line_insert_char(line, '!', 0);
      ok((text = line_to_string(line)), eq_str, "!boo!ya!"); free(text);
      check(line, line_is_evil);
    }


    it("should not write to a line that is full"){
      line_t *no_room = line_create("hello");
      no_room->size=5;
      line_insert_char(no_room, 'a', 0);
      ok((text = line_to_string(no_room)), eq_str, "hello"); free(text);
      check(no_room, line_is_evil);
      l_free(no_room, line);
    }

    l_free(line, line);
  }

  describe("line_write_line"){
    line_t *src = line_create("1234");
    line_t *dest = line_create("aaa");
    char *text;

    it("should write with valid doffset and counts"){
      line_write_line(dest, src, 1, 0, 3);
      ok((text = line_to_string(dest)), eq_str, "a123"); free(text);
      check(dest, !line_is_evil);
      check(src, !line_is_evil);
    }

    it("should not write with invalid count and src length offset"){
      line_write_line(dest, src, 0, 0, 5);
      ok((text = line_to_string(dest)), eq_str, "a123"); free(text);
      check(dest, line_is_evil);
    }

    it("it should not write to an evil buffer"){
      line_write_line(dest, src, 0, 0, 2);
      ok((text = line_to_string(dest)), eq_str, "a123"); free(text);
      check(dest, line_is_evil);
    }
  }

}
