#include <stdint.h>
#include <string.h>
#include "tools.h"
#include "minunit.h"

#define equal_strings(a, b) (strcmp(a, b) == 0)

MU_TEST(line_t_test) {
  puts("testing new_line");
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(line_t_test);
}

int main(int argc, char *argv[]) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return 0;
}
