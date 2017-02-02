#include "test.h"

MU_TEST(doc_t_test) {
  describe("doc_create"){
    doc_t *doc = doc_create();

    it("should create a doc"){
      ok(doc->size, eq_size, 100);
      ok(doc->length, eq_uint, 0);
      bool lines_not_evil = true;
      range(i , 0, doc->size){
        if(line_is_evil(doc->lines[i])){
          lines_not_evil = false;
        }
      }
      ok(lines_not_evil, eq_int, true);
      check(doc, !doc_is_evil);
    }

    l_free(doc, doc);
  }

  describe("doc_free"){
    it("should return null"){
      doc_t *doc = doc_create();
      l_free(doc, doc);
      check(doc, is_null);
    }
  }
}
