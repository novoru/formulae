#include <stdlib.h>
#include "formulae.h"

Object *new_obj_pair(Object *car, Object *cdr) {
  Object *pair = malloc(sizeof(Object));
  pair->kind = OBJ_PAIR;
  pair->car = car;
  pair->cdr = cdr;
  
  return pair;
}

Object *new_obj_symbol(Token *tok) {
  Object *symbol = malloc(sizeof(Object));
  symbol->kind = OBJ_SYMBOL;
  symbol->tok = tok;
  
  return symbol;
}

Object *new_obj_str(char *s) {
  Object *str = malloc(sizeof(Object));
  str->kind = OBJ_STRING;
  str->str = s;
  
  return str;
}

Object *new_obj_num(int n) {
  Object *num = malloc(sizeof(Object));
  num->kind = OBJ_NUM;
  num->num = n;
  
  return num;
}

Object *new_obj_float(float f) {
  Object *fnum = malloc(sizeof(Object));
  fnum->fnum = f;
  
  return fnum;
}

Object *new_obj_nil() {
  Object *nil = malloc(sizeof(Object));
  nil->kind = OBJ_NIL;
  
  return nil;
}

void obj_append(Object *obj, Object *cdr) {
}

char *inspect_obj(Object *obj) {
  char *s = "";

  return s;
}

Object *apply_proc(Object *proc, Object *list) {
  Object *result = malloc(sizeof(Object));

  // ToDo
  // Object *(*func)(Object *) = map_get(proc);
  // result = func(list);
  
  return result;
}
