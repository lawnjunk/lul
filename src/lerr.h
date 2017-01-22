#ifndef LERR
#define LERR
#include "tools.h"

typedef struct {
  char *msg;
  bool trouble;
} lerr_t;

// create and free
lerr_t *err_create(char *message);
lerr_t *err_free(lerr_t *err);

// operations
lerr_t *err_trouble_on(lerr_t *err, char *msg);
lerr_t *err_trouble_off(lerr_t *err);
bool err_is_evil(lerr_t *err);

#endif
