#include "lerr.h"
#include "buffer.h"

typedef enum {
  LE,
  BE,
} buffer_endian;

/*// type decliations for functions that are used out of order*/
/*buffer_t *slice(buffer_t *self, size_t start, size_t end);*/

// make_read8 creates a functions for reading 8bit
// signed and unsinged ints, at a size_t offset
// return type (type)
#define make_read8(name, type) \
  type name(buffer_t *buf, size_t offset){ \
    if(offset > buf->length -1) {\
      err_trouble_on(buf->err, "access out of bounds");\
    }\
    type *nums = (type *) buf->data; \
    return nums[offset]; \
  }

make_read8(buffer_read_uint8, uint8_t);
make_read8(buffer_read_int8, int8_t);

/*// make_write8 creates functions for writing a signed*/
/*// or unsigned 8bit int, at a size_t offse*/
/*// return type int*/
/*// return false on fail*/
/*// return true on success*/
#define make_write8(name, type) \
  buffer_t *name(buffer_t *buf, type value, size_t offset){ \
    if(err_is_evil(buf->err)) return buf;\
    if(offset > buf->length - 1){\
      err_trouble_on(buf->err, "write attempt out of bounds");\
      return buf;\
    }\
    type *nums = (type *) buf->data; \
    nums[offset] = value; \
    return buf; \
  }

make_write8(buffer_write_uint8, uint8_t);
make_write8(buffer_write_int8, int8_t);

#define make_read16(name, type, endianness) \
  type name(buffer_t *buf, size_t offset){ \
    uint8_t *nums = (uint8_t *) buf->data; \
    if (offset > buf->length - 2){\
      err_trouble_on(buf->err, "access out of bounds");\
      offset = buf->length - 2;\
    }\
    type result; \
    result = (type) nums[offset + (endianness == LE ? 1 : 0)]; \
    result = result << 8; \
    return result | nums[offset + (endianness == LE ? 0 : 1)]; \
  }

make_read16(buffer_read_uint16_LE, uint16_t, LE);
make_read16(buffer_read_int16_LE, int16_t, LE);
make_read16(buffer_read_uint16_BE, uint16_t, BE);
make_read16(buffer_read_int16_BE, int16_t, BE);

#define write_int16(name, type, endianness) \
  buffer_t * name(buffer_t *buf, type value, size_t offset){ \
    if(err_is_evil(buf->err)) return buf;\
    if(offset > buf->length - 2){\
      err_trouble_on(buf->err, "write attempt out of bounds");\
      return buf;\
    }\
    uint8_t *nums = (uint8_t *) buf->data; \
    nums[offset + (endianness == LE ? 0 : 1)] = value & 0xff; \
    nums[offset + (endianness == LE ? 1 : 0)] = value >> 8; \
    return buf;\
  }

write_int16(buffer_write_uint16_LE, uint16_t, LE);
write_int16(buffer_write_int16_LE, int16_t, LE);
write_int16(buffer_write_uint16_BE, uint16_t, BE);
write_int16(buffer_write_int16_BE, int16_t, BE);

#define read_int32(name, type, endianness) \
  type name(buffer_t *self, size_t offset){ \
    uint8_t *nums = (uint8_t *) self->data; \
    if(offset > self->length - 4){\
      err_trouble_on(self->err, "access out of bounds");\
      offset = self->length - 4;\
    }\
    type result =            nums[offset + (endianness == LE ? 3 : 0)]; \
    result = (result << 8) | nums[offset + (endianness == LE ? 2 : 1)]; \
    result = (result << 8) | nums[offset + (endianness == LE ? 1 : 2)]; \
    return   (result << 8) | nums[offset + (endianness == LE ? 0 : 3)]; \
  }

read_int32(buffer_read_uint32_LE, uint32_t, LE);
read_int32(buffer_read_int32_LE, int32_t, LE);
read_int32(buffer_read_uint32_BE, uint32_t, BE);
read_int32(buffer_read_int32_BE, int32_t, BE);

/*// TODO: REPLACE the ternery endianness check with some pre-procesor haxs*/
/*// to not add checks at runtime!*/
#define make_write32(name, type, endianness) \
  buffer_t * name(buffer_t *buf, type value, size_t offset){ \
    if(err_is_evil(buf->err)) return buf;\
    if(offset > buf->length - 4) {\
      err_trouble_on(buf->err, "attempt out of bounds write");\
      return buf;\
    }\
    uint8_t *nums = (uint8_t *) buf->data; \
    nums[offset + (endianness == LE ? 0 : 3)] = value & 0xff ; \
    nums[offset + (endianness == LE ? 1 : 2)] = (value >> 8) & 0xff; \
    nums[offset + (endianness == LE ? 2 : 1)] = (value >> 16) & 0xff; \
    nums[offset + (endianness == LE ? 3 : 0)] = (value >> 24) & 0xff; \
    return buf;\
  }

make_write32(buffer_write_uint32_LE, uint32_t, LE);
make_write32(buffer_write_int32_LE, int32_t, LE);
make_write32(buffer_write_uint32_BE, uint32_t, BE);
make_write32(buffer_write_int32_BE, int32_t, BE);

/*// returns -1 on fail*/
/*// does not copy the null byte*/
/*int write_string(buffer_t *self, char *str, size_t offset){*/
  /*if(offset > self->length){*/
    /*return -1;*/
  /*}*/

  /*char *buf = (char *) self->data;*/
  /*int i;*/
  /*for(i=0;i<strlen(str) && i<self->length; i++){*/
    /*buf[offset + i] = str[i];*/
  /*}*/
  /*return i;*/
/*}*/

/*// working out how much mem to alocate for read_string*/
/*[>0123456<]*/
/*[>"hello"<]*/
/*[>.....<]*/
/*[>min(l - s, e - s) ==  alocate_length<]*/
/*[>min(6 - 3, 7 - 3) ==  3<]*/
/*[>min(  3  , 4    ) ==  3<]*/

/*// returns -1 on fail*/
/*// returns num read on success*/
/*char *read_string(buffer_t *self, size_t start, size_t end){*/
  /*if(end < start || end > self->length) return NULL;*/
  /*char *buf = (char *) self->data;*/
  /*int length = min( self->length - start, end - start);*/
  /*char *result = (char *) GC_MALLOC(( sizeof(char) * length) + 1);*/
  /*int i;*/
  /*for( i=0; i<length; i++){*/
    /*result[i] = buf[i];*/
  /*}*/
  /*result[i] = '\0';*/
  /*return result;*/
/*}*/

/*char *to_string(buffer_t *self){*/
  /*char *buf = (char *) self->data;*/
  /*char *result = (char *) GC_MALLOC((sizeof(char) * self->length) + 1);*/
  /*int next = 0;*/
  /*char c;*/
  /*for(int i=0; i<self->length; ++i){*/
    /*c = buf[i];*/
    /*if(isprint(c) || isspace(c)) result[next++] = c;*/
  /*}*/
  /*result[next] = '\0';*/
  /*return result;*/
/*}*/

#define fill_byte(name, type) \
  buffer_t *name(buffer_t *self,  type num){ \
    if(err_is_evil(self->err)) return self;\
    type *buf = (type*) self->data; \
    for(int i=0; i<self->length; i++){ \
      buf[i] = num; \
    } \
    return self;\
  }

fill_byte(buffer_fill_uint8, uint8_t);
fill_byte(buffer_fill_int8, int8_t);
fill_byte(buffer_fill_char, char);

/*buffer_t *slice(buffer_t *self, size_t start, size_t end){*/
  /*if (start > self->length) return NULL;*/
  /*buffer_t *result = (buffer_t *) GC_MALLOC(sizeof(buffer_t));*/
  /*uint8_t *buf = self->data;*/
  /*result->data =  buf + start;*/
  /*result->length = (end > self->length ? self->length - start: end - start); */
  /*add_buffer_methods(result);*/
  /*return result;*/
/*}*/

buffer_t *buffer_create(size_t length){
  // create new buffer_t
  buffer_t *result = malloc(sizeof(buffer_t));
  result->data = malloc(sizeof(uint8_t) * length);
  result->length = length;
  result->err = err_create("generic buffer error"); // TODO: refacort msgs to macros
  return result;
}

buffer_t *buffer_free(buffer_t *buf){
  free(buf->data);
  free(buf);
  buf = NULL;
  return buf;
}

bool buffer_is_evil(buffer_t *buf){
  return err_is_evil(buf->err);
}

buffer_t *buffer_from_file(FILE *infile){
  fseek(infile, 0, SEEK_END); // jump to end of file
  size_t  length = ftell(infile); // get length
  fseek(infile, 0, SEEK_SET); // go back to begenning of file
  // allocate buffer
  buffer_t *result = buffer_create(length);
  // read bytes
  fread(result->data, length, 1, infile);
  return result;
}
