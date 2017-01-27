#ifndef LUL_DOC
#define LUL_DOC
#include "tools.h"
#include "flub.h"
#include "line.h"
#include "buffer.h"

// starts at 100 lines and doubles each time it runs up 100

#define doc_t struct doc
struct doc {
  line_t **lines;
  flub_t *err;
  unsigned int length; // number of lines
  unsigned int size;   // amount allocated
};

// line create and destroy
doc_t *doc_create();
doc_t *doc_free(doc_t *doc);

// line operations

#endif
