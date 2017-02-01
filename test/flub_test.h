#include "test.h"

MU_TEST(flub_t_test) {
  describe("TEST flub_create") {
    it("should return a flub"){
      char * message = "example message";
      flub_t *err = flub_create(message);

      ok(err->msg, eq_str, "example message");
      ok(err->trouble, eq_int, false);
      flub_free(err);
    }
  }

  describe("TEST flub_free") {
    flub_t *err = flub_create("a bit of a byte");
    it("should return null"){
      flub_t *gone = flub_free(err);
      check(gone, is_null);
    }
  }


  describe("TEST flub_trouble_on"){
    it("should turn on truble and set its message"){
      flub_t *err = flub_create("a bit of a byte");
      err = flub_trouble_on(err, "something failed");
      truthy(err->trouble);
      ok(err->msg, eq_str, "something failed");
      flub_free(err);
    }
  }

  describe("TEST flub_trouble_off"){
    it("should turn the trouble off"){
      flub_t *err = flub_create("a bit of a byte");
      flub_trouble_off(err);
      truthy(!err->trouble);
      check(err, !flub_is_evil);
      flub_free(err);
    }
  }

  describe("TEST flub_is_evil"){
    flub_t *err = flub_create("a bit of a byte");

    it("should return false if truble is false"){
      check(err, !flub_is_evil);
    }

    it("should return true if the trouble is true"){
      flub_trouble_on(err, "");
      check(err, flub_is_evil);
    }

    flub_free(err);
  }
}
