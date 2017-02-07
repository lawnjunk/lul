#ifndef LERR
#define LERR
#include "tools.h"

// create and free
flub_t flub_create(char *message);

// operations
void flub_trouble_on(flub_t *err, char *msg);
void flub_trouble_off(flub_t *err);
bool flub_is_evil(flub_t err);

#endif
