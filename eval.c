#include <string.h>
#include "formulae.h"

static Object *eval_pair(Object *car, Object *cdr);
static Object *eval_symbol(Object *obj);

Object *eval(Object *obj) {
  switch(obj->kind) {
  case OBJ_PAIR:
    return eval_pair(eval(FML_CAR(obj)), eval(FML_CDR(obj)));
  case OBJ_SYMBOL:
    return obj;
  case OBJ_STRING:
    return obj;
  case OBJ_NUM:
    return obj;
  case OBJ_FLOAT:
    return obj;
  case OBJ_NIL:
    return obj;
  }
}

static Object *eval_pair(Object *car, Object *cdr) {
  Object *obj = FML_NIL();
  
  if(IS_SYMBOL(car)) {
    Object* (*proc)(Object *) = get_proc(car->tok->lit);
    if(proc != NULL && cdr != NULL)
      obj = proc(cdr);
    else
      error("error: unknown symbol\n");
  }
  else
    obj = FML_PAIR(car, cdr);

  return obj;
}
