#include <stdlib.h>
#include "formulae.h"

SExpr *new_sexpr(SExpr *car, SExpr *cdr) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_LIST;
  sexpr->car = car;
  sexpr->cdr = cdr;

  return sexpr;
}

SExpr *new_sexpr_symbol(Token *tok) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_SYMBOL;
  sexpr->symbol = tok;

  return sexpr;  
}

SExpr *new_sexpr_str(char *str) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_STRING;
  sexpr->str = str;

  return sexpr;  
}

SExpr *new_sexpr_int(int num) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_INT;
  sexpr->num = num;

  return sexpr;  
}

SExpr *new_sexpr_float(float fnum) {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_FLOAT;
  sexpr->fnum = fnum;

  return sexpr;  
}

SExpr *new_sexpr_nil() {
  SExpr *sexpr = malloc(sizeof(SExpr));
  sexpr->kind = SE_NIL;

  return sexpr;  
}

void sexpr_append(SExpr *sexpr, SExpr *cdr) {
  SExpr *tmp = sexpr;
  while(tmp->cdr->kind == SE_LIST) {
    tmp = tmp->cdr;
  }

  if(tmp->cdr->kind == SE_NIL)
    tmp->cdr = cdr;
  else
    tmp->cdr = new_sexpr(tmp->cdr, cdr);
}
