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
  Object *car = FML_CAR(pair);
  Object *cdr = FML_CDR(pair);
  if(IS_SYMBOL(car)) {
    Object* (*proc)(Env *, Object *) = get_proc(car->tok->lit);
    if(proc != NULL) {
      if(len_obj(cdr) < 0)
	error("evaluation error(%s:%d): invalid argument", __FILE__, __LINE__);
      return proc(env, cdr);
    }
    else
      return pair;
  }
  else
    return FML_PAIR(eval(env, car), eval(env, cdr));
}

static Object *eval_symbol(Env *env, Object *obj) {
  Object *symbol = (Object *)get_env(env, obj->tok->lit);

  if(symbol == NULL)
    error("evaluation error(%s:%d): unknown symbol: '%s'", __FILE__, __LINE__, obj->tok->lit);

  return eval(env, symbol);
}
