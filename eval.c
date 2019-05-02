#include <string.h>
#include <stdio.h>
#include "formulae.h"

static Object *eval_pair(Env *env, Object *pair);
static Object *eval_symbol(Env *env, Object *obj);

Object *eval(Env *env, Object *obj) {
  switch(obj->kind) {
  case OBJ_PAIR:
    return eval_pair(env, obj);
  case OBJ_SYMBOL:
    return eval_symbol(env, obj);
  case OBJ_STRING:
    return obj;
  case OBJ_NUM:
    return obj;
  case OBJ_FLOAT:
    return obj;
  case OBJ_NIL:
    return obj;
  default:
    return obj;
  }
}

static Object *eval_pair(Env *env, Object *pair) {
  if(IS_SYMBOL(FML_CAR(pair))) {
    Object* (*proc)(Env *, Object *) = get_proc(FML_CAR(pair)->tok->lit);
    if(proc != NULL) {
      Object *cdr = FML_CDR(pair);
      if(len_obj(cdr) < 0)
	error("evaluation error(%s:%d): invalid argument", __FILE__, __LINE__);
      return proc(env, cdr);
    }
    else
      error("evaluation error(%s:%d): unknown symbol: '%s'", __FILE__, __LINE__, FML_CAR(pair)->tok->lit);
  }
  else
    return FML_PAIR(eval(env, FML_CAR(pair)), eval(env, FML_CDR(pair)));
}

static Object *eval_symbol(Env *env, Object *obj) {
  Object *symbol = (Object *)get_env(env, obj->tok->lit);

  printf("env: %s\n", inspect_env(env));
  
  if(symbol == NULL)
    error("evaluation error(%s:%d): unknown symbol: '%s'", __FILE__, __LINE__, obj->tok->lit);

  return eval(env, symbol);
}
