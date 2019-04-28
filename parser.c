#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "formulae.h"

static Object *parse_sexpr(Parser *p);

Parser *new_parser(Lexer *l) {
  Parser *p = malloc(sizeof(Parser));
  p->l = l;
  next_token_parser(p);
  next_token_parser(p);

  return p;
}

void next_token_parser(Parser *p) {
  p->curTok = p->peekTok;
  p->peekTok = next_token_lexer(p->l);
}

Object *parse_expr(Parser *p) {
  Object *obj = new_obj_nil();
  
  while(p->curTok->kind != TOK_EOF) {
    parse_sexpr(p);
    next_token_parser(p);
  }

  return obj;
}

static Object *parse_sexpr(Parser *p) {
  switch(p->curTok->kind) {
  case TOK_LPAREN:
    ;
    Object *obj = FML_PAIR(FML_NIL(), FML_NIL());
    while(1) {
      if(p->curTok->kind == TOK_RPAREN)
	return obj;
    }
  case TOK_IDENT:
    return new_obj_symbol(p->curTok);
  case TOK_NUM:
    return new_obj_num(atoi(p->curTok->lit));
  default:
    return NULL;
  }
}
