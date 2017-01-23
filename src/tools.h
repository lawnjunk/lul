#ifndef LUL_TOOLS
#define LUL_TOOLS

// # unified header for all external libs
#include <ncurses.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// MIN and MAX macros
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

// cast and compare macros
#define equal_strings(a, b) (strcmp(a, b) == 0)
#define equal_uint8(a, b) ((uint8_t) a == (uint8_t) b)
#define equal_int8(a, b) ((int8_t) a == (int8_t) b)
#define equal_uint16(a, b) ((uint16_t) a == (uint16_t) b)
#define equal_int16(a, b) ((int16_t) a == (int16_t) b)
#define equal_uint32(a, b) ((uint32_t) a == (uint32_t) b)
#define equal_int32(a, b) ((int32_t) a == (int32_t) b)
#define equal_char(a, b) ((char) a == (char) b)
#define equal_size(a, b) ((size_t) a == (size_t) b)

// null check macro
#define is_null(ptr) (ptr == NULL)

#endif 
