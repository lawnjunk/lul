#ifndef LUL_DOC
#define LUL_DOC
#include "tools.h"

// starts at 100 lines and doubles each time it runs up 100
//TODO: eventualy i want to refacter doc_cursor_t into its own file


// doc  create and destroy
doc_t *doc_create();
doc_t *doc_free(doc_t *doc);
doc_t *doc_trouble_on(doc_t *doc, char* msg);
bool doc_is_evil(doc_t *doc);

doc_t *doc_insert_new_line(doc_t *doc, cursor_t *cur);

#endif
