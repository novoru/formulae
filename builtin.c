#include "formulae.h"

Object *builtin_add(Object *list) {
  if(IS_NIL(list))
    return FML_NUM(0);

  Object *car;
  
  if(!IS_PAIR(list) && !IS_NUM(list))
    error("invalid argument: %s\n", inspect_obj_kind(list));
  else if(IS_NUM(list))
    return list;
  else
    car = FML_CAR(list);
    
  Object *result = new_obj_num(car->num);
  Object *cdr = eval(FML_CDR(list));
  
  while(!IS_NIL(cdr)) {
    if(!IS_NUM(FML_CAR(cdr)))
      error("invalid argument: %s\n", inspect_obj_kind(FML_CAR(cdr)));
    result->num += FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *builtin_sub(Object *list) {
  if(IS_NIL(list))
    return FML_NUM(0);

  Object *car;
  
  if(!IS_PAIR(list) && !IS_NUM(list))
    error("invalid argument: %s\n", inspect_obj_kind(list));
  else
    car = FML_CAR(list);
    
  Object *result = new_obj_num(car->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num -= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *builtin_mult(Object *list) {
  if(IS_NIL(list))
    return FML_NUM(0);

  Object *car;
  
  if(!IS_PAIR(list) && !IS_NUM(list))
    error("invalid argument: %s\n", inspect_obj_kind(list));
  else
    car = FML_CAR(list);
    
  Object *result = new_obj_num(car->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num *= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *builtin_div(Object *list) {
  if(IS_NIL(list))
    return FML_NUM(0);

  Object *car;
  
  if(!IS_PAIR(list) && !IS_NUM(list))
    error("invalid argument: %s\n", inspect_obj_kind(list));
  else
    car = FML_CAR(list);
    
  Object *result = new_obj_num(car->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num /= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *builtin_car(Object *list) {
  if(!IS_PAIR(FML_CAR(list)))
    error("invalid argument:%s\n", inspect_obj_kind(FML_CAR(list)));

  return FML_CAAR(list);
}

Object *builtin_cdr(Object *list) {
  if(!IS_PAIR(FML_CDR(list)))
    error("invalid argument:%s\n", inspect_obj_kind(FML_CDR(list)));

  return FML_CDAR(list);
}
