#include "test.h"

MU_TEST(cursor_t_test) {
  describe("cursor_create and cursor_free"){
    doc_t *doc = doc_create();
    cursor_t *pt = cursor_create(doc, 100, 300);
    okay(pt->x, "should be 100", pt->x == 100);
    okay(pt->y,"should be 300", pt->y  == 300);
    okay(pt->doc, "should referce doc", pt->doc == doc);
    cursor_is_evil(pt);

    l_free(pt, cursor);
    okay(doc, "should not be freed from cursor_free", !is_null(doc));
    okay(pt, "should not be freed from cursor_free", pt == NULL);
    l_free(doc, doc);
  }

  describe("cursor_move_up"){
    doc_t *doc = doc_create();
    cursor_t *cur = cursor_create(doc, 0, 0);

    it("the cursor can not move above y:0"){
      cursor_move_up(cur);
      ok(cur->y, eq_uint, 0);
      check(cur, !cursor_is_evil);
    }

    it("the cursor can move up when y>0"){
      // set the doc_legth to 10
      doc->length = 10;
      cur->y = 4;
      cursor_move_up(cur);
      ok(cur->y, eq_uint, 3);
      cursor_move_up(cur);
      ok(cur->y, eq_uint, 2);
      cursor_move_up(cur);
      ok(cur->y, eq_uint, 1);
      cursor_move_up(cur);
      ok(cur->y, eq_uint, 0);
      check(cur, !cursor_is_evil);
    }

    it("the cursor cannot move up if it is evil"){
      flub_trouble_on(cur->err, "for testing");
      cur->y = 3;
      cursor_move_up(cur);
      ok(cur->y, eq_uint, 3);
      check(cur, cursor_is_evil);
    }

    l_free(doc, doc);
    l_free(cur, cursor);
  }

  describe("cursor_move_down"){
    doc_t *doc = doc_create();
    cursor_t *cur = cursor_create(doc, 0, 0);
    doc->length = 4;

    it("the cursor can move down until y < (doc->length)"){
      cursor_move_down(cur);
      ok(cur->y, eq_uint, 1);
      cursor_move_down(cur);
      ok(cur->y, eq_uint, 2);
      cursor_move_down(cur);
      ok(cur->y, eq_uint, 3);
      cursor_move_down(cur);
      ok(cur->y, eq_uint, 3);
    }

    it("the cursor cannot move down if it is evil"){
      flub_trouble_on(cur->err, "for testing");
      cur->y = 3;
      cursor_move_down(cur);
      ok(cur->y, eq_uint, 3);
      check(cur, cursor_is_evil);
    }
    l_free(doc, doc);
    l_free(cur, cursor);
  }

  describe("cursor_move_left"){
    doc_t *doc = doc_create();
    cursor_t *cur = cursor_create(doc, 4, 0);

    it("should move less until x == 0"){
      cursor_move_left(cur);
      ok(cur->x, eq_uint, 3);
      cursor_move_left(cur);
      ok(cur->x, eq_uint, 2);
      cursor_move_left(cur);
      ok(cur->x, eq_uint, 1);
      cursor_move_left(cur);
      ok(cur->x, eq_uint, 0);
      cursor_move_left(cur);
      ok(cur->x, eq_uint, 0);
    }

    it("the curor cannot move left if it is evil"){
      cursor_trouble_on(cur, "for testing");
      cur->x = 3;
      cursor_move_left(cur);
      ok(cur->x, eq_uint, 3);
    }

    l_free(doc, doc);
    l_free(cur, cursor);
  }

  describe("cursor_move_right"){
    doc_t *doc = doc_create();
    cursor_t *cur = cursor_create(doc, 0, 0);
    doc->lines[0]->length = 3;

    it("the cursor can move right until x < (cur_line->length)"){
      cursor_move_right(cur);
      ok(cur->x, eq_uint, 1);
      cursor_move_right(cur);
      ok(cur->x, eq_uint, 2);
      cursor_move_right(cur);
      ok(cur->x, eq_uint, 3);
      cursor_move_right(cur);
      ok(cur->x, eq_uint, 3);
    }

    it("the curor cannot move left if it is evil"){
      cursor_trouble_on(cur, "for testing");
      cur->x = 2;
      cursor_move_right(cur);
      ok(cur->x, eq_uint, 2);
    }

    l_free(doc, doc);
    l_free(cur, cursor);
  }

  describe("cursor_write_char"){
    doc_t *doc = doc_create();
    cursor_t *cur = cursor_create(doc, 0, 0);
    line_t *cur_line = doc->lines[0];

    it("should be able to write a char to the line"){
      cursor_write_char(cur, 'h');
      cursor_move_right(cur);
      cursor_write_char(cur, 'e');
      cursor_move_right(cur);
      cursor_write_char(cur, 'l');
      cursor_move_right(cur);
      cursor_write_char(cur, 'l');
      cursor_move_right(cur);
      cursor_write_char(cur, 'o');

      ok(line_read_char(cur_line, 0), eq_char, 'h');
      ok(line_read_char(cur_line, 1), eq_char, 'e');
      ok(line_read_char(cur_line, 2), eq_char, 'l');
      ok(line_read_char(cur_line, 3), eq_char, 'l');
      ok(line_read_char(cur_line, 4), eq_char, 'o');
      ok(cur_line->length, eq_uint, 5);
      check(cur, !cursor_is_evil);
    }

    it("should be able to insert a char"){
      cur->x = 0;
      cursor_write_char(cur, 'g');
      cursor_write_char(cur, 'u');
      cursor_write_char(cur, 'l');
      cursor_write_char(cur, 's');

      ok(line_read_char(cur_line, 0), eq_char, 's');
      ok(line_read_char(cur_line, 1), eq_char, 'l');
      ok(line_read_char(cur_line, 2), eq_char, 'u');
      ok(line_read_char(cur_line, 3), eq_char, 'g');
      ok(cur_line->length, eq_uint, 9);
    }

    it("should not be able to insert a char if the cursor is evil"){
      line_insert_char(cur_line, '\0', 0);
      cur_line->length = 0;
      cur->x = 0;
      cursor_trouble_on(cur, "testing");
      check(cur, cursor_is_evil);
      check(cur->doc, !doc_is_evil);
      cursor_write_char(cur, 'a');
      ok(cur_line->length, eq_int, 0);
      ok(line_read_char(cur_line, 0), eq_char, '\0');
    }

    it("should not be able to insert a char if the cursor->doc is evil"){
      line_insert_char(cur_line, '\0', 0);
      cur_line->length = 0;
      cur->x = 0;

      doc_trouble_on(cur->doc, "for testing");

      flub_trouble_off(cur->err);
      check(cur->err, !flub_is_evil);
      check(cur->doc, doc_is_evil);
      cursor_write_char(cur, 'a');
      ok(cur_line->length, eq_int, 0);
      ok(line_read_char(cur_line, 0), eq_char, '\0');
    }

    it("should not be able to insert a char if the cur_line is evil"){
      line_insert_char(cur_line, '\0', 0);
      cur_line->length = 0;
      cur->x = 0;
      flub_trouble_off(cur->err);
      flub_trouble_off(cur->doc->err);
      line_trouble_on(cur_line, "hello");

      check(cur, !cursor_is_evil);
      check(cur->doc, !doc_is_evil);
      check(cur_line, line_is_evil);

      cursor_write_char(cur, 'a');
      ok(cur_line->length, eq_int, 0);
      ok(line_read_char(cur_line, 0), eq_char, '\0');
    }

    l_free(doc, doc);
    l_free(cur, cursor);
  }

}
