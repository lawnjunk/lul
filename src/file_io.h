#ifndef LUL_FILE_IO
#define LUL_FILE_IO
#include "tools.h"

typedef void (*buffer_cb)(buffer_t *data);

typedef struct file_context {
  uv_fs_t open_req;
  uv_fs_t close_req;
  uv_fs_t read_req;
  uv_fs_t fstat_req;
  uv_buf_t *buf;
  buffer_cb done;
} file_context_t ;

void file_read_buffer(char *path , buffer_cb cb);

#endif 

