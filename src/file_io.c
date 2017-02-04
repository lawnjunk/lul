#include "tools.h"
#include "file_io.h"

#define req_get_ctx(req) (file_context_t *) req->data

action_node_t *action_node_create(file_action action,  action_node_t *next){
  action_node_t *node = malloc(sizeof(action_node_t));
  node->action= action;
  node->next = next;
  return node;
}

action_node_t *action_node_free_all(action_node_t *node){
  if(!is_null(node->next)){
    action_node_free_all(node->next);
  }
  puts("WHAHHAHHHA");
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
    free(ctx);
  }
  return NULL;
}

void file_fail_cb(uv_fs_t *req){

}


void file_open_cb(uv_fs_t *req){
  puts("file_open_cb");
  /*action_node_free_all(ctx->next);*/
  if(req->result < 0){ // error 
    file_fail_cb(req);
    return;
  }

  file_context_t *ctx = req_get_ctx(req);

  action_node_t *last = ctx->next;
  ctx->next = last->next;
  action_node_free(last);

  if(is_null(ctx->next) || is_null(ctx->next->action)){
    file_fail_cb(req);
    return;
  }

  ctx->file_number = req->result;
  ctx->next->action(ctx);
  
}

void file_fstat_cb(uv_fs_t *req){
  puts("file_fstat_cb");
}

void file_read_cb(uv_fs_t *req){
  puts("file_read_cb");
}

void file_close_cb(uv_fs_t *req){
  puts("file_open_cb");
  /*action_node_free_all(ctx->next);*/
  if(req->result < 0){ // error 
    file_fail_cb(req);
    return;
  }

  file_context_t *ctx = req_get_ctx(req);
  // respond to user
  ctx->done(false, ctx->result);

  // clean up context
  file_context_free(ctx);
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
}

void file_write(file_context_t *ctx){
  puts("file_write");
}

void file_fstat(file_context_t *ctx){
  puts("file_fstat");
  uv_fs_fstat(uv_default_loop(), &ctx->file_req, ctx->file_number, file_fstat_cb);

}

void file_read(file_context_t *ctx){
  puts("file_read");
}

void file_read_buffer(char *path, file_done_cb done){
  puts("file_read_buffer");
  // open file
  // fstat 
  // read 
  // close && respind
  file_context_t *ctx = file_context_create();
  ctx->path = path;
  ctx->done = done;
  ctx->file_req.data = ctx;
  ctx->flags = O_RDONLY;
  ctx->mode = 0600;
  ctx->next = action_node_create(&file_open,
      action_node_create(&file_fstat,
        action_node_create(&file_close, NULL)));

  ctx->next->action(ctx);
}
