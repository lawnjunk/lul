#ifndef LUL_TOOLS
#define LUL_TOOLS
//#define DEBUG

// # unified header for all external libs
#include <sys/time.h>
#include <ncurses.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

// memory management macro
// l_free is used to force vars to be assined NULL after calling
// the appropriate type_free destructor
#define l_free(x, type) x = type ## _free(x)

// MIN and MAX macros
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

// cool for loop macro
#define range(x, s, e)\
  for(int x = s; x < e; x++)

#define range_down(x, s, e)\
  for(int x = s; x > e; x--)

// cast and compare macros
#define eq_str(a, b) (strcmp(a, b) == 0)
#define eq_uint8(a, b) ((uint8_t) a == (uint8_t) b)
#define eq_int8(a, b) ((int8_t) a == (int8_t) b)
#define eq_uint16(a, b) ((uint16_t) a == (uint16_t) b)
#define eq_int16(a, b) ((int16_t) a == (int16_t) b)
#define eq_uint32(a, b) ((uint32_t) a == (uint32_t) b)
#define eq_int32(a, b) ((int32_t) a == (int32_t) b)
#define eq_char(a, b) ((char) a == (char) b)
#define eq_size(a, b) ((size_t) a == (size_t) b)

// null check macro
#define is_null(ptr) (ptr == NULL)

#define LUL_COLOR_RESET   "\x1B[0m"
#define LUL_COLOR_RED     "\x1B[31m"
#define LUL_COLOR_GREEN   "\x1B[32m"
#define LUL_COLOR_YELLOW  "\x1B[33m"
#define LUL_COLOR_BLUE    "\x1B[34m"
#define LUL_COLOR_MAGENTA "\x1B[35m"
#define LUL_COLOR_CYAN    "\x1B[36m"
#define LUL_COLOR_WHITE   "\x1B[37m"

#ifdef DEBUG
#define dlog(args...)\
printf(LUL_COLOR_MAGENTA); printf("DEBUG: ");\
printf(LUL_COLOR_CYAN); printf(args);\
printf(LUL_COLOR_RESET); puts("");
#else 
#define dlog(args ...)
#endif

#endif 
