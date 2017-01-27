#ifndef LERR
#define LERR
#include "tools.h"

typedef struct {
  char *msg;
  bool trouble;
} flub_t;

// create and free
flub_t *flub_create(char *message);
flub_t *flub_free(flub_t *err);

// operations
flub_t *flub_trouble_on(flub_t *err, char *msg);
flub_t *flub_trouble_off(flub_t *err);
bool flub_is_evil(flub_t *err);

#endif
