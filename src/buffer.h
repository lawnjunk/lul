#ifndef BYTE_ARRAY
#define BYTE_ARRAY
#include "tools.h"
#include "lerr.h"

// this is a class
typedef struct {
  uint8_t *data;
  size_t length;
  lerr_t *err;
  bool is_slice; // necessary for buffer_free
} buffer_t;

// uint8
uint8_t buffer_read_uint8(buffer_t *buf, size_t offset);
buffer_t *buffer_write_uint8(buffer_t *buf, uint8_t value, size_t offset);
// int8
int8_t buffer_read_int8(buffer_t *buf, size_t offset);
buffer_t *buffer_write_int8(buffer_t *buf, int8_t value, size_t offset);

// uint16 LE
uint16_t buffer_read_uint16_LE(buffer_t *buf, size_t offset);
buffer_t *buffer_write_uint16_LE(buffer_t *buf, uint16_t value, size_t offset);
// uint16 BE
uint16_t buffer_read_uint16_BE(buffer_t *buf, size_t offset);
buffer_t *buffer_write_uint16_BE(buffer_t *buf, uint16_t value, size_t offset);

// int16 LE
int16_t buffer_read_int16_LE(buffer_t *buf, size_t offset);
buffer_t *buffer_write_int16_LE(buffer_t *buf, int16_t value, size_t offset);
// int16 BE
int16_t buffer_read_int16_BE(buffer_t *buf, size_t offset);
buffer_t *buffer_write_int16_BE(buffer_t *buf, int16_t value, size_t offset);

// uint32 LE
uint32_t buffer_read_uint32_LE(buffer_t *buf, size_t offset);
buffer_t *buffer_write_uint32_LE(buffer_t *buf, uint32_t value, size_t offset);

// uint32 BE
uint32_t buffer_read_uint32_BE(buffer_t *buf, size_t offset);
buffer_t *buffer_write_uint32_BE(buffer_t *buf, uint32_t value, size_t offset);

//int32 LE
int32_t buffer_read_int32_LE(buffer_t *buf, size_t offset);
buffer_t *buffer_write_int32_LE(buffer_t *buf, int32_t value, size_t offset);
//in32 BE
int32_t buffer_read_int32_BE(buffer_t *buf, size_t offset);
buffer_t *buffer_write_int32_BE(buffer_t *buf, int32_t value, size_t offset);

// strings
buffer_t *buffer_write_string(buffer_t *buf, char *str, size_t offset);
char *buffer_read_string(buffer_t *buf, size_t start, size_t end);
char *to_string(buffer_t *buf);

// buffer_fill
buffer_t *buffer_fill_uint8(buffer_t *buf, uint8_t num);
buffer_t *buffer_fill_int8(buffer_t *buf, int8_t num);
buffer_t *buffer_fill_char(buffer_t *buf, char num);

// slice
buffer_t *buffer_slice(buffer_t *buf, size_t start, size_t end);

// write buffer
buffer_t *buffer_write_buffer(buffer_t *dest, buffer_t *src, size_t offset, size_t count);

// is evil
bool buffer_is_evil(buffer_t *buf);

// create create and free
buffer_t *buffer_free(buffer_t *buf);
buffer_t *buffer_create(size_t length);
buffer_t *buffer_from_char_array(char *data);
buffer_t *buffer_from_int8_array(int8_t *data, size_t length);
buffer_t *buffer_from_uint8_array(uint8_t *data, size_t length);
buffer_t *buffer_from_file(FILE *infile);

#define buffer_print(input) \
  for(int i=0; i<input->length; i++){ \
    printf("%s[%d]: 0X%X\n", #input, i, buffer_read_uint8(input, i)); \
  }

#endif
