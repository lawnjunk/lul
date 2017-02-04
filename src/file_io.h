#ifndef LUL_FILE_IO
#define LUL_FILE_IO
#include "tools.h"

// callbacks result
typedef struct {
  void *result;
  bool failure;
} arg_t;

typedef void (*file_done_cb)(arg_t *arg);
typedef void (*file_read_buffer_cb)(buffer_t *data);
typedef void (*file_write_buffer_cb)(flub_t *flub);

typedef struct file_context {
  uv_fs_t file_req;
  uv_stat_t statbuf;
  ssize_t file_id;
  uv_buf_t buf;
  file_read_buffer_cb file_read_buffer_done;
  file_write_buffer_cb file_write_buffer_done;
} file_context_t ;

void file_read_buffer(char *path , file_read_buffer_cb cb);
void file_write_buffer(char *path, buffer_t *buf, file_write_buffer_cb cb);

#endif 
