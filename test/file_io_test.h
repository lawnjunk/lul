#include "test.h"

void on_read(buffer_t *buf){
  it("SHOULD RUN THIS SHIZ"){
    truthy(true);
    check(buf, !is_null);
    ok(buf->length, eq_size, 36);
  }
}

void on_fail(buffer_t *buf){
  it("SHOULD RUN THIS SHIZ"){
    truthy(true);
    check(buf, is_null);
  }
}

MU_TEST(file_io_test){
  describe("it should run z tests"){
    file_read_buffer("./main.c", on_read);
    file_read_buffer("./nope.c", on_fail);
  }
  puts("FWHUEE");
}
