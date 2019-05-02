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

  if(IS_PAIR(cdr)) {
    while(!IS_NIL(cdr)) {
      Object *obj = eval(env, FML_CAR(cdr));
      if(!IS_NUM(obj))
	error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(obj));
      result->num += obj->num;
      cdr = eval(env, FML_CDR(cdr));
    }
  }
  else if(IS_NUM(cdr)) {
    result->num += cdr->num;
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

  if(IS_PAIR(cdr)) {
    while(!IS_NIL(cdr)) {
      Object *obj = eval(env, FML_CAR(cdr));
      if(!IS_NUM(obj))
	error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(obj));
      result->num -= obj->num;
      cdr = eval(env, FML_CDR(cdr));
    }
  }
  else if(IS_NUM(cdr)) {
    result->num += cdr->num;
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

  if(IS_PAIR(cdr)) {
    while(!IS_NIL(cdr)) {
      Object *obj = eval(env, FML_CAR(cdr));
      if(!IS_NUM(obj))
	error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(obj));
      result->num *= obj->num;
      cdr = eval(env, FML_CDR(cdr));
    }
  }
  else if(IS_NUM(cdr)) {
    result->num += cdr->num;
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

  if(IS_PAIR(cdr)) {
    while(!IS_NIL(cdr)) {
      Object *obj = eval(env, FML_CAR(cdr));
      if(!IS_NUM(obj))
	error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(obj));
      result->num /= obj->num;
      cdr = eval(env, FML_CDR(cdr));
    }
  }
  else if(IS_NUM(cdr)) {
    result->num += cdr->num;
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
  Object *obj = eval(env, FML_CAR(list));
  if(!IS_PAIR(obj)) {
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(list)));
  }

  return FML_CAR(obj);
}

Object *builtin_cdr(Env *env, Object *list) {
  Object *obj = eval(env, FML_CAR(list));
  if(!IS_PAIR(obj)) {
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(list)));
  }

  return FML_CDR(obj);
}

Object *builtin_define(Env *env, Object *list) {
  if(!IS_PAIR(list))
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(list));

  if(!IS_SYMBOL(FML_CAR(list)))
    error("builtin error(%s:%d): invalid argument: '%s'", __FILE__, __LINE__, inspect_obj_kind(FML_CAR(list)));

  set_env(env, FML_CAR(list)->tok->lit, (void *)FML_CADR(list));
  
  return FML_CAR(list);
}

void register_func(Env *env, char *name, int nargs, void *_func) {
  Object *func = new_obj_func(env, nargs, _func);
  set_env(env, name, func);
}
