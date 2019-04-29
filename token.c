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
