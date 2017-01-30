#include "test.h"

MU_TEST(buffer_t_test) {
  describe("TEST buffer_create"){
    buffer_t *buf = buffer_create(10);
    should("->length should equal 10", buf->length == 10);
    should("->data should not be NULL", !is_null(buf->data));
    should("->err should not be evil", !flub_is_evil(buf->err));
    should("->err->msg should be 'generic buffer error'",
        eq_str(buf->err->msg, "generic buffer error"))
      l_free(buf, buffer);
  }

  describe("TEST buffer_free"){
    buffer_t *buf = buffer_create(10);
    l_free(buf, buffer);
    should("buf should be null", is_null(buf));
  }

  describe("TEST buffer_from_file"){
    FILE *test_data = fopen("./test/test_data.txt", "r");
    buffer_t *buf = buffer_from_file(test_data);
    should("->length should equal 6", buf->length == 6);
    should("->data should conain 'hello\\n'", (
          (buf->data[0] == 'h') &&
          (buf->data[1] == 'e') &&
          (buf->data[2] == 'l') &&
          (buf->data[3] == 'l') &&
          (buf->data[4] == 'o') &&
          (buf->data[5] == '\n')
          ));
    l_free(buf, buffer);
    fclose(test_data);
  }

  describe("TEST buffer_is_evil"){
    buffer_t *buf = buffer_create(5);
    should("buf should not be evil", !buffer_is_evil(buf));
    flub_trouble_on(buf->err, "bad news");
    should("buf should be evil", buffer_is_evil(buf));
    l_free(buf, buffer);
  }

  describe("TEST buffer_read_uint8"){
    buffer_t *buf = buffer_create(10);
    buf->data[0] = 11;
    buf->data[1] = 22;
    buf->data[2] = 33;

    uint8_t result;
    result = buffer_read_uint8(buf, 0);
    should("shold be 11", result == 11);
    result = buffer_read_uint8(buf, 1);
    should("shold be 22", result == 22);
    result = buffer_read_uint8(buf, 2);
    should("shold be 33", result == 33);
    result = buffer_read_uint8(buf, 3);
    should("shold be 0", result == 0);
    l_free(buf, buffer);
  }

  describe("TEST buffer_read_char"){
    buffer_t *buf = buffer_create(10);
    buf->data[0] = 'a';
    buf->data[1] = 'b';
    buf->data[2] = 'c';

    char result;
    result = buffer_read_char(buf, 0);
    should("shold be 'a'", result == 'a');
    result = buffer_read_char(buf, 1);
    should("shold be 'b'", result == 'b');
    result = buffer_read_char(buf, 2);
    should("shold be 'c'", result == 'c');
    result = buffer_read_char(buf, 3);
    should("shold be 0", result == 0);
    l_free(buf, buffer);
  }

  describe("TEST buffer_read_int8"){
    buffer_t *buf = buffer_create(10);
    buf->data[0] = 11;
    buf->data[1] = 22;
    buf->data[2] = 33;

    int8_t result;
    result = buffer_read_int8(buf, 0);
    should("shold be 11", eq_int8(result,  11));
    result = buffer_read_int8(buf, 1);
    should("shold be 22", eq_int8(result, 22));
    result = buffer_read_int8(buf, 2);
    should("shold be 33", eq_int8(result, 33));
    result = buffer_read_int8(buf, 3);
    should("shold be 0", eq_int8(result, 0));
    l_free(buf, buffer);
  }

  describe("TEST buffer_write_uint8"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_write_uint8(buf, 11, 0);
    should("write 11 at index 0", eq_uint8(buf->data[0], 11));
    should("buffer should not be evil" , !flub_is_evil(buf->err));
    buf = buffer_write_uint8(buf, 22, 2);
    should("write 22 at index 2", eq_uint8(buf->data[2], 22));
    should("buffer should not be evil" , !flub_is_evil(buf->err));
    buf = buffer_write_uint8(buf, 100, 6);
    should("buffer should be evil" , flub_is_evil(buf->err));
    l_free(buf, buffer);
  }

  describe("TEST buffer_write_char"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_write_char(buf,'a' , 0);
    should("write 11 at index 0", eq_char(buf->data[0], 'a'));
    should("buffer should not be evil" , !flub_is_evil(buf->err));
    buf = buffer_write_char(buf, 'b', 2);
    should("write 22 at index 2", eq_char(buf->data[2], 'b'));
    should("buffer should not be evil" , !flub_is_evil(buf->err));
    buf = buffer_write_char(buf, 'c', 6);
    should("buffer should be evil" , flub_is_evil(buf->err));
    l_free(buf, buffer);
  }

  describe("TEST buffer_write_int8"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_write_int8(buf, 11, 0);
    should("write 11 at index 0", eq_int8(buf->data[0], 11));
    should("buffer should not be evil" , !flub_is_evil(buf->err));
    buf = buffer_write_int8(buf, 22, 2);
    should("write 22 at index 2", eq_int8(buf->data[2], 22));
    should("buffer should not be evil" , !flub_is_evil(buf->err));
    buf = buffer_write_int8(buf, 100, 6);
    should("buffer should be evil" , flub_is_evil(buf->err));
    l_free(buf, buffer);
  }

  describe("TESTING buffer_read_uint16_LE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    uint16_t result;
    result = buffer_read_uint16_LE(buf, 0);
    should("result should equal 0xeeff", eq_uint16(result , 0xeeff));
    should("buf should no be evil", !buffer_is_evil(buf));

    result = buffer_read_uint16_LE(buf, 1);
    should("result should equal 0xaaee", eq_uint16(result , 0xaaee));
    should("buf should no be evil", !buffer_is_evil(buf));

    result = buffer_read_int16_LE(buf, 3);
    should("result should equal 0x77dd", eq_uint16(result , 0x77dd));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_uint16_LE(buf, 4);
    should("result should equal 0x77dd", eq_uint16(result , 0x77dd));
    should("buf should be evil", buffer_is_evil(buf));

    l_free(buf, buffer);
  }

  describe("TESTING buffer_read_int16_LE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    int16_t result;
    result = buffer_read_int16_LE(buf, 0);
    should("result should equal 0xeeff", eq_int16(result, 0xeeff));
    should("buf should no be evil", !buffer_is_evil(buf));

    result = buffer_read_int16_LE(buf, 1);
    should("result should equal 0xaaee", eq_int16(result, 0xaaee));
    should("buf should no be evil", !buffer_is_evil(buf));

    result = buffer_read_int16_LE(buf, 3);
    should("result should equal 0x77dd", eq_int16(result, 0x77dd));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_int16_LE(buf, 4);
    should("result should equal 0x77dd", eq_int16(result, 0x77dd));
    should("buf should be evil", buffer_is_evil(buf));

    l_free(buf, buffer);
  }

  describe("TESTING buffer_read_uint16_BE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    uint16_t result;
    result = buffer_read_uint16_BE(buf, 0);
    should("result should equal 0xffee", eq_uint16(result, 0xffee));
    should("buf should no be evil", !buffer_is_evil(buf));

    result = buffer_read_uint16_BE(buf, 1);
    should("result should equal 0xeeaa", eq_uint16(result, 0xeeaa));
    should("buf should no be evil", !buffer_is_evil(buf));

    result = buffer_read_uint16_BE(buf, 3);
    should("result should equal 0xdd77", eq_uint16(result, 0xdd77));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_uint16_BE(buf, 4);
    should("result should equal 0xdd77", eq_uint16(result, 0xdd77));
    should("buf should be evil", buffer_is_evil(buf));

    l_free(buf, buffer);
  }

  describe("TESTING buffer_read_int16_BE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    int16_t result;
    result = buffer_read_int16_BE(buf, 0);
    should("result should equal 0xffee", eq_int16(result, 0xffee));
    should("buf should no be evil", !buffer_is_evil(buf));

    result = buffer_read_int16_BE(buf, 1);
    should("result should equal 0xeeaa", eq_int16(result, 0xeeaa));
    should("buf should no be evil", !buffer_is_evil(buf));

    result = buffer_read_int16_BE(buf, 3);
    should("result should equal 0xdd77", eq_int16(result, 0xdd77));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_int16_BE(buf, 4);
    should("result should equal 0xdd77", eq_int16(result, 0xdd77));
    should("buf should be evil", buffer_is_evil(buf));

    l_free(buf, buffer);
  }

  describe("TEST bufffer_write_uint16_LE"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_write_int16_LE(buf, (uint16_t) 0xffee, 0);
    should("buffer_read_uint16_LE at index 0 should be 0xffee",
        eq_uint16(buffer_read_int16_LE(buf, 0), 0xffee));
    should("buf should not be evil", !buffer_is_evil(buf));

    buf = buffer_write_int16_LE(buf, (uint16_t) 0xaaff, 3);
    should("buffer_read_uint16_LE at index 3 should be 0xaaff",
        eq_uint16(buffer_read_int16_LE(buf, 3), 0xaaff));
    should("buf should not be evil", !buffer_is_evil(buf));

    buf = buffer_write_int16_LE(buf, (uint16_t) 0x0, 4);
    should("buffer_read_uint16_LE at index 3 should be 0xaaff",
        eq_uint16(buffer_read_int16_LE(buf, 3), 0xaaff));
    should("buf should be evil", buffer_is_evil(buf));

    buf = buffer_write_int16_LE(buf, (uint16_t) 0x0, 0);
    should("buffer_read_uint16_LE at index 3 should be 0xaaff",
        eq_uint16(buffer_read_int16_LE(buf, 3), 0xaaff));
    should("buf should be evil", buffer_is_evil(buf));
  }

  describe("TEST buffer_read_uint32_LE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    uint32_t result;
    result = buffer_read_uint32_LE(buf, 0);
    should("result should equal 0xddaaeeff", eq_uint32(result, 0xddaaeeff));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_uint32_LE(buf, 1);
    should("result should equal 0x77ddaaee", eq_uint32(result, 0x77ddaaee));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_uint32_LE(buf, 2);
    should("result should equal 0x77ddaaee", eq_uint32(result, 0x77ddaaee));
    should("buf should be evil", buffer_is_evil(buf));

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_int32_LE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    int32_t result;
    result = buffer_read_int32_LE(buf, 0);
    should("result should equal 0xddaaeeff", eq_int32(result, 0xddaaeeff));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_int32_LE(buf, 1);
    should("result should equal 0x77ddaaee", eq_int32(result, 0x77ddaaee));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_int32_LE(buf, 2);
    should("result should equal 0x77ddaaee", eq_int32(result, 0x77ddaaee));
    should("buf should be evil", buffer_is_evil(buf));

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_uint32_BE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    uint32_t result;
    result = buffer_read_uint32_BE(buf, 0);
    should("result should equal 0xffeeaadd", eq_uint32(result, 0xffeeaadd));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_uint32_BE(buf, 1);
    should("result should equal 0xeeaadd77", eq_uint32(result, 0xeeaadd77));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_uint32_BE(buf, 2);
    should("result should equal 0xeeaadd77", eq_uint32(result, 0xeeaadd77));
    should("buf should be evil", buffer_is_evil(buf));

    l_free(buf, buffer);
  }

  describe("TEST buffer_read_int32_BE"){
    buffer_t *buf = buffer_create(5);
    buf->data[0] = 0xff;
    buf->data[1] = 0xee;
    buf->data[2] = 0xaa;
    buf->data[3] = 0xdd;
    buf->data[4] = 0x77;

    int32_t result;
    result = buffer_read_int32_BE(buf, 0);
    should("result should equal 0xffeeaadd", eq_int32(result, 0xffeeaadd));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_int32_BE(buf, 1);
    should("result should equal 0xeeaadd77", eq_int32(result, 0xeeaadd77));
    should("buf should not be evil", !buffer_is_evil(buf));

    result = buffer_read_int32_BE(buf, 2);
    should("result should equal 0xeeaadd77", eq_int32(result, 0xeeaadd77));
    should("buf should be evil", buffer_is_evil(buf));

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_uint32_LE"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_write_uint32_LE(buf, (uint32_t) 0xaabbccdd, 3);
    should("buf should be evil", buffer_is_evil(buf));
    for(int i=0; i<buf->length; i++){
      should("be zero", eq_uint8(buf->data[i], 0));
    }

    // sould not be able to write in an evil buffer
    buf = buffer_write_uint32_LE(buf, (uint32_t) 0xaabbccdd, 0);
    should("buf should be evil", buffer_is_evil(buf));
    flub_trouble_off(buf->err);

    buf = buffer_write_uint32_LE(buf, (uint32_t) 0xaabbccdd, 0);
    should("buf should not be evil", !buffer_is_evil(buf));
    should("buffer_read_int32_LE(0) should be 0xaabbccdd",
        eq_uint32(buffer_read_uint32_LE(buf, 0), 0xaabbccdd));

    buf = buffer_write_uint32_LE(buf, (uint32_t) 0xaabbccdd, 1);
    should("buf should not be evil", !buffer_is_evil(buf));
    should("buffer_read_int32_LE(1) should be 0xaabbccdd",
        eq_uint32(buffer_read_uint32_LE(buf, 1), 0xaabbccdd));

    buf = buffer_write_uint32_LE(buf, (uint32_t) 0x0, 2);
    should("buf should be evil", buffer_is_evil(buf));
    should("buffer_read_int32_LE(2) should be 0xaabbccdd",
        eq_uint32(buffer_read_uint32_LE(buf, 2), 0xaabbccdd));

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_int32_LE"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_write_int32_LE(buf, (int32_t) 0xaabbccdd, 3);
    should("buf should be evil", buffer_is_evil(buf));
    for(int i=0; i<buf->length; i++){
      should("be zero", eq_int8(buf->data[i], 0));
    }

    // sould not be able to write in an evil buffer
    buf = buffer_write_int32_LE(buf, (int32_t) 0xaabbccdd, 0);
    should("buf should be evil", buffer_is_evil(buf));
    flub_trouble_off(buf->err);

    buf = buffer_write_int32_LE(buf, (int32_t) 0xaabbccdd, 0);
    should("buf should not be evil", !buffer_is_evil(buf));
    should("buffer_read_int32_LE(0) should be 0xaabbccdd",
        eq_int32(buffer_read_int32_LE(buf, 0), 0xaabbccdd));

    buf = buffer_write_int32_LE(buf, (int32_t) 0xaabbccdd, 1);
    should("buf should not be evil", !buffer_is_evil(buf));
    should("buffer_read_int32_LE(1) should be 0xaabbccdd",
        eq_int32(buffer_read_int32_LE(buf, 1), 0xaabbccdd));

    buf = buffer_write_int32_LE(buf, (int32_t) 0x0, 2);
    should("buf should be evil", buffer_is_evil(buf));
    should("buffer_read_int32_LE(2) should be 0xaabbccdd",
        eq_int32(buffer_read_int32_LE(buf, 2), 0xaabbccdd));

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_uint32_BE"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_write_uint32_BE(buf, (uint32_t) 0xaabbccdd, 3);
    should("buf should be evil", buffer_is_evil(buf));
    for(int i=0; i<buf->length; i++){
      should("be zero", eq_uint8(buf->data[i], 0));
    }

    // sould not be able to write in an evil buffer
    buf = buffer_write_uint32_BE(buf, (uint32_t) 0xaabbccdd, 0);
    should("buf should be evil", buffer_is_evil(buf));
    flub_trouble_off(buf->err);

    buf = buffer_write_uint32_BE(buf, (uint32_t) 0xaabbccdd, 0);
    should("buf should not be evil", !buffer_is_evil(buf));
    should("buffer_read_uint32_BE(0) should be 0xaabbccdd",
        eq_uint32(buffer_read_uint32_BE(buf, 0), 0xaabbccdd));

    buf = buffer_write_uint32_BE(buf, (uint32_t) 0xaabbccdd, 1);
    should("buf should not be evil", !buffer_is_evil(buf));
    should("buffer_read_uint32_BE(1) should be 0xaabbccdd",
        eq_uint32(buffer_read_uint32_BE(buf, 1), 0xaabbccdd));

    buf = buffer_write_uint32_BE(buf, (uint32_t) 0x0, 2);
    should("buf should be evil", buffer_is_evil(buf));
    should("buffer_read_uint32_BE(2) should be 0xaabbccdd",
        eq_uint32(buffer_read_uint32_BE(buf, 2), 0xaabbccdd));

    l_free(buf, buffer);
  }

  describe("TEST buffer_write_int32_BE"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_write_int32_BE(buf, (int32_t) 0xaabbccdd, 3);
    should("buf should be evil", buffer_is_evil(buf));
    for(int i=0; i<buf->length; i++){
      should("be zero", eq_int8(buf->data[i], 0));
    }

    // sould not be able to write in an evil buffer
    buf = buffer_write_int32_BE(buf, (int32_t) 0xaabbccdd, 0);
    should("buf should be evil", buffer_is_evil(buf));
    flub_trouble_off(buf->err);

    buf = buffer_write_int32_BE(buf, (int32_t) 0xaabbccdd, 0);
    should("buf should not be evil", !buffer_is_evil(buf));
    should("buffer_read_int32_BE(0) should be 0xaabbccdd",
        eq_int32(buffer_read_int32_BE(buf, 0), 0xaabbccdd));

    buf = buffer_write_int32_BE(buf, (int32_t) 0xaabbccdd, 1);
    should("buf should not be evil", !buffer_is_evil(buf));
    should("buffer_read_int32_BE(1) should be 0xaabbccdd",
        eq_int32(buffer_read_int32_BE(buf, 1), 0xaabbccdd));

    buf = buffer_write_int32_BE(buf, (int32_t) 0x0, 2);
    should("buf should be evil", buffer_is_evil(buf));
    should("buffer_read_int32_BE(2) should be 0xaabbccdd",
        eq_int32(buffer_read_int32_BE(buf, 2), 0xaabbccdd));

    l_free(buf, buffer);
  }

  describe("TEST buffer_fill_uint8"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_fill_uint8(buf, (uint8_t) 0xfa);
    for(int i=0; i<buf->length; i++){
      should("buf at index should be 0xfa", eq_uint8(buf->data[i], 0xfa));
    }

    // sholdnt be able to over write if buffer is dirty
    flub_trouble_on(buf->err, "ut oh");
    buf = buffer_fill_uint8(buf, (uint8_t) 0x00);
    for(int i=0; i<buf->length; i++){
      should("buf at index should be 0xfa", eq_uint8(buf->data[i], 0xfa));
    }
    l_free(buf, buffer);
  }

  describe("TEST buffer_fill_int8"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_fill_int8(buf, (int8_t) 0xfa);
    for(int i=0; i<buf->length; i++){
      should("buf at index should be 0xfa", eq_int8(buf->data[i], 0xfa));
    }

    // sholdnt be able to over write if buffer is dirty
    flub_trouble_on(buf->err, "ut oh");
    buf = buffer_fill_int8(buf, (int8_t) 0x00);
    for(int i=0; i<buf->length; i++){
      should("buf at index should be 0xfa", eq_int8(buf->data[i], 0xfa));
    }
    l_free(buf, buffer);
  }

  describe("TEST buffer_fill_char"){
    buffer_t *buf = buffer_create(5);
    buf = buffer_fill_char(buf, 'a');
    for(int i=0; i<buf->length; i++){
      should("buf at index should be 0xfa", eq_char(buf->data[i], 'a'));
    }

    // sholdnt be able to over write if buffer is dirty
    flub_trouble_on(buf->err, "ut oh");
    buf = buffer_fill_char(buf, 'b');
    for(int i=0; i<buf->length; i++){
      should("buf at index should be 0xfa", eq_char(buf->data[i], 'a'));
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
    should("slice should have a length of 3", eq_size(slice->length, 3));
    should("slice at 0 should be 0xcc", eq_uint8(slice->data[0], 0xcc));
    should("slice at 1 should be 0xdd", eq_uint8(slice->data[1], 0xdd));
    should("slice at 2 should be 0xee", eq_uint8(slice->data[2], 0xee));

    slice = buffer_write_uint8(slice, 0x3, 0);
    should("slice at 0 should be 0x3", eq_uint8(slice->data[0], 0x3));
    should("buf at 2 should be 0x3", eq_uint8(buf->data[2], 0x3));

    flub_trouble_on(buf->err, "bad news");
    buffer_t *evil_slice = buffer_slice(buf, 0, 4);
    should("be an evil buffer", buffer_is_evil(evil_slice));
    should("have a length of 0", eq_size(evil_slice->length, 0));

    buffer_t *evil_start = buffer_slice(buf, 15, 16);
    should("be an evil buffer", buffer_is_evil(evil_start));
    should("have a length of 0", eq_size(evil_start->length, 0));

    buffer_t *evil_end = buffer_slice(buf, 2, 1);
    should("be an evil buffer", buffer_is_evil(evil_end));
    should("have a length of 0", eq_size(evil_start->length, 0));

    l_free(evil_start, buffer);
    l_free(evil_slice, buffer);
    l_free(evil_end, buffer);
    l_free(slice, buffer);
    l_free(buf, buffer);
  }

  describe("TEST buffer_write_buffer"){
    buffer_t *dest = buffer_create(8);
    buffer_t *src = buffer_create(4);
    buffer_write_uint32_BE(src, 0xaabbccdd, 0);
    dest = buffer_write_buffer(dest, src, 4, src->length);
    should("dest[4] should be 0xaa",
        eq_uint8(buffer_read_uint8(dest, 4), 0xaa));
    should("dest[5] should be 0xbb",
        eq_uint8(buffer_read_uint8(dest, 5), 0xbb));
    should("dest[6] should be 0xcc",
        eq_uint8(buffer_read_uint8(dest, 6), 0xcc));
    should("dest[7] should be 0xdd",
        eq_uint8(buffer_read_uint8(dest, 7), 0xdd));

    flub_trouble_on(dest->err, "for testing");
    dest = buffer_write_buffer(dest, src, 0, src->length);
    for(int i=0; i<4; i++){
      should("dest->data at index should be 0x0",
          eq_uint8(buffer_read_uint8(dest, i), 0x0));
    }
    should("dest should be evil", buffer_is_evil(dest));
    flub_trouble_off(dest->err);

    flub_trouble_on(src->err, "for testing");
    dest = buffer_write_buffer(dest, src, 0, src->length);
    for(int i=0; i<4; i++){
      should("dest->data at index should be 0x0",
          eq_uint8(buffer_read_uint8(dest, i), 0x0));
    }

    should("dest should be evil", buffer_is_evil(dest));
    flub_trouble_off(dest->err);
    flub_trouble_off(src->err);

    dest = buffer_write_buffer(dest, src, 5, src->length);
    should("dest should be evil", buffer_is_evil(dest));
    should("dest[5] should be 0xbb",
        eq_uint8(buffer_read_uint8(dest, 5), 0xbb));
    should("dest[6] should be 0xcc",
        eq_uint8(buffer_read_uint8(dest, 6), 0xcc));
    should("dest[7] should be 0xdd",
        eq_uint8(buffer_read_uint8(dest, 7), 0xdd));

    l_free(dest, buffer);
    l_free(src, buffer);
  }

  describe("TEST buffer_from_char_array"){
    buffer_t *buf = buffer_from_char_array("lulwat");
    should("have a length of six", eq_size(buf->length, 6));
    char *data = "lulwat";
    for(int i=0;i<6;i++){
      should("have the right data at index",
          eq_char(buffer_read_uint8(buf, i), data[i]));
    }
  }

  describe("TEST buffer_from_int8_array"){
    buffer_t *buf = buffer_from_int8_array((int8_t []) {0, 1, 2, 3}, 4);
    should("buf should have a length of 4", eq_size(buf->length, 4));
    for(int i=0;i<4;i++){
      should("have the right data at index",
          eq_char(buffer_read_uint8(buf, i), i));
    }
  }

  describe("TEST buffer_from_uint8_array"){
    buffer_t *buf = buffer_from_uint8_array((uint8_t []) {0, 1, 2, 3}, 4);
    should("buf should have a length of 4", eq_size(buf->length, 4));
    for(int i=0;i<4;i++){
      should("have the right data at index",
          eq_char(buffer_read_uint8(buf, i), i));
    }
  }
}

