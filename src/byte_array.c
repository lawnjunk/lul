#include <stdint.h>
#include <gc.h>
#include <string.h>
#include <ctype.h>
#include "byte_array.h"
#include "tools.h"

typedef enum {
  LE,
  BE,
} byte_array_endian;


// type decliations for functions that are used out of order
byte_array_t *slice(byte_array_t *self, size_t start, size_t end);

// make_read8 creates a functions for reading 8bit
// signed and unsinged ints, at a size_t offset
// return type (type)
#define make_read8(name, type) \
  type name(byte_array_t *self, size_t offset){ \
    type *nums = (type *) self->buffer; \
    return nums[offset]; \
  }

make_read8(read_uint8, uint8_t);
make_read8(read_int8, int8_t);

// make_write8 creates functions for writing a signed
// or unsigned 8bit int, at a size_t offse
// return type int
// return false on fail
// return true on success
#define make_write8(name, type) \
  bool name(byte_array_t *self, type value, size_t offset){ \
    if(offset > self->length) \
    return false; \
    type *nums = (type *) self->buffer; \
    nums[offset] = value; \
    return true; \
  }

make_write8(write_uint8, uint8_t);
make_write8(write_int8, int8_t);

#define make_read16(name, type, endianness) \
  type name(byte_array_t *self, size_t offset){ \
    uint8_t *nums = (uint8_t *) self->buffer; \
    type result; \
    result = (type) nums[offset + (endianness == LE ? 1 : 0)]; \
    result = result << 8; \
    return result | nums[offset + (endianness == LE ? 0 : 1)]; \
  }

make_read16(read_uint16_LE, uint16_t, LE);
make_read16(read_int16_LE, int16_t, LE);
make_read16(read_uint16_BE, uint16_t, BE);
make_read16(read_int16_BE, int16_t, BE);

#define write_int16(name, type, endianness) \
  bool name(byte_array_t *self, type value, size_t offset){ \
    if(offset > self->length) \
    return false;  \
    uint8_t *nums = (uint8_t *) self->buffer; \
    nums[offset + (endianness == LE ? 0 : 1)] = value & 0xff; \
    nums[offset + (endianness == LE ? 1 : 0)] = value >> 8; \
    return true; \
  }

write_int16(write_uint16_LE, uint16_t, LE);
write_int16(write_int16_LE, int16_t, LE);
write_int16(write_uint16_BE, uint16_t, BE);
write_int16(write_int16_BE, int16_t, BE);

#define read_int32(name, type, endianness) \
  type name(byte_array_t *self, size_t offset){ \
    uint8_t *nums = (uint8_t *) self->buffer; \
    type result =            nums[offset + (endianness == LE ? 3 : 0)]; \
    result = (result << 8) | nums[offset + (endianness == LE ? 2 : 1)]; \
    result = (result << 8) | nums[offset + (endianness == LE ? 1 : 2)]; \
    return   (result << 8) | nums[offset + (endianness == LE ? 0 : 3)]; \
  }

read_int32(read_uint32_LE, uint32_t, LE);
read_int32(read_int32_LE, int32_t, LE);
read_int32(read_uint32_BE, uint32_t, BE);
read_int32(read_int32_BE, int32_t, BE);

// TODO: REPLACE the ternery endianness check with some pre-procesor haxs
// to not add checks at runtime!
#define make_write32(name, type, endianness) \
  bool name(byte_array_t *self, type value, size_t offset){ \
    if(offset > self->length) \
    return false; \
    uint8_t *nums = (uint8_t *) self->buffer; \
    nums[offset + (endianness == LE ? 0 : 3)] = value & 0xff ; \
    nums[offset + (endianness == LE ? 1 : 2)] = (value >> 8) & 0xff; \
    nums[offset + (endianness == LE ? 2 : 1)] = (value >> 16) & 0xff; \
    nums[offset + (endianness == LE ? 3 : 0)] = (value >> 24) & 0xff; \
    return true; \
  }

make_write32(write_uint32_LE, uint32_t, LE);
make_write32(write_int32_LE, int32_t, LE);
make_write32(write_uint32_BE, uint32_t, BE);
make_write32(write_int32_BE, int32_t, BE);

// returns -1 on fail
// does not copy the null byte
int write_string(byte_array_t *self, char *str, size_t offset){
  if(offset > self->length){
    return -1;
  }

  char *buf = (char *) self->buffer;
  int i;
  for(i=0;i<strlen(str) && i<self->length; i++){
    buf[offset + i] = str[i];
  }
  return i;
}

// working out how much mem to alocate for read_string
/*0123456*/
/*"hello"*/
/*.....*/
/*min(l - s, e - s) ==  alocate_length*/
/*min(6 - 3, 7 - 3) ==  3*/
/*min(  3  , 4    ) ==  3*/

// returns -1 on fail
// returns num read on success
char *read_string(byte_array_t *self, size_t start, size_t end){
  if(end < start || end > self->length) return NULL;
  char *buf = (char *) self->buffer;
  int length = min( self->length - start, end - start);
  char *result = (char *) GC_MALLOC(( sizeof(char) * length) + 1);
  int i;
  for( i=0; i<length; i++){
    result[i] = buf[i];
  }
  result[i] = '\0';
  return result;
}

char *to_string(byte_array_t *self){
  char *buf = (char *) self->buffer;
  char *result = (char *) GC_MALLOC((sizeof(char) * self->length) + 1);
  int next = 0;
  char c;
  for(int i=0; i<self->length; ++i){
    c = buf[i];
    if(isprint(c) || isspace(c)) result[next++] = c;
  }
  result[next] = '\0';
  return result;
}

#define fill_byte(name, type) \
  void name(byte_array_t *self,  type num){ \
    type *buf = (type*) self->buffer; \
    for(int i=0; i<self->length; i++){ \
      buf[i] = num; \
    } \
  }

fill_byte(fill_uint8, uint8_t);
fill_byte(fill_int8, int8_t);
fill_byte(fill_char, char);

static void add_byte_array_methods(byte_array_t *target){
  // add methods
  add_method(target, read_uint8);
  add_method(target, read_int8);
  add_method(target, write_uint8);
  add_method(target, write_int8);

  add_method(target, read_uint16_LE);
  add_method(target, read_int16_LE);
  add_method(target, read_uint16_BE);
  add_method(target, read_int16_BE);

  add_method(target, write_uint16_LE);
  add_method(target, write_int16_LE);
  add_method(target, write_uint16_BE);
  add_method(target, write_int16_BE);

  add_method(target, read_uint32_LE);
  add_method(target, read_int32_LE);
  add_method(target, read_uint32_BE);
  add_method(target, read_int32_BE);

  add_method(target, write_uint32_LE);
  add_method(target, write_int32_LE);
  add_method(target, write_uint32_BE);
  add_method(target, write_int32_BE);

  add_method(target, write_string);
  add_method(target, read_string);
  add_method(target, to_string);

  add_method(target, fill_uint8);
  add_method(target, fill_int8);
  add_method(target, fill_char);

  add_method(target, slice);
  // return new byte_array_t
}

byte_array_t *slice(byte_array_t *self, size_t start, size_t end){
  if (start > self->length) return NULL;
  byte_array_t *result = (byte_array_t *) GC_MALLOC(sizeof(byte_array_t));
  uint8_t *buf = self->buffer;
  result->buffer =  buf + start;
  result->length = (end > self->length ? self->length - start: end - start); 
  add_byte_array_methods(result);
  return result;
}

byte_array_t *new_byte_array(size_t length){
  // create new byte_array_t
  byte_array_t *result = GC_MALLOC(sizeof(byte_array_t));
  result->buffer = GC_MALLOC(sizeof(uint8_t) * length);
  result->length = length;

  add_byte_array_methods(result);

  return result;
}

byte_array_t *new_byte_array_from_file(FILE *infile){
  fseek(infile, 0, SEEK_END); // jump to end of file
  size_t  length = ftell(infile); // get length
  fseek(infile, 0, SEEK_SET); // go back to begenning of file

  // allocate buffer
  byte_array_t *result = new_byte_array(length);
  
  // read bytes
  fread(result->buffer, length, 1, infile);

  return result;
}
