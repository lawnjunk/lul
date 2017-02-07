#include "tools.h"

flub_t flub_create(char *msg){
  debug("flub_create");
  return (flub_t) { .trouble=false, .msg=msg };
}

bool flub_is_evil(flub_t err){
  debug("flub_is_evil");
  return err.trouble;
}

void flub_trouble_on(flub_t *err, char *msg){
  debug("flub_trouble_on");
  err->msg = msg;
  err->trouble = true;
};

void flub_trouble_off(flub_t *err){
  debug("flub_trouble_off");
  err->trouble = false;
}
