#include "tools.h"
#include "minunit.h"
#include "lul_types.h"
#include "cursor.h"
#include "buffer.h"
#include "flub.h"
#include "line.h"
#include "doc.h"

#define describe(msg) puts(msg); if(true)
#define it(msg) printf("  %s\n", msg); if(true)

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

#ifdef NO_TEST_LOG
#define ok(thing, cmp, val) mu_check(cmp(thing, val));
#else
#define ok(thing, cmp, val)\
  printf("    [%s]: ", #thing); \
  cmp(thing, val) ? printf(LUL_COLOR_GREEN) : printf(LUL_COLOR_RED);\
  printf("%s %s\n", #cmp, #val);\
  printf(LUL_COLOR_RESET);\
  mu_check(cmp(thing, val));
#endif

#ifdef NO_TEST_LOG
#define check(thing, cmp) mu_check(cmp(thing));
#else
#define check(thing, cmp)\
  printf("    [%s]: ", #thing); \
  cmp(thing) ? printf(LUL_COLOR_GREEN) : printf(LUL_COLOR_RED);\
  printf("%s\n", #cmp);\
  printf(LUL_COLOR_RESET);\
  mu_check(cmp(thing));
#endif
// usefule log tools for debuging
#define p_i(x) printf(":{{ %s }}: %d\n", #x, x);
#define p_l(x) printf(":{{ %s }}: %ld\n", #x, x);
#define p_u(x) printf(":{{ %s }}: %u\n", #x, x);
#define p_ul(x) printf(":{{ %s }}: %lu\n", #x, x);
#define p_s(x) printf(":{{ %s }}: %s\n", #x, x);
#define p_f(x) printf(":{{ %s }}: %f\n", #x, x);
