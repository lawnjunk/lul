#include "tools.h"
#include "minunit.h"
#include "lerr.h"
#include "buffer.h"

#define equal_strings(a, b) (strcmp(a, b) == 0)
#define describe(msg) puts(msg); if(true)
#define should(msg, truth)\
  printf("  %s: %s\n", truth ? "success" : "fail   ", msg);\
mu_check(truth);\

#define fail() should( "generic fail", false)
#define is_null(ptr) (ptr == NULL)


MU_TEST(lerr_t_test) {
  describe("TEST err_create") {
    char * message = "example message";
    lerr_t *err = err_create(message);
    should("->msg should equal 'example message'", equal_strings(err->msg, message));
    should("->trouble should equal false", err-> trouble == false);
    err_free(err);
  }

  describe("TEST err_free") {
    lerr_t *err = err_create("a bit of a byte");
    lerr_t *gone = err_free(err);
    should("should be null", is_null(gone));
  }

  describe("TEST err_trouble_on"){
    lerr_t *err = err_create("a bit of a byte");
    bool truth = (err_trouble_on(err))->trouble == true;
    should("turn truble on",  truth);
    err_free(err);
  }

  describe("TEST err_trouble_off"){
    lerr_t *err = err_create("a bit of a byte");
    bool truth = (err_trouble_off(err))->trouble == false;
    should("turn truble off",  truth);
    err_free(err);
  }

  describe("TEST err_is_evil"){
    lerr_t *err = err_create("a bit of a byte");
    should("err should not be evil",  !err_is_evil(err));
    err_trouble_on(err);
    should("err should be evil",  err_is_evil(err));
    err_free(err);
  }
}

MU_TEST(buffer_t_test) {
  describe("TEST buffer_create"){
    buffer_t *buf = buffer_create(10);
    should("->length should equal 10", buf->length == 10);
    should("->data should not be NULL", !is_null(buf->data));
    buffer_free(buf);
  }

  describe("TEST buffer_free"){
    buffer_t *buf = buffer_create(10);
    buf = buffer_free(buf);
    should("buf should be null", is_null(buf));
  }

  describe("TEST buffer_from_file"){
    FILE *test_data = fopen("./test_data.txt", "r");
    buffer_t *buf = buffer_from_file(test_data);
    should("->length should equal 6", buf->length == 6);
    should("->data should conain 'hello\\n'", (
          (buf->data[0] == 'h') &&
          (buf->data[1] == 'e') &&
          (buf->data[2] == 'l') &&
          (buf->data[3] == 'l') &&
          (buf->data[4] == 'o') &&
          (buf->data[5] == '\n') 
          ));
    buffer_free(buf);
    fclose(test_data);
  }
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(lerr_t_test);
  MU_RUN_TEST(buffer_t_test);
}

int main(int argc, char *argv[]) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return 0;
}
