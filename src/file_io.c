#include "tools.h"

#define fs_result_is_evil(req) (req->result < 0)

static void file_on_open(uv_fs_t *);
static void file_on_read(uv_fs_t *);
static void file_on_close(uv_fs_t *);
static void file_on_fstat(uv_fs_t *);
static void file_on_fail(uv_fs_t *);
static file_context_t *file_context_create(void);
static file_context_t *file_context_free(file_context_t *ctx);

void file_read_buffer(char *path, buffer_cb cb){
  file_context_t *ctx = file_context_create();
  ctx->done = cb;
  
  int wat = uv_fs_open(uv_default_loop(), &ctx->open_req, path, O_RDONLY, S_IRUSR, file_on_open);
  printf("WAT %d ", wat);
}


void file_on_fail(uv_fs_t *req){
  file_context_t *ctx = (file_context_t *) req->data;
  file_context_free(ctx);
  ctx->done(NULL);
};


void file_on_open(uv_fs_t *req){
  if(fs_result_is_evil(req)){
    file_on_fail(req);
    return;
  }
 
  file_context_t *ctx = (file_context_t *) req->data;
  uv_fs_fstat(uv_default_loop(), &ctx->fstat_req, req->result, file_on_fstat);
}

void file_on_fstat(uv_fs_t *req){
  if(fs_result_is_evil(req)){
    file_on_fail(req);
    return;
  }

  file_context_t *ctx = (file_context_t *) req->data;

  size_t buf_len = sizeof(char) * req->statbuf.st_size;
  char *buf = malloc(buf_len);
  uv_buf_t iov = uv_buf_init(buf, buf_len);
  ctx->done(buffer_create(iov.len));
}

void file_on_read(uv_fs_t *req){
  if(fs_result_is_evil(req)){
    file_on_fail(req);
    return;
  }
  file_context_t *ctx = (file_context_t *) req->data;
  uv_buf_t *iov = ctx->read_req.bufs;
}

void file_on_close(uv_fs_t *req){
  if(fs_result_is_evil(req)){
    file_on_fail(req);
    return;
  }

  file_context_t *ctx = (file_context_t *) req->data;
  uv_buf_t *iov = ctx->read_req.bufs;
  ctx->done(buffer_create(iov->len));
  file_context_free(ctx);
}

file_context_t *file_context_create(){
  file_context_t *result = malloc(sizeof(file_context_t));
  result->open_req.data = result;
  result->fstat_req.data = result;
  result->read_req.data = result;
  result->close_req.data = result;
  return result;
}

file_context_t *file_context_free(file_context_t *ctx){
  uv_fs_req_cleanup(&ctx->open_req);
  uv_fs_req_cleanup(&ctx->fstat_req);
  uv_fs_req_cleanup(&ctx->read_req);
  uv_fs_req_cleanup(&ctx->close_req);
  free(ctx);
  ctx = NULL;
  return ctx;
}
