#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "formulae.h"

static SExpr *parse_expr(Parser *p);
static SExpr *parse_list(Parser *p);
static SExpr *parse_symbol(Parser *p);
static SExpr *parse_str(Parser *p);
static SExpr *parse_int(Parser *p);
static SExpr *parse_float(Parser *p);
static _Bool peek_token_is(Parser *p, TokenKind kind);
static void expect_peek(Parser *p, TokenKind kind);

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

SExpr *parse_sexpr(Parser *p) {
  SExpr *sexpr;

  while(p->curTok->kind != TOK_EOF) {
    sexpr = parse_expr(p);
    next_token_parser(p);
  }
  
  return sexpr;
}

static SExpr *parse_expr(Parser *p) {
  printf("parse_expr\n");
  switch(p->curTok->kind) {
  case TOK_LPAREN:
    next_token_parser(p);
    
    if(p->curTok->kind == TOK_RPAREN) {
      next_token_parser(p);
      return new_sexpr_nil();
    }

    SExpr *expr = new_sexpr(new_sexpr_nil(), new_sexpr_nil());
    
    expr->car = parse_expr(p);
    next_token_parser(p);

    while(p->curTok->kind != TOK_RPAREN && p->curTok->kind != TOK_EOF) {
      sexpr_append(expr, parse_expr(p));
      next_token_parser(p);
    }
    
    return expr;
  case TOK_IDENT:
    return parse_symbol(p);
  case TOK_DOUBLE_QUOTE:
    return parse_str(p);
  case TOK_NUM:
    return parse_int(p);
  default:
    break;
  }

  return NULL;
}

static SExpr *parse_list(Parser *p) {
  printf("parse_list\n");
  return NULL;
}

static SExpr *parse_symbol(Parser *p) {
  printf("parse_symbol\n");
  return new_sexpr_symbol(p->curTok);
}

static SExpr *parse_str(Parser *p) {
  printf("parse_str\n");
  return NULL;
}

static SExpr *parse_int(Parser *p) {
  printf("parse_int\n");
  return new_sexpr_int(atoi(p->curTok->lit));
}

static SExpr *parse_float(Parser *p) {
  printf("parse_float\n");
  return NULL;
}


static _Bool peek_token_is(Parser *p, TokenKind kind) {
  return p->peekTok->kind == kind;
}

static void expect_peek(Parser *p, TokenKind kind) {
  if(!peek_token_is(p, kind)) {
    // TODO: push error to container
    printf("(parse error) expect: %s, actual: %s\n", inspect_token_kind(kind), inspect_token_kind(p->peekTok->kind));
    exit(1);
  }
  next_token_parser(p);
}
