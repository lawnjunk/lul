#ifndef LUL_FILE_IO
#define LUL_FILE_IO
#include "tools.h"

typedef void (*file_done_cb)(bool failed, void *data);

typedef void (*fs_cb)(uv_fs_t *req);


typedef struct file_context {
  char *path;
  uv_fs_t file_req;
  uv_stat_t statbuf;
  uv_buf_t buf;
  ssize_t file_number;
  file_done_cb done;
  void *result;
  int flags;
  int mode;
  struct action_node *next;
} file_context_t ;

typedef void (*file_action)(file_context_t *ctx);

typedef struct action_node {
  file_action action;
  struct action_node *next; 
} action_node_t;


void file_read_buffer(char *path , file_done_cb);
void file_write_buffer(char *path, buffer_t *buf, file_done_cb cb);

void file_open(file_context_t *ctx);
void file_close(file_context_t *ctx);
void file_fail(file_context_t *ctx);
void file_write(file_context_t *ctx);
void file_fstat(file_context_t *ctx);
void file_read(file_context_t *ctx);


file_context_t *file_context_create();
#endif 
