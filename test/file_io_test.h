#include "test.h"

void on_read(buffer_t *buf){
  it("SHOULD RUN THIS SHIZ"){
    check(buf, !buffer_is_evil);
    truthy(true);
    check(buf, !is_null);
    ok(buffer_read_char(buf, 0), eq_char, 'h');
    ok(buffer_read_char(buf, 1), eq_char, 'e');
    ok(buffer_read_char(buf, 2), eq_char, 'l');
    ok(buffer_read_char(buf, 3), eq_char, 'l');
    ok(buffer_read_char(buf, 4), eq_char, 'o');
    ok(buffer_read_char(buf, 5), eq_char, '\n');
    ok(buffer_read_char(buf, 10), eq_char, '\n');
    ok(buf->length, eq_size, 6);
  }
}

void on_fail(buffer_t *buf){
  it("should be an empty buff"){
    truthy(true);
    check(buf, is_null);
  }
}

void test_on_write(flub_t *err){
  if(flub_is_evil(err))
    puts ("SHIZ it hit here");
  else
    printf("booye\n");
}

MU_TEST(file_io_test){
  describe("it should run z tests"){
    file_read_buffer("./test/test_data.txt", on_read);
    file_read_buffer("./nope.c", on_fail);

    buffer_t *temp_data = buffer_from_char_array("this is a test");
    puts("\\nn");
    file_write_buffer("./test_file.txt", temp_data, test_on_write);

  }
}
