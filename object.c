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

Object *append(Object *list, Object *cdr) {
  if(IS_NIL(list))
    return cdr;
  else
    return FML_PAIR(FML_CAR(list), append(FML_CDR(list), cdr));
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

char *inspect_obj_kind(Object *obj) {
  switch (obj->kind) {
  case OBJ_PAIR:
    return "PAIR";
  case OBJ_SYMBOL:
    return "SYMBOL";
  case OBJ_STRING:
    return "STRING";
  case OBJ_NUM:
    return "NUM";
  case OBJ_FLOAT:
    return "FLOAT";
  case OBJ_NIL:
    return "NIL";
  default:
    return format("ILLEGAL: %d", obj->kind);
  }
}

void init_proctbl() {
  proctbl = new_map();

  register_proc("+", (void *)builtin_add);
  register_proc("-", (void *)builtin_sub);
  register_proc("*", (void *)builtin_mult);
  register_proc("/", (void *)builtin_div);

  register_proc("cons", (void *)builtin_cons);
  register_proc("car", (void *)builtin_car);
  register_proc("cdr", (void *)builtin_cdr);
  register_proc("length", (void *)builtin_length);
}

void register_proc(char *symbol, void *proc) {
  map_push(proctbl, symbol, (void *)proc);
}

void *get_proc(char *symbol) {
  return (void *)map_get(proctbl, symbol);
}

int len_obj(Object *obj) {
  if(IS_NIL(obj))
    return 0;
    
  int len = 0;
  Object *tmp = obj;
  
  while(IS_PAIR(tmp)) {
    len++;
    tmp = FML_CDR(tmp);
  }

  return len;
}
