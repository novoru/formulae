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
