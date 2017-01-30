#include "test.h"
#include "cursor.h"

MU_TEST(doc_t_test) {
  describe("doc_create"){
    doc_t *doc = doc_create();
    
    okay(doc->size, "should be 100", doc->size == 100);
    okay(doc->length,"should be 0", doc->length == 0);
    okay(doc->err , "should not be evil", !flub_is_evil(doc->err));

    bool evil= line_is_evil((doc->lines)[0]);
    evil = line_is_evil((doc->lines)[doc->size-1]);
    okay(doc->lines, "is full of line_t structs", evil == false);

    doc_is_evil(doc);

    l_free(doc, doc);
  }

  describe("doc_free"){
    doc_t *doc = doc_create();
    l_free(doc, doc);
    okay(doc->lines, "should be NULL", doc == NULL);
  }
}
