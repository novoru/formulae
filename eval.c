#include <string.h>
#include <stdio.h>
#include "formulae.h"

static Object *eval_program(Env *env, Object *obj);
static Object *eval_pair(Env *env, Object *pair);
static Object *eval_symbol(Env *env, Object *obj);
static Object *eval_closure(Env *env, Object *closure, Object *args);

Object *eval(Env *env, Object *obj) {
  switch(obj->kind) {
  case OBJ_PROGRAM:
    return eval_program(env, obj);
  case OBJ_PAIR:
    return eval_pair(env, obj);
  case OBJ_BUILTIN:
    return obj;
  case OBJ_CLOSURE:
    return obj;
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

static Object *eval_program(Env *env, Object *obj) {
  if(obj->program->len == 0) return FML_NIL();

  Object *result = FML_NIL();
  
  for(int i = 0; i < obj->program->len; i++) {
    result = eval(env, (Object *)obj->program->data[i]);
  }

  return result;
}

static Object *eval_pair(Env *env, Object *pair) {
  Object *car = FML_CAR(pair);
  Object *cdr = FML_CDR(pair);

  if(IS_SYMBOL(car)) {
    Object *obj = eval_symbol(env, car);

    return eval(env, FML_PAIR(obj, cdr));
  }
  else if(IS_BUILTIN(car)) {
    Object* (*builtin)(Env *env, Object *args) = car->builtin;

    if(car->nargs < 0) {}
    else if(car->nargs != len_obj(cdr))
      error("evaluation error(%s:%d): invalid number of arguments: %d", __FILE__, __LINE__, len_obj(cdr));
    return builtin(env, cdr);
  }
  else if(IS_CLOSURE(car)) {
    return eval_closure(env, car, cdr);
  }
  else if(IS_PAIR(car)) {
    car = eval(env, car);
    cdr = eval(env, cdr);

    return eval(env, FML_PAIR(car, cdr));
  }
  
  return FML_PAIR(eval(env, car), eval(env, cdr));
}

static Object *eval_symbol(Env *env, Object *obj) {
  Object *symbol = (Object *)get_env(env, obj->tok->lit);

  if(symbol == NULL)
    error("evaluation error(%s:%d)\n: unknown symbol: '%s'", __FILE__, __LINE__, obj->tok->lit);

  return eval(env, symbol);
}

static Object *eval_closure(Env *env, Object *closure, Object *args) {
  if(len_obj(closure->args) != len_obj(args))
    error("evaluation error(%s:%d)\n: invalid number of arguments: %d", __FILE__, __LINE__, len_obj(args));

  if(len_obj(closure->args) == 0)
    return eval(closure->env, closure->closure);

  Object *ccar = FML_CAR(closure->args);
  Object *ccdr = FML_CDR(closure->args);
  
  Object *acar = FML_CAR(args);
  Object *acdr = FML_CDR(args);

  set_env(closure->env, ccar->tok->lit, acar);

  while(!IS_NIL(ccdr)) {
    ccar = FML_CAR(ccdr);
    ccdr = FML_CDR(ccdr);
    acar = FML_CAR(acdr);
    acdr = FML_CDR(acdr);

    set_env(closure->env, ccar->tok->lit, acar);
  }

  return eval(closure->env, closure->closure);
}
