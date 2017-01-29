#include "tools.h"

flub_t *flub_create(char *msg){
  debug("flub_create");
  flub_t *result = (flub_t *) malloc(sizeof(flub_t));
  result->msg = msg;
  result->trouble = false;
  return result;
}

flub_t *flub_free(flub_t *err){
  debug("flub_free");
  free(err);
  err = NULL;
  return err;
}

bool flub_is_evil(flub_t *err){
  debug("flub_is_evil");
  if(is_null(err)) return true;
  return err->trouble;
}

flub_t *flub_trouble_on(flub_t *err, char *msg){
  debug("flub_trouble_on");
  err->msg = msg;
  err->trouble = true;
  return err;
};

flub_t *flub_trouble_off(flub_t *err){
  debug("flub_trouble_off");
  err->trouble = false;
  return err;
}
