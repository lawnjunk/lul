#ifndef LUL_DOC
#define LUL_DOC
#include "tools.h"
#include "flub.h"
#include "line.h"

// starts at 100 lines and doubles each time it runs up 100
//TODO: eventualy i want to refacter doc_cursor_t into its own file


#define doc_t struct doc
struct doc {
  line_t **lines;
  flub_t *err;
  unsigned int length; // number of lines
  unsigned int size;   // amount allocated
};


// doc  create and destroy
doc_t *doc_create();
doc_t *doc_free(doc_t *doc);
doc_t *doc_trouble_on(doc_t *doc, char* msg);
bool doc_is_evil(doc_t *doc);

#endif
