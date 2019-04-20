#include <stdlib.h>
#include "formulae.h"

Token *new_token(TokenKind kind, char *lit) {
  Token *tok = malloc(sizeof(Token));
  tok->kind = kind;
  tok->lit = lit;

  return tok;
}

char *inspect_token_kind(TokenKind kind) {
  char *s = "";
  switch(kind) {
  case TOK_IDENT:
    s = "TOK_IDENT";
    break;
  case TOK_NUM:
    s = "TOK_NUM";
    break;
  case TOK_ASSIGN:
    s = "TOK_ASSIGN('=')";
    break;
  case TOK_PLUS:
    s = "TOK_PLUS('+')";
    break;
  case TOK_MINUS:
    s = "TOK_MINUS('-')";
    break;
  case TOK_BANG:
    s = "TOK_BANG('!')";
    break;
  case TOK_ASTERISK:
    s = "TOK_ASTERISK('*')";
    break;
  case TOK_SLASH:
    s = "TOK_SLASH('/a')";
    break;
  case TOK_DOT:
    s = "TOK_DOT('.')";
    break;
  case TOK_LT:
    s = "TOK_LT('<')";
    break;
  case TOK_LTE:
    s = "TOK_LTE('<=')";
    break;
  case TOK_GT:
    s = "TOK_GT('>')";
    break;
  case TOK_GTE:
    s = "TOK_GTE('>=')";
    break;
  case TOK_LPAREN:
    s = "TOK_LPAREN('(')";
    break;
  case TOK_RPAREN:
    s = "TOK_RPAREN(')')";
    break;
  default:
    break;
  }

  return s;
}
