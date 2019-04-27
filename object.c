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
  switch (obj->kind) {
  case OBJ_PAIR:
    return format("(%s . %s)", inspect_obj(obj->car), inspect_obj(obj->cdr));
  case OBJ_SYMBOL:
    return obj->tok->lit;
  case OBJ_STRING:
    return obj->str;
  case OBJ_NUM:
    return format("%d", obj->num);
  case OBJ_FLOAT:
    return format("%l", obj->fnum);
  case OBJ_NIL:
    return "()";
  default:
    return "";
  }
}

void init_proctbl() {
  proctbl = new_map();
}

void register_proc(char *symbol, void *proc) {
  map_push(proctbl, symbol, (void *)proc);
}

void *get_proc(char *symbol) {
  return (void *)map_get(proctbl, symbol);
}

Object *apply_proc(char *symbol, Object *list) {
  Object *result = malloc(sizeof(Object));
  /*
    ToDo:
    need to add builtin function to symbol map
  */
  
  Object *(*proc)(Object *) = map_get(proctbl, symbol);
  result = proc(list);
  
  return result;
}
