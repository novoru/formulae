#include <string.h>
#include "formulae.h"

static SExpr *eval_symbol(SExpr *sexpr);

SExpr *eval (SExpr *sexpr) {
  switch(((SExpr*)(sexpr->car))->kind) {
  case SE_LIST:
    break;
  case SE_SYMBOL:
    return eval_symbol(sexpr);
  case SE_STRING:
    break;
  case SE_INT:
    return sexpr->car;
  case SE_FLOAT:
    break;
  case SE_NIL:
    break;
  default:
    break;
  }

  return NULL;
}

static SExpr *eval_symbol(SExpr *sexpr) {
  return NULL;
}
