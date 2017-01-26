#include "test.h"

MU_TEST(flub_t_test) {
  describe("TEST flub_birth") {
    char * message = "example message";
    flub_t *err = flub_birth(message);
    should("->msg should equal 'example message'", equal_strings(err->msg, message));
    should("->trouble should equal false", err-> trouble == false);
    flub_nuke(err);
  }

  describe("TEST flub_nuke") {
    flub_t *err = flub_birth("a bit of a byte");
    flub_t *gone = flub_nuke(err);
    should("should be null", is_null(gone));
  }

  describe("TEST flub_trouble_on"){
    flub_t *err = flub_birth("a bit of a byte");
    err = flub_trouble_on(err, "something failed");
    should("turn truble on",  err->trouble);
    should("turn set err msg",  equal_strings(err->msg, "something failed"));
    flub_nuke(err);
  }

  describe("TEST flub_trouble_off"){
    flub_t *err = flub_birth("a bit of a byte");
    bool truth = (flub_trouble_off(err))->trouble == false;
    should("turn truble off",  truth);
    flub_nuke(err);
  }

  describe("TEST flub_is_evil"){
    flub_t *err = flub_birth("a bit of a byte");
    should("err should not be evil",  !flub_is_evil(err));
    flub_trouble_on(err, "");
    should("err should be evil",  flub_is_evil(err));
    flub_nuke(err);
  }
}
