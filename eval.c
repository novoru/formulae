#include <string.h>
#include "formulae.h"

static Object *eval_pair(Object *pair);
static Object *eval_symbol(Object *obj);

Object *eval(Object *obj) {
  switch(obj->kind) {
  case OBJ_PAIR:
    return eval_pair(obj);
  case OBJ_SYMBOL:
    return obj;
  case OBJ_STRING:
    return obj;
  case OBJ_NUM:
    return obj;
  case OBJ_FLOAT:
    return obj;
  case OBJ_NIL:
    return obj;
  }
}

static Object *eval_pair(Object *pair) {
  if(IS_SYMBOL(FML_CAR(pair))) {
    Object* (*proc)(Object *) = get_proc(FML_CAR(pair)->tok->lit);
    if(proc != NULL) {
      Object *cdr = eval(FML_CDR(pair));
      if(len_obj(cdr) < 0)
	error("error: invalid argument\n");
      return proc(cdr);
    }
    else
      error("error: unknown symbol: '%s'\n", FML_CAR(pair)->tok->lit);
  }
  else
    return FML_PAIR(eval(FML_CAR(pair)), eval(FML_CDR(pair)));
}
