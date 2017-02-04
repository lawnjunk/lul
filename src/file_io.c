#include "tools.h"

#define fs_result_is_evil(req) (req->result < 0)

static void file_read_buffer_open(uv_fs_t *);
static void file_read_buffer_fstat(uv_fs_t *);
static void file_read_buffer_read(uv_fs_t *);
static void file_read_buffer_fail(uv_fs_t *);
static void file_read_buffer_close(uv_fs_t *);
static void file_write_buffer_on_open(uv_fs_t *);
static void file_write_buffer_on_write(uv_fs_t *);
static void file_write_buffer_on_fail(uv_fs_t *);
static void file_write_buffer_on_close(uv_fs_t *);
static file_context_t *file_context_create(void);
static file_context_t *file_context_free(file_context_t *ctx);

#define req_get_ctx(req, name)\
  file_context_t *name = (file_context_t *) req->data;

void file_write_buffer(char *path, buffer_t *buf, file_write_buffer_cb cb){
  puts("hit file_write_buffer");
  file_context_t *ctx = file_context_create();
  ctx->file_write_buffer_done = cb;
  ctx->buf = uv_buf_init("hello", 5);
  puts(path);
  uv_fs_open(uv_default_loop(), &ctx->file_req, path, O_RDWR | O_CREAT, 0640, file_write_buffer_on_open);
}

void file_write_buffer_on_open(uv_fs_t *req){
  printf("hit file_write_buffer_on_open %lu\n", req->result);
  if(req->result < 0 ){
    puts("FUUBAR");
    file_write_buffer_on_fail(req);
    return;
  }
  
  req_get_ctx(req, ctx);
  uv_fs_req_cleanup(req);
  uv_fs_write(uv_default_loop(), &ctx->file_req, ctx->file_id, &ctx->buf, 1, 0, file_write_buffer_on_write);
}

void file_write_buffer_on_write(uv_fs_t *req){
  puts("hit file_write_buffer_on_write");
  if(fs_result_is_evil(req)){
    file_write_buffer_on_fail(req);
    return;
  }

  req_get_ctx(req, ctx);
  ctx->file_write_buffer_done(flub_create("no bugz"));
  uv_fs_close(uv_default_loop(), &ctx->file_req, ctx->file_id, file_write_buffer_on_close);

  uv_fs_req_cleanup(req);
  file_context_free(ctx);
}

void file_write_buffer_on_close(uv_fs_t *req){
  puts("hit file_write_buffer_on_close");
  req_get_ctx(req, ctx);
  ctx->file_write_buffer_done(flub_create(""));
  uv_fs_req_cleanup(req);
  file_context_free(ctx);
};

void file_write_buffer_on_fail(uv_fs_t *req){
  puts("hit file_write_buffer_on_fail");
  puts("hit file_write_buffer_fail");
  req_get_ctx(req, ctx);
  ctx->file_write_buffer_done(NULL);
  uv_fs_req_cleanup(req);
  file_context_free(ctx);
};

void file_read_buffer(char *path, file_read_buffer_cb cb){
  file_context_t *ctx = file_context_create();
  ctx->file_read_buffer_done = cb;
  
  uv_fs_open(uv_default_loop(), &ctx->file_req, path, O_RDONLY, S_IRUSR, file_read_buffer_open);
}

void file_read_buffer_open(uv_fs_t *req){
  if(fs_result_is_evil(req)){
    file_read_buffer_fail(req);
    return;
  }
 
  req_get_ctx(req, ctx);
  ctx->file_id = req->result;
  uv_fs_req_cleanup(req);
  uv_fs_fstat(uv_default_loop(), &ctx->file_req, ctx->file_id, file_read_buffer_fstat);
}

void file_read_buffer_fstat(uv_fs_t *req){
  if(fs_result_is_evil(req)){
    file_read_buffer_fail(req);
    return;
  }

  req_get_ctx(req, ctx);
  size_t buf_len = sizeof(char) * req->statbuf.st_size;
  char *data = malloc(buf_len);
  ctx->buf = uv_buf_init(data, buf_len);
  uv_fs_read(uv_default_loop(), &ctx->file_req, ctx->file_id , &ctx->buf,  1, 0, file_read_buffer_read);
  uv_fs_req_cleanup(req);
}

void file_read_buffer_read(uv_fs_t *req){
  puts("hit file_read_buffer_read");
  if(fs_result_is_evil(req)){
    file_read_buffer_fail(req);
    return;
  }

  req_get_ctx(req, ctx);
  printf("ctx->statbuf->st_size %llu\n", ctx->statbuf.st_size);
  uv_fs_close(uv_default_loop(), &ctx->file_req, ctx->file_id, file_read_buffer_close);
  uv_fs_req_cleanup(req);
}

void file_read_buffer_fail(uv_fs_t *req){
  puts("hit file_read_buffer_fail");
  req_get_ctx(req, ctx);
  ctx->file_read_buffer_done(NULL);
  uv_fs_req_cleanup(req);
  file_context_free(ctx);
};

void file_read_buffer_close(uv_fs_t *req){
  puts("hit file_read_buffer_close");
  if(fs_result_is_evil(req)){
    file_read_buffer_fail(req);
    return;
  }

  req_get_ctx(req, ctx);
  ctx->file_read_buffer_done(buffer_from_int8_array((int8_t *) ctx->buf.base, ctx->buf.len));

  uv_fs_req_cleanup(req);
  file_context_free(ctx);
}

file_context_t *file_context_create(){
  file_context_t *result = malloc(sizeof(file_context_t));
  result->file_req.data = result;
  return result;
}

file_context_t *file_context_free(file_context_t *ctx){
  uv_fs_req_cleanup(&ctx->file_req);
  if(!is_null(ctx->buf.base))
    free(ctx->buf.base);
  free(ctx);
  ctx = NULL;
  return ctx;
}

#undef req_get_ctx
