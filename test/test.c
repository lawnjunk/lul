#include "test.h"
#include "flub_test.c"
#include "buffer_test.c"
#include "line_test.c"

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(flub_t_test);
  MU_RUN_TEST(buffer_t_test);
  MU_RUN_TEST(line_t_test);
}

int main(int argc, char *argv[]) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  dlog("whats up?");
  return 0;
}
