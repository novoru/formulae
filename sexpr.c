#include <stdlib.h>
#include "formulae.h"

SExpr *new_sexpr(void *car, void *cdr) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_LIST;
  sexpr->car = car;
  sexpr->cdr = cdr;

  return sexpr;
}

SExpr *new_sexpr_symbol(Token *tok) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_SYMBOL;
  sexpr->car = (void*)tok;
  sexpr->cdr = new_sexpr_nil();
  
  return sexpr;  
}

SExpr *new_sexpr_str(char *str) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_STRING;
  sexpr->car = (void*)str;
  sexpr->cdr = new_sexpr_nil();

  return sexpr;  
}

SExpr *new_sexpr_int(int num) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_INT;
  sexpr->car = (void*)num;
  sexpr->cdr = new_sexpr_nil();

  return sexpr;  
}

SExpr *new_sexpr_float(float fnum) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_FLOAT;
  //sexpr->car = (void*)fnum;
  sexpr->cdr = new_sexpr_nil();

  return sexpr;  
}

SExpr *new_sexpr_nil() {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_NIL;

  return sexpr;  
}

void sexpr_append(SExpr *sexpr, void *cdr) {
  SExpr *tmp = sexpr;
  while(((SExpr*)tmp->cdr)->kind != SE_NIL) {
    tmp = tmp->cdr;
  }

  tmp->cdr = cdr;
}

char *inspect_sexpr(SExpr *sexpr) {
  switch(sexpr->kind) {
  case SE_LIST:
    return format("(%s %s)", inspect_sexpr((SExpr*)sexpr->car), inspect_sexpr((SExpr*)sexpr->cdr));
  case SE_SYMBOL:
    return format("%s %s", ((Token*)sexpr->car)->lit, inspect_sexpr((SExpr*)sexpr->cdr));
  case SE_STRING:
    return format("%s %s", (char*)sexpr->car, inspect_sexpr((SExpr*)sexpr->cdr));
  case SE_INT:
    return format("%d %s", (int)sexpr->car, inspect_sexpr((SExpr*)sexpr->cdr));
  case SE_FLOAT:
    //return format("%f", (float)sexpr->car);
    return "";
  case SE_NIL:
    return format("()");
  default:
    printf("(%s: %d) invalid s-expression\n", __FILE__, __LINE__);
    exit(1);
  }
}
