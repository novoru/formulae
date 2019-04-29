#include "formulae.h"

Object *plus(Object *list) {
  Object *result = new_obj_num(eval(FML_CAR(list))->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num += eval(FML_CAR(cdr))->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *minus(Object *list) {
  Object *result = new_obj_num(FML_CAR(list)->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num -= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *mult(Object *list) {
  Object *result = new_obj_num(FML_CAR(list)->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num *= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

Object *divide(Object *list) {
  Object *result = new_obj_num(FML_CAR(list)->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num /= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}
