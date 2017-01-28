#include "tools.h"
#include "doc.h"
#include "line.h"
#include "flub.h"

#define DOC_START_SIZE 100

doc_t *doc_create(){
  dlog("doc_create");
  doc_t *result = (doc_t *) malloc(sizeof(doc_t));
  result->lines = (line_t **) calloc(sizeof(line_t *), DOC_START_SIZE);
  result->err = flub_create("generic doc error");
  result->size = DOC_START_SIZE;
  range(i, 0 , result->size){
    (result->lines)[i] = line_create("");
  }
  result->length = 0;
  return result;
}
// for(int i=0;i<result->size;i++){*/

doc_t *doc_free(doc_t *doc){
  dlog("doc_free");
  range(i, 0, doc->size){
    // free each line then free lines
    line_free((doc->lines)[i]);
  }

  free(doc->lines);

  // free err
  flub_free(doc->err);
  // free line
  free(doc); doc = NULL;
  return doc;
}

bool doc_is_evil(doc_t *doc){
  if(is_null(doc)) return true;
  return flub_is_evil(doc->err);
}

doc_t *doc_trouble_on(doc_t *doc, char *msg){
  flub_trouble_on(doc->err, msg);
  return doc;
}

