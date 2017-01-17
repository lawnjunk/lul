#ifndef BYTE_ARRAY
#define BYTE_ARRAY

#include <stdint.h>
#include <stdio.h>
#include "tools.h"
#include "lul_types.h"

#define byte_array_t struct byte_array

// this is a class
struct byte_array {
  uint8_t *buffer;
  size_t length;

  // uint8
  uint8_t (*read_uint8)(byte_array_t *self, size_t offset);
  boolean (*write_uint8)(byte_array_t *self, uint8_t value, size_t offset);
  // int8
  int8_t (*read_int8)(byte_array_t *self, size_t offset);
  boolean (*write_int8)(byte_array_t *self, int8_t value, size_t offset);
  
  // uint16 LE
  uint16_t (*read_uint16_LE)(byte_array_t *self, size_t offset);
  boolean (*write_uint16_LE)(byte_array_t *self, uint16_t value, size_t offset);
  // uint16 BE
  uint16_t (*read_uint16_BE)(byte_array_t *self, size_t offset);
  boolean (*write_uint16_BE)(byte_array_t *self, uint16_t value, size_t offset);
  
  // int16 LE
  int16_t (*read_int16_LE)(byte_array_t *self, size_t offset);
  boolean (*write_int16_LE)(byte_array_t *self, int16_t value, size_t offset);
  // int16 BE
  int16_t (*read_int16_BE)(byte_array_t *self, size_t offset);
  boolean (*write_int16_BE)(byte_array_t *self, int16_t value, size_t offset);
  
  // uint32 LE
  uint32_t (*read_uint32_LE)(byte_array_t *self, size_t offset);
  boolean (*write_uint32_LE)(byte_array_t *self, uint32_t value, size_t offset);
  // uint32 BE
  uint32_t (*read_uint32_BE)(byte_array_t *self, size_t offset);
  boolean (*write_uint32_BE)(byte_array_t *self, uint32_t value, size_t offset);

  //int32 LE
  int32_t (*read_int32_LE)(byte_array_t *self, size_t offset);
  boolean (*write_int32_LE)(byte_array_t *self, int32_t value, size_t offset);
  //in32 BE
  int32_t (*read_int32_BE)(byte_array_t *self, size_t offset);
  boolean (*write_int32_BE)(byte_array_t *self, int32_t value, size_t offset);

  // strings
  int (*write_string)(byte_array_t *self, char *str, size_t offset);
  char *(*read_string)(byte_array_t *self, size_t start, size_t end);
  char *(*to_string)(byte_array_t *self);

  // fill
  void (*fill_uint8)(byte_array_t *self, uint8_t num);
  void (*fill_int8)(byte_array_t *self, int8_t num);
  void (*fill_char)(byte_array_t *self, char num);

  // slice
  byte_array_t *(*slice)(byte_array_t *self, size_t start, size_t end);
};

byte_array_t *new_byte_array(size_t length);
byte_array_t *new_byte_array_from_file(FILE *infile);

#define byte_array_print(input) \
  for(int i=0; i<input->length; i++){ \
    printf("%s[%d]: 0X%X\n", #input, i, apply(input, read_uint8, i)); \
  }

#endif
