#include "test.h"

void on_read(bool failed,void *buf){
  puts("FUCK YEA HIT ON_READ TEST FILE CALLBACK");
  ok(buffer_read_char(buf, 0), eq_char, 'P');
}

void on_write(bool failed,void *buf){
  puts("MMMHUMMMM on write be done");
}

MU_TEST(file_io_test){
  describe("it should run z tests"){
    file_read_buffer("./makefile", on_read);

    buffer_t *wat = buffer_from_char_array("hello world");
    printf("wat len: %lu", wat->length);
    file_write_buffer("./goooey_fooey.txt", wat, on_write);

    flub_t err = { .trouble= false, .msg= "hello" };

  }
}
