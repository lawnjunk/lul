#include "tools.h"
#include "file_io.h"

#define req_get_ctx(req) (file_context_t *) req->data


void file_open(file_context_t *ctx);
void file_close(file_context_t *ctx);
void file_fail(file_context_t *ctx);
void file_write(file_context_t *ctx);
void file_fstat(file_context_t *ctx);
void file_read(file_context_t *ctx);

action_node_t *action_append(file_action action,  action_node_t *next){
  action_node_t *node = malloc(sizeof(action_node_t));
  node->action= action;
  node->next = next;
  return node;
}

action_node_t *action_node_all_free(action_node_t *node){
  if(is_null(node)) return NULL;
  if(!is_null(node->next)){
    puts("fuu");
    return action_node_all_free(node->next);
  }
  free(node);
  return NULL;;
}

action_node_t *action_node_free(action_node_t *node){
  if(!is_null(node))
    free(node);
  return NULL;;
}


file_context_t *file_context_create(){
  file_context_t *ctx = malloc(sizeof(file_context_t));
  ctx->file_req.data = ctx;
  return ctx;;
}

file_context_t *file_context_free(file_context_t *ctx){
  if(!is_null(ctx)){
    action_node_all_free(ctx->next);
    free(ctx);
  }
  return NULL;
}


void file_open_cb(uv_fs_t *req){
  puts("file_open_cb");
  /*action_node_free_all(ctx->next);*/
  file_context_t *ctx = req_get_ctx(req);
  if(req->result < 0){ // error
    file_fail(ctx);
    return;
  }

  action_node_t *last = ctx->next;
  ctx->next = last->next;
  action_node_free(last);

  if(is_null(ctx->next) || is_null(ctx->next->action)){
    file_fail(ctx);
    return;
  }

  ctx->file_number = req->result;
  uv_fs_req_cleanup(req);
  ctx->next->action(ctx);

}

void file_fstat_cb(uv_fs_t *req){
  puts("file_fstat_cb");
  file_context_t *ctx = req_get_ctx(req);
  if(req->result < 0){ // error
    file_fail(ctx);
    return;
  }

  ctx->statbuf = req->statbuf;

  action_node_t *last = ctx->next;
  ctx->next = last->next;
  action_node_free(last);

  uv_fs_req_cleanup(req);
  ctx->next->action(ctx);

}

void file_read_cb(uv_fs_t *req){
  puts("file_read_cb");
  file_context_t *ctx = req_get_ctx(req);
  if(req->result < 0){ // error
    file_fail(ctx);
    return;
  }

  printf("booya len: %zu\n", ctx->buf.len);
  action_node_t *last = ctx->next;
  ctx->next = last->next;
  action_node_free(last);
  // clean req
  uv_fs_req_cleanup(req);
  // run next action
  ctx->next->action(ctx);
  // run next action
}

void file_write_cb(uv_fs_t *req){
  puts("file_write_cb");
  file_context_t *ctx = req_get_ctx(req);
  if(req->result < 0){ // error
    file_fail(ctx);
    return;
  }

  action_node_t *last = ctx->next;
  ctx->next = last->next;
  action_node_free(last);
  // clean req
  uv_fs_req_cleanup(req);
  // run next action
  ctx->next->action(ctx);
  // run next action
}

void file_close_cb(uv_fs_t *req){
  puts("file_open_cb");

  file_context_t *ctx = req_get_ctx(req);
  if(req->result < 0){ // error
    file_fail(ctx);
    return;
  }

  // get context
  // fetch next action
  action_node_t *last = ctx->next;
  ctx->next = last->next;
  action_node_free(last);
  // clean req
  uv_fs_req_cleanup(req);
  // run next action
  ctx->next->action(ctx);
}

void file_open(file_context_t *ctx){
  puts("file_open");
  uv_fs_open(uv_default_loop(), &ctx->file_req, ctx->path, ctx->flags, ctx->mode,
      file_open_cb);
}

void file_close(file_context_t *ctx){
  puts("file_close");
  uv_fs_close(uv_default_loop(), &ctx->file_req, ctx->file_number, file_close_cb);
}

void file_fail(file_context_t *ctx){
  puts("file_fail");

  ctx->done(true, NULL);

  file_context_free(ctx);
}

void file_write(file_context_t *ctx){
  puts("file_write");
  printf("CHAR AT 0 %c\n", ctx->buf.base[0]);
  uv_fs_write(uv_default_loop(), &ctx->file_req, ctx->file_number, &ctx->buf,
      ctx->buf.len , 1, file_write_cb);
}

void file_fstat(file_context_t *ctx){
  puts("file_fstat");
  uv_fs_fstat(uv_default_loop(), &ctx->file_req, ctx->file_number, file_fstat_cb);

}

void file_read(file_context_t *ctx){
  puts("file_read");
  ctx->buf.len = sizeof(char) * ctx->statbuf.st_size;
  ctx->buf.base = malloc(ctx->buf.len);
  uv_fs_read(uv_default_loop(), &ctx->file_req, ctx->file_number, &ctx->buf, 1, 0,
      file_read_cb);
}

void file_respond_buffer(file_context_t *ctx){
  puts("file_respond_buffer");

  buffer_t result = buffer_init(ctx->buf.len);
  memcpy(result.data, ctx->buf.base, ctx->buf.len);
  ctx->done(false, &result);

  file_context_free(ctx);
}

void file_respond_write(file_context_t *ctx){
  puts("file_respond_write");
  ctx->done(false, NULL);
  file_context_free(ctx);
}

void file_read_buffer(char *path, file_done_cb done){
  puts("file_read_buffer");
  // open file
  // fstat file
  // read file
  // close file
  // respind
  file_context_t *ctx = file_context_create();
  ctx->path = path;
  ctx->done = done;
  ctx->file_req.data = ctx;
  ctx->flags = O_RDONLY;
  ctx->mode = 0600;
  ctx->next = action_append(&file_open,
      action_append(&file_fstat,
        action_append(&file_read,
          action_append(&file_close,
            action_append(&file_respond_buffer, NULL)))));

  ctx->next->action(ctx);
}

void file_write_buffer(char *path, buffer_t *buf, file_done_cb done){
  puts("file_read_buffer");
  // open file
  // write file
  // close file
  // respond
  file_context_t *ctx = file_context_create();
  ctx->path = path;
  ctx->done = done;
  ctx->file_req.data = ctx;
  ctx->flags = O_WRONLY | O_CREAT;
  ctx->mode = 0644;

  ctx->buf.base = malloc(sizeof(char) * buf->length);
  ctx->buf.len = buf->length;
  memcpy(ctx->buf.base, buf->data, buf->length);

  ctx->next = action_append(&file_open,
      action_append(&file_write,
        action_append(&file_close,
         action_append(&file_respond_write, NULL))));

  ctx->next->action(ctx);
}
