#include "tools.h"
#include "flub.h"

flub_t *flub_birth(char *msg){
  flub_t *result = (flub_t *) malloc(sizeof(flub_t));
  result->msg = msg;
  result->trouble = false;
  return result;
}

flub_t *flub_nuke(flub_t *err){
  free(err);
  err = NULL;
  return err;
}

bool flub_is_evil(flub_t *err){
  return err->trouble;
}

flub_t *flub_trouble_on(flub_t *err, char *msg){
  err->msg = msg;
  err->trouble = true;
  return err;
};

flub_t *flub_trouble_off(flub_t *err){
  err->trouble = false;
  return err;
}
