#include <stdio.h>
#include "formulae.h"

Object *builtin_add(Env *env, Object *list) {
  if(IS_NIL(list))
    return FML_NUM(0);

  Object *car = eval(env, FML_CAR(list));

  if(!IS_NUM(car))
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(car));
  
  Object *result = new_obj_num(car->num);
  Object *cdr = eval(env, FML_CDR(list));
  
  while(!IS_NIL(cdr)) {
    if(!IS_NUM(FML_CAR(cdr)))
      error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(cdr)));
    result->num += FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *builtin_sub(Env *env, Object *list) {
  if(IS_NIL(list))
    return FML_NUM(0);

  Object *car = eval(env, FML_CAR(list));

  if(!IS_NUM(car))
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(car));
  
  Object *result = new_obj_num(car->num);
  Object *cdr = eval(env, FML_CDR(list));
  
  while(!IS_NIL(cdr)) {
    if(!IS_NUM(FML_CAR(cdr)))
      error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(cdr)));
    result->num -= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *builtin_mult(Env *env, Object *list) {
  if(IS_NIL(list))
    return FML_NUM(0);

  Object *car = eval(env, FML_CAR(list));

  if(!IS_NUM(car))
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(car));
  
  Object *result = new_obj_num(car->num);
  Object *cdr = eval(env, FML_CDR(list));
  
  while(!IS_NIL(cdr)) {
    if(!IS_NUM(FML_CAR(cdr)))
      error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(cdr)));
    result->num *= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *builtin_div(Env *env, Object *list) {
  if(IS_NIL(list))
    return FML_NUM(0);

  Object *car = eval(env, FML_CAR(list));

  if(!IS_NUM(car))
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(car));
  
  Object *result = new_obj_num(car->num);
  Object *cdr = eval(env, FML_CDR(list));
  
  while(!IS_NIL(cdr)) {
    if(!IS_NUM(FML_CAR(cdr)))
      error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(cdr)));
    result->num /= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *builtin_length(Env *env, Object *list) {
  if(IS_NIL(FML_CAR(list)))
    return FML_NUM(0);

  if(!IS_PAIR(FML_CAR(list)))
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(list)));

  return FML_NUM(len_obj(FML_CAR(list)));
}

Object *builtin_cons(Env *env, Object *list) {
  int len = len_obj(list);
  if(len != 2) {
    error("builtin error(%s:%d): invalid number of arguments: %d", __FILE__, __LINE__, len);
  }
  return FML_PAIR(FML_CAR(list), FML_CADR(list));
}

Object *builtin_car(Env *env, Object *list) {
  if(!IS_PAIR(FML_CAR(list))) {
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(list)));
  }

  return FML_CAAR(list);
}

Object *builtin_cdr(Env *env, Object *list) {
  if(!IS_PAIR(FML_CAR(list))) {
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(list)));
  }

  return FML_CDAR(list);
}

Object *builtin_define(Env *env, Object *list) {
  if(!IS_PAIR(list))
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(list));

  if(!IS_SYMBOL(FML_CAR(list)))
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(list)));

  set_env(env, FML_CAR(list)->tok->lit, (void *)FML_CADR(list));
  
  return FML_CAR(list);
}
