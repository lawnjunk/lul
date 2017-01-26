#include "tools.h"
#include "minunit.h"
#include "flub.h"
#include "buffer.h"
#include "line.h"

#define describe(msg) puts(msg); if(true)
#define should(msg, truth)\
  printf("  %s: %s\n", truth ? "\x1B[32mbooya\x1b[0m" : "\x1B[31mfuck \x1b[0m", msg);\
mu_check(truth);\

#define fail() should( "generic fail", false)
