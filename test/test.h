#include "tools.h"
#include "minunit.h"
#include "flub.h"
#include "buffer.h"
#include "line.h"

#define describe(msg) puts(msg); if(true)

#ifdef NO_TEST_LOG
#define should(msg, truth) mu_check(truth);
#else 
#define should(msg, truth)\
  printf("  %s: %s\n", truth ? "\x1B[32mbooya\x1b[0m" : "\x1B[31mfuck \x1b[0m", msg);\
mu_check(truth);
#endif

#define fail() should( "generic fail", false)

#ifdef NO_TEST_LOG
#define okay(thing, msg, truth) mu_check(truth);
#else
#define okay(thing, msg, check)\
  printf("  [%s]: ", #thing); \
  check ? printf(LUL_COLOR_GREEN) : printf(LUL_COLOR_RED);\
  printf("%s\n", msg);\
  printf(LUL_COLOR_RESET);\
  mu_check(check);
#endif

// usefule log tools for debuging
#define p_i(x) printf(":{{ %s }}: %d\n", #x, x);
#define p_l(x) printf(":{{ %s }}: %ld\n", #x, x);
#define p_u(x) printf(":{{ %s }}: %u\n", #x, x);
#define p_ul(x) printf(":{{ %s }}: %lu\n", #x, x);
#define p_s(x) printf(":{{ %s }}: %s\n", #x, x);
#define p_f(x) printf(":{{ %s }}: %f\n", #x, x);
