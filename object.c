#include <stdlib.h>
#include "formulae.h"

Object *new_obj_program() {
  Object *program = malloc(sizeof(Object));
  program->program = new_vec();

  return program;
}

Object *new_obj_pair(Object *car, Object *cdr) {
  Object *pair = malloc(sizeof(Object));
  pair->kind = OBJ_PAIR;
  pair->car = car;
  pair->cdr = cdr;
  
  return pair;
}

Object *new_obj_builtin(Env *outer, int nargs, void *b) {
  Object *builtin = malloc(sizeof(Object));
  builtin->kind = OBJ_BUILTIN;
  builtin->env = new_enclosed_env(outer);
  builtin->nargs = nargs;
  builtin->builtin = b;
  
  return builtin;
}

Object *new_obj_closure(Env *outer, Object *args, Object *c) {
  Object *closure = malloc(sizeof(Object));
  closure->kind = OBJ_CLOSURE;
  closure->env = new_enclosed_env(outer);
  closure->args = args;
  closure->closure = c;
  
  return closure;
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

Object *new_obj_bool(bool b) {
  Object *obj = malloc(sizeof(Object));
  obj->kind = OBJ_BOOL;
  obj->b = b;

  return obj;
}

Object *append(Object *list, Object *cdr) {
  if(IS_NIL(list))
    return cdr;
  else
    return FML_PAIR(FML_CAR(list), append(FML_CDR(list), cdr));
}

char *inspect_obj(Object *obj) {
  switch (obj->kind) {
  case OBJ_PROGRAM:
    ;
    char *s = "";
    for(int i = 0; i < obj->program->len; i++) {
      if(i == 0) s = inspect_obj((Object *)obj->program->data[i]);
      else s = format("%s\n%s", s, inspect_obj((Object *)obj->program->data[i]));
    }
    return s;
  case OBJ_PAIR:
    return format("(%s . %s)", inspect_obj(obj->car), inspect_obj(obj->cdr));
  case OBJ_BUILTIN:
    return "builtin";
  case OBJ_CLOSURE:
    return format("closure-> (args:%s), (body:%s)", inspect_obj(obj->args), inspect_obj(obj->closure));
  case OBJ_SYMBOL:
    return obj->tok->lit;
  case OBJ_STRING:
    return obj->str;
  case OBJ_NUM:
    return format("%d", obj->num);
  case OBJ_FLOAT:
    return format("%l", obj->fnum);
  case OBJ_BOOL:
    return (obj->b) ? "#t":"#f";
  case OBJ_NIL:
    return "()";
  default:
    return "";
  }
}

char *inspect_obj_kind(Object *obj) {
  switch (obj->kind) {
  case OBJ_PROGRAM:
    return "PROGRAM";
  case OBJ_PAIR:
    return "PAIR";
  case OBJ_BUILTIN:
    return "BUILTIN";
  case OBJ_CLOSURE:
    return "CLOSURE";
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
  case OBJ_BOOL:
    return "BOOL";
  default:
    return format("ILLEGAL: %d", obj->kind);
  }
}

int len_obj(Object *obj) {
  Object *tmp = obj;
  int len = 0;
  
  while(1){
    if(IS_NIL(obj)) return len;
    if(!IS_PAIR(obj)) return FML_LIST_DOTTED;

    obj = FML_CDR(obj);
    len++;

    if(IS_NIL(obj)) return len;
    if(!IS_PAIR(obj)) return FML_LIST_DOTTED;

    obj = FML_CDR(obj);
    tmp = FML_CDR(tmp);
    if(obj == tmp) return FML_LIST_CIRCULAR;
    len++;
  }
  
  return len;
}

Object *cmp_obj(Object *obj1, Object *obj2) {
  if(obj1->kind != obj2->kind)
    return FML_BOOL(false);

  switch(obj1->kind) {
  case OBJ_NUM:
    return FML_BOOL(obj1->num == obj2->num ? true:false);
  case OBJ_BOOL:
    return FML_BOOL(obj1->b == obj2->b ? true:false);
  case OBJ_NIL:
    return FML_TRUE();
  case OBJ_CLOSURE:
    return FML_BOOL((obj1->args == obj2->args) && (obj1->closure == obj2->closure) ? true:false);
  default:
    printf("obj1:%s, obj2:%s\n", inspect_obj(obj1), inspect_obj(obj2));
    printf("&obj1:%d, &obj2:%d\n", obj1, obj2);
    return FML_BOOL(obj1 == obj2 ? true:false);
  }
}
