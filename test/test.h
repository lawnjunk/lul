#ifndef LUL_TEST
#define LUL_TEST

#include "tools.h"
#include "minunit.h"
#include "lul_types.h"
#include "cursor.h"
#include "buffer.h"
#include "flub.h"
#include "line.h"
#include "doc.h"

char lul_error_msg[1000];
char lul_error_messages[5][1000];
int  lul_error_count = 0;

#define lul_errors_report()\
  for(int i=0; i< lul_error_count; i++){\
    printf("%s", lul_error_messages[i]);\
  }

#define describe(msg) puts(msg); if(true)
#define it(msg) minunit_run++; printf("  %s\n", msg); if(true)

#ifdef NO_TEST_LOG
#define should(msg, truth) mu_check(truth);
#else
#define should(msg, truth)\
  printf("  %s: %s\n", truth ? "\x1B[32mbooya\x1b[0m" : "\x1B[31mfuck \x1b[0m", msg);\
  mu_check(truth);
#endif

#define fail() \
  sprintf(lul_error_msg, "    [generic fail]: %sfuck(%s:%d)%s\n", LUL_COLOR_RED,  __FILE__, __LINE__,LUL_COLOR_RESET);\
  if(lul_error_count < 5){\
    strcpy(lul_error_messages[lul_error_count++], lul_error_msg);\
  }\
  printf("%s", lul_error_msg);\
  mu_check(false);

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

#define ok_msg_fail(thing, cmp, val)\
  sprintf(lul_error_msg, "    [%s]: %sfuck(%s:%d) %s %s%s\n", #thing ,\
      LUL_COLOR_RED, __FILE__, __LINE__, #cmp, #val, LUL_COLOR_RESET);\
      if(lul_error_count < 5)\
        strcpy(lul_error_messages[lul_error_count++], lul_error_msg);

#define ok_msg_success(thing, cmp, val)\
  sprintf(lul_error_msg, "    [%s]: %s%s %s%s\n", #thing,\
      LUL_COLOR_RED, #cmp, #val, LUL_COLOR_RESET);

#ifdef NO_TEST_LOG
#define ok(thing, cmp, val) mu_check(cmp(thing, val));
#else
#define ok(thing, cmp, val)\
  if(cmp(thing, val)){\
    ok_msg_success(thing, cmp, val);\
  } else {\
    ok_msg_fail(thing, cmp, val);\
  }\
  printf("%s", lul_error_msg);\
  mu_check(cmp(thing, val));
#endif

#define check_msg_fail(thing, cmp)\
  sprintf(lul_error_msg, "    [%s]: %sfuck(%s:%d) %s%s\n", #thing ,\
      LUL_COLOR_RED, __FILE__, __LINE__, #cmp, LUL_COLOR_RESET);\
      if(lul_error_count < 5)\
        strcpy(lul_error_messages[lul_error_count++], lul_error_msg);

#define check_msg_success(thing, cmp)\
  sprintf(lul_error_msg, "    [%s]: %s%s %s\n", #thing,\
      LUL_COLOR_RED, #cmp, LUL_COLOR_RESET);

#ifdef NO_TEST_LOG
#define check(thing, cmp) mu_check(cmp(thing));
#else
#define check(thing, cmp)\
  if(cmp(thing)){\
    check_msg_success(thing, cmp);\
  }else{\
    check_msg_fail(thing, cmp);\
  }\
  printf("%s", lul_error_msg);\
  mu_check(cmp(thing));
#endif
// usefule log tools for debuging
#define p_i(x) printf(":{{ %s }}: %d\n", #x, x);
#define p_l(x) printf(":{{ %s }}: %ld\n", #x, x);
#define p_u(x) printf(":{{ %s }}: %u\n", #x, x);
#define p_ul(x) printf(":{{ %s }}: %lu\n", #x, x);
#define p_s(x) printf(":{{ %s }}: %s\n", #x, x);
#define p_f(x) printf(":{{ %s }}: %f\n", #x, x);
#endif
