#include "test.h"

MU_TEST(buffer_t_test) {
  describe("TEST buffer_create"){
    it("should create a buffer"){
      buffer_t *buf = buffer_create(10);
      ok(buf->length, eq_size, 10);
      check(buf->data, !is_null);
      check(buf, !buffer_is_evil);
      ok(buf->err->msg, eq_str, "generic buffer error");
      l_free(buf, buffer);
    }
  }

  describe("TEST buffer_free"){
    it("the buf should be null affter freeing it"){
      buffer_t *buf = buffer_create(10);
      l_free(buf, buffer);
      check(buf, is_null);
    }
  }

  describe("TEST buffer_from_file"){

    it("should fill a buffer with the data from a file at a file path"){
      FILE *test_data = fopen("./test/test_data.txt", "r");
      buffer_t *buf = buffer_from_file(test_data);
      ok(buf->length, eq_size, 6);
      ok(buf->data[0], eq_char, 'h');
      ok(buf->data[1], eq_char, 'e');
      ok(buf->data[2], eq_char, 'l');
      ok(buf->data[3], eq_char, 'l');
      ok(buf->data[4], eq_char, 'o');
      ok(buf->data[5], eq_char, '\n');
      check(buf, !buffer_is_evil);
      l_free(buf, buffer);
      fclose(test_data);
    }

  }

  describe("TEST buffer_is_evil"){
    buffer_t *buf = buffer_create(5);
    it("should return false if buf->err->trouble == false"){
      check(buf, !buffer_is_evil);
    }

    it("should return true if buf->err->trouble == true"){
      flub_trouble_on(buf->err, "bad news");
      check(buf, buffer_is_evil);
    }

    it("buffer_is_evil should return true if buf is NULL"){
      check(NULL, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_uint8"){
    buffer_t *buf = buffer_create(10);
    buf->data[0] = 11;
    buf->data[1] = 22;
    buf->data[2] = 33;

    it("should retrun the correct int for a given offset"){
      ok(buffer_read_uint8(buf, 0), eq_uint8, 11);
      ok(buffer_read_uint8(buf, 1), eq_uint8, 22);
      ok(buffer_read_uint8(buf, 2), eq_uint8, 33);
      ok(buffer_read_uint8(buf, 3), eq_uint8, 0);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_char"){
    buffer_t *buf = buffer_create(10);
    buf->data[0] = 'a';
    buf->data[1] = 'b';
    buf->data[2] = 'c';

    it("should retrun the correct char for a given offset"){
      ok(buffer_read_char(buf, 0), eq_char, 'a');
      ok(buffer_read_char(buf, 1), eq_char, 'b');
      ok(buffer_read_char(buf, 2), eq_char, 'c');
      ok(buffer_read_char(buf, 3), eq_char, 0);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_int8"){
    buffer_t *buf = buffer_create(10);
    buf->data[0] = 11;
    buf->data[1] = 22;
    buf->data[2] = 33;

    it("should retrun the correct int for a given offset"){
      ok(buffer_read_int8(buf, 0), eq_int8, 11);
      ok(buffer_read_int8(buf, 1), eq_int8, 22);
      ok(buffer_read_int8(buf, 2), eq_int8, 33);
      ok(buffer_read_int8(buf, 3), eq_int8, 0);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_uint8"){
    buffer_t *buf = buffer_create(5);

    it("should write a uint to the correct offset"){
      buf = buffer_write_uint8(buf, 11, 0);
      ok(buf->data[0], eq_uint8, 11);
      buf = buffer_write_uint8(buf, 22, 2);
      ok(buf->data[2], eq_uint8, 22);
      check(buf, !buffer_is_evil);
    }

    it("should return an evil buf on out of bounds write"){
      buf = buffer_write_uint8(buf, 100, 6);
      check(buf, buffer_is_evil);
    }
    l_free(buf, buffer);
  }

  describe("TEST buffer_write_char"){
    buffer_t *buf = buffer_create(5);
    it("should write a char to the correct offset"){
      buf = buffer_write_char(buf, 'a', 0);
      ok(buf->data[0], eq_char, 'a');
      buf = buffer_write_char(buf,'b', 2);
      ok(buf->data[2], eq_char, 'b');
      check(buf, !buffer_is_evil);
    }

    it("should return an evil buf on write to buf->length"){
      buf = buffer_write_char(buf, 'c', 5);
      check(buf, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_int8"){
    buffer_t *buf = buffer_create(5);

    it("should write a int to the correct offset"){
      buf = buffer_write_int8(buf, 11, 0);
      ok(buf->data[0], eq_int8, 11);
      buf = buffer_write_int8(buf, 22, 2);
      ok(buf->data[2], eq_int8, 22);
      check(buf, !buffer_is_evil);
    }

    it("should return an evil buf on out of bounds write"){
      buf = buffer_write_int8(buf, 100, 6);
      check(buf, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TESTING buffer_read_uint16_LE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    it("should return the correct LE number"){
      ok(buffer_read_uint16_LE(buf, 0), eq_uint16, 0xeeff);
      ok(buffer_read_uint16_LE(buf, 1), eq_uint16, 0xaaee);
      ok(buffer_read_uint16_LE(buf, 3), eq_uint16, 0x77dd);
      ok(buffer_read_uint16_LE(buf, 4), eq_uint16, 0x77dd);
    }

    l_free(buf, buffer);
  }

  describe("TESTING buffer_read_int16_LE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    it("should return the correct LE number"){
      ok(buffer_read_int16_LE(buf, 0), eq_int16, 0xeeff);
      ok(buffer_read_int16_LE(buf, 1), eq_int16, 0xaaee);
      ok(buffer_read_int16_LE(buf, 3), eq_int16, 0x77dd);
      check(buf, !buffer_is_evil);
    }

    it("buffer should be evil on read out of bounds"){
      ok(buffer_read_int16_LE(buf, 4), eq_int16, 0x77dd);
      check(buf, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TESTING buffer_read_uint16_BE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    it("should return the correct BE number"){
      ok(buffer_read_uint16_BE(buf, 0), eq_uint16, 0xffee);
      ok(buffer_read_uint16_BE(buf, 1), eq_uint16, 0xeeaa);
      ok(buffer_read_uint16_BE(buf, 3), eq_uint16, 0xdd77);
      check(buf, !buffer_is_evil);
    }

    it("buffer should be evil on read out of bounds"){
      ok(buffer_read_uint16_BE(buf, 4), eq_uint16, 0xdd77);
      check(buf, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TESTING buffer_read_int16_BE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    it("should return the correct BE number"){
      ok(buffer_read_int16_BE(buf, 0), eq_int16, 0xffee);
      ok(buffer_read_int16_BE(buf, 1), eq_int16, 0xeeaa);
      ok(buffer_read_int16_BE(buf, 3), eq_int16, 0xdd77);
      check(buf, !buffer_is_evil);
    }

    it("buffer should be evil on read out of bounds"){
      ok(buffer_read_int16_BE(buf, 4), eq_int16, 0xdd77);
      check(buf, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TEST bufffer_write_uint16_LE"){
    buffer_t *buf = buffer_create(5);
    it("should write int16 to valid offset"){
      buf = buffer_write_int16_LE(buf, (uint16_t) 0xffee, 0);
      ok(buffer_read_uint16_LE(buf, 0), eq_uint16, 0xffee);
      buf = buffer_write_int16_LE(buf, (uint16_t) 0xaaff, 3);
      ok(buffer_read_uint16_LE(buf, 3), eq_uint16, 0xaaff);
      check(buf, !buffer_is_evil);
    }

    it("return evil buffer on write to invalid offset"){
      buf = buffer_write_int16_LE(buf, (uint16_t) 0x0, 4);
      check(buf, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_uint32_LE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    it("should write uint16 to valid offset"){
      buf = buffer_write_uint32_LE(buf, (uint32_t) 0xffee, 0);
      ok(buffer_read_uint32_LE(buf, 0), eq_uint32, 0xffee);
      buf = buffer_write_uint32_LE(buf, (uint32_t) 0xaabbccdd, 1);
      ok(buffer_read_uint32_LE(buf, 1), eq_uint32, 0xaabbccdd);
      check(buf, !buffer_is_evil);
    }

    it("return evil buffer on write to invalid offset"){
      buffer_fill_uint8(buf, 0);
      buf = buffer_write_uint32_LE(buf, (uint32_t) 0xaabbccdd, 2);
      check(buf, buffer_is_evil);
      ok(buffer_read_uint32_LE(buf, 0), eq_uint32, 0);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_int32_LE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    it("should return the correct LE number"){
      ok(buffer_read_int32_LE(buf, 0), eq_int16, 0xddaaeeff);
      ok(buffer_read_int32_LE(buf, 1), eq_int16, 0x77ddaaee);
      check(buf, !buffer_is_evil);
    }

    it("buffer should be evil on read out of bounds"){
      ok(buffer_read_int32_LE(buf, 2), eq_int16, 0x77ddaaee);
      check(buf, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_uint32_BE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    it("should return the correct BE number"){
      ok(buffer_read_uint32_BE(buf, 0), eq_uint16, 0xffeeaadd);
      ok(buffer_read_uint32_BE(buf, 1), eq_uint16, 0xeeaadd77);
      check(buf, !buffer_is_evil);
    }

    it("buffer should be evil on read out of bounds"){
      ok(buffer_read_uint32_BE(buf, 2), eq_uint16, 0xeeaadd77);
      check(buf, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_int32_BE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    it("should return the correct BE number"){
      ok(buffer_read_int32_BE(buf, 0), eq_int16, 0xffeeaadd);
      ok(buffer_read_int32_BE(buf, 1), eq_int16, 0xeeaadd77);
      check(buf, !buffer_is_evil);
    }

    it("buffer should be evil on read out of bounds"){
      ok(buffer_read_int32_BE(buf, 2), eq_int16, 0xeeaadd77);
      check(buf, buffer_is_evil);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_uint32_LE"){
    buffer_t *buf = buffer_create(5);

    it("should write to a vaild offset"){
      buf = buffer_write_uint32_LE(buf, 0xaabbccdd, 0);
      ok(buffer_read_uint32_LE(buf, 0), eq_uint32, 0xaabbccdd);
      buf = buffer_write_uint32_LE(buf, 0xaabbccdd, 1);
      ok(buffer_read_uint32_LE(buf, 1), eq_uint32, 0xaabbccdd);
      check(buf, !buffer_is_evil);
    }

    it("should return an evil buf on write to invalid offset"){
      buffer_fill_uint8(buf, 0);
      buffer_write_uint32_LE(buf, (uint32_t)  0xaabbccdd, 2);
      ok(buffer_read_uint8(buf, 4), eq_uint32, 0);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_int32_LE"){
    buffer_t *buf = buffer_create(5);

    it("should write to a vaild offset"){
      buf = buffer_write_int32_LE(buf, 0xaabbccdd, 0);
      ok(buffer_read_int32_LE(buf, 0), eq_int32, 0xaabbccdd);
      buf = buffer_write_int32_LE(buf, 0xaabbccdd, 1);
      ok(buffer_read_int32_LE(buf, 1), eq_int32, 0xaabbccdd);
      check(buf, !buffer_is_evil);
    }

    it("should return an evil buf on write to invalid offset"){
      buffer_fill_uint8(buf, 0);
      buffer_write_int32_LE(buf, (int32_t)  0xaabbccdd, 2);
      ok(buffer_read_uint8(buf, 4), eq_int32, 0);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_int32_BE"){
    buffer_t *buf = buffer_create(5);

    it("should write to a vaild offset"){
      buf = buffer_write_int32_BE(buf, 0xaabbccdd, 0);
      ok(buffer_read_int32_BE(buf, 0), eq_int32, 0xaabbccdd);
      buf = buffer_write_int32_BE(buf, 0xaabbccdd, 1);
      ok(buffer_read_int32_BE(buf, 1), eq_int32, 0xaabbccdd);
      check(buf, !buffer_is_evil);
    }

    it("should return an evil buf on write to invalid offset"){
      buffer_fill_uint8(buf, 0);
      buffer_write_int32_BE(buf, (int32_t)  0xaabbccdd, 2);
      ok(buffer_read_uint8(buf, 4), eq_int32, 0);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_uint32_BE"){
    buffer_t *buf = buffer_create(5);

    it("should write to a vaild offset"){
      buf = buffer_write_uint32_BE(buf, 0xaabbccdd, 0);
      ok(buffer_read_uint32_BE(buf, 0), eq_int32, 0xaabbccdd);
      buf = buffer_write_uint32_BE(buf, 0xaabbccdd, 1);
      ok(buffer_read_uint32_BE(buf, 1), eq_int32, 0xaabbccdd);
      check(buf, !buffer_is_evil);
    }

    it("should return an evil buf on write to invalid offset"){
      buffer_fill_uint8(buf, 0);
      buffer_write_uint32_BE(buf, (int32_t)  0xaabbccdd, 2);
      ok(buffer_read_uint8(buf, 4), eq_uint32, 0);
    }

    l_free(buf, buffer);
  }

  describe("TEST buffer_fill_uint8"){
    buffer_t *buf = buffer_create(5);
    it("should fill a non evil buffer"){
      buf = buffer_fill_uint8(buf, (uint8_t) 0xfa);
      for(int i=0; i<buf->length; i++){
        ok(buf->data[i], eq_uint8,  0xfa);
      }
    }

    // sholdnt be able to over write if buffer is dirty
    it("should not write to an evil buffer"){
      buffer_trouble_on(buf, "ut oh");
      buf = buffer_fill_uint8(buf, (uint8_t) 0x00);
      for(int i=0; i<buf->length; i++){
        ok(buf->data[i], eq_uint8,  0xfa);
      }
    }
    l_free(buf, buffer);
  }

  describe("TEST buffer_fill_int8"){
    buffer_t *buf = buffer_create(5);
    it("should fill a non evil buffer"){
      buf = buffer_fill_int8(buf, (int8_t) 0xfa);
      for(int i=0; i<buf->length; i++){
        ok(buf->data[i], eq_int8,  0xfa);
      }
    }

    // sholdnt be able to over write if buffer is dirty
    it("should not fill an evil buffer"){
      flub_trouble_on(buf->err, "ut oh");
      buf = buffer_fill_int8(buf, (int8_t) 0x00);
      for(int i=0; i<buf->length; i++){
        ok(buf->data[i], eq_int8,  0xfa);
      }
    }
    l_free(buf, buffer);
  }

  describe("TEST buffer_fill_char"){
    buffer_t *buf = buffer_create(5);
    it("should fill a non evil buffer"){
      buf = buffer_fill_char(buf, 'a');
      for(int i=0; i<buf->length; i++){
        ok(buf->data[i], eq_char,  'a');
      }
    }

    it("should not fill an evil buffer"){
      flub_trouble_on(buf->err, "ut oh");
      buf = buffer_fill_char(buf, '\0');
      for(int i=0; i<buf->length; i++){
        ok(buf->data[i], eq_char,  'a');
      }
    }
    l_free(buf, buffer);
  }

  describe("TEST buffer_slice"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xaa;
    buf->data[1] = 0xbb;
    buf->data[2] = 0xcc;
    buf->data[3] = 0xdd;
    buf->data[4] = 0xee;
    buffer_t *slice = buffer_slice(buf, 2, 5);

    it("should create a slice with valid offset"){
      ok(slice->length, eq_size, 3);
      ok(slice->data[0], eq_uint8, 0xcc);
      ok(slice->data[1], eq_uint8, 0xdd);
      ok(slice->data[2], eq_uint8, 0xee);

      slice = buffer_write_uint8(slice, 0x3, 0);
      ok(slice->data[0], eq_uint8, 0x3);
      ok(buf->data[2], eq_uint8, 0x3);
    }

    it("should not create a slice from an evil buffer"){
      flub_trouble_on(buf->err, "bad news");
      buffer_t *evil_slice = buffer_slice(buf, 0, 4);
      check(evil_slice, buffer_is_evil);
      ok(evil_slice->length, eq_size, 0);

      buffer_t *evil_start = buffer_slice(buf, 15, 16);
      check(evil_slice, buffer_is_evil);
      ok(evil_start->length, eq_size, 0);

      buffer_t *evil_end = buffer_slice(buf, 2, 1);
      check(buf, buffer_is_evil);
      ok(evil_start->length, eq_size, 0);
      l_free(evil_start, buffer);
      l_free(evil_slice, buffer);
      l_free(evil_end, buffer);
    }

    l_free(slice, buffer);
    l_free(buf, buffer);
  }

  describe("TEST buffer_write_buffer"){
    buffer_t *dest = buffer_create(8);
    buffer_t *src = buffer_create(5);

    it("should write data with valid offsets and count"){
      buffer_fill_uint8(dest, 0);
      buffer_write_uint32_BE(src, 0xaabbccdd, 1);
      dest = buffer_write_buffer(dest, src, 4, 1, 3);
      check(dest, !buffer_is_evil);
      ok(buffer_read_uint8(dest, 4), eq_uint8, 0xaa);
      ok(buffer_read_uint8(dest, 5), eq_uint8, 0xbb);
      ok(buffer_read_uint8(dest, 6), eq_uint8, 0xcc);
      ok(buffer_read_uint8(dest, 7), eq_uint8, 0x00);
    }

    it("should return evil buf when doffset invalid"){
      flub_trouble_off(dest->err);
      buffer_fill_uint8(dest, 0);
      buffer_fill_uint8(src, 0);
      buffer_write_uint32_BE(src, 0xaabbccdd, 1);
      dest = buffer_write_buffer(dest, src, 5, 1, 4);

      check(dest, buffer_is_evil);
      ok(buffer_read_uint8(dest, 4), eq_uint8, 0);
      ok(buffer_read_uint8(dest, 5), eq_uint8, 0);
      ok(buffer_read_uint8(dest, 6), eq_uint8, 0);
      ok(buffer_read_uint8(dest, 7), eq_uint8, 0);

    }

    it("should return evil buf when doffset invalid"){
      flub_trouble_off(dest->err);
      buffer_fill_uint8(dest, 0);
      buffer_fill_uint8(src, 0);
      buffer_write_uint32_BE(src, 0xaabbccdd, 1);
      dest = buffer_write_buffer(dest, src, 4, 3, 4);
      check(dest, buffer_is_evil);
      ok(buffer_read_uint8(dest, 4), eq_uint8, 0);
      ok(buffer_read_uint8(dest, 5), eq_uint8, 0);
      ok(buffer_read_uint8(dest, 6), eq_uint8, 0);
      ok(buffer_read_uint8(dest, 7), eq_uint8, 0);
    }

    it("should not write to an evil buffer"){
      flub_trouble_off(dest->err);
      buffer_fill_uint8(dest, 0);
      buffer_trouble_on(dest, "for testing");
      dest = buffer_write_buffer(dest, src, 0, 0, src->length);
      for(int i=0; i<4; i++){
        ok(buffer_read_uint8(dest, i), eq_uint8, 0);
      }
      flub_trouble_off(dest->err);
    }

    l_free(dest, buffer);
    l_free(src, buffer);
  }

  describe("TEST buffer_from_char_array"){
    char *data = "lulwat";
    buffer_t *buf = buffer_from_char_array(data);

    it("should fill the buffer with 'lulwat'"){
      ok(buf->length, eq_size, 6);
      range(i, 0, 6) {
        ok(buffer_read_char(buf, i), eq_char, data[i]);
      }
    }
    l_free(buf, buffer);
  }

  describe("TEST buffer_from_int8_array"){
    int8_t *data = (int8_t []) {0, 1, 2, 3};
    buffer_t *buf = buffer_from_int8_array(data, 4);

    it("should fill the buffer with '[0, 1, 2, 3]"){
      ok(buf->length, eq_size, 4);
      range(i, 0, 4) {
        ok(buffer_read_int8(buf, i), eq_int8, data[i]);
      }
    }
    l_free(buf, buffer);
  }

  describe("TEST buffer_from_uint8_array"){
    uint8_t *data = (uint8_t []) {0, 1, 2, 3};
    buffer_t *buf = buffer_from_uint8_array(data, 4);
    it("should fill the buffer with '[0, 1, 2, 3]"){
      ok(buf->length, eq_size, 4);
      range(i, 0, 4) {
        ok(buffer_read_uint8(buf, i), eq_uint8, data[i]);
      }
    }
  }
}

