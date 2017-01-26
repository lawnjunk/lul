#include "test.h"


/*printf("debug %d\n", DEBUG);*/

MU_TEST(line_t_test) {
  describe("TEST line_birth"){
    line_t *line = line_birth("hello world");
    should("have a length of 11", (line->length == 11));
    should("have a flub", !flub_is_evil(line->err));
    should("have a size of line_with", (line->size == LINE_WITH));
    should("have a buffer with length 1000", (line->buffer->length == LINE_WITH));
    line_nuke(line); 
  }
}
