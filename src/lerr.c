#include "tools.h"
#include "lerr.h"

lerr_t *err_birth(char *msg){
  lerr_t *result = (lerr_t *) malloc(sizeof(lerr_t));
  result->msg = msg;
  result->trouble = false;
  return result;
}

lerr_t *err_nuke(lerr_t *err){
  free(err);
  err = NULL;
  return err;
}

bool err_is_evil(lerr_t *err){
  return err->trouble;
}

lerr_t *err_trouble_on(lerr_t *err, char *msg){
  err->msg = msg;
  err->trouble = true;
  return err;
};

lerr_t *err_trouble_off(lerr_t *err){
  err->trouble = false;
  return err;
}
