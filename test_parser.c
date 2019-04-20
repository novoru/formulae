#include <stdio.h>
#include <stdlib.h>
#include "formulae.h"
#include "test.h"

void expect_sexpr_nil(char *file, int line, SExpr *sexpr) {
  if(sexpr->kind != SE_NIL) {
    printf("%s: %d\n", file, line);
    printf("s-expression is not NIL, but %d\n", sexpr->kind);
    exit(1);
  }
}

void expect_sexpr_int(char *file, int line, SExpr *sexpr, int num) {
  if(sexpr->kind != SE_INT) {
    printf("%s: %d\n", file, line);
    printf("s-expression is not INT, but %d\n", sexpr->kind);
    exit(1);
  }
  if(sexpr->num != num) {
    printf("%s: %d\n", file, line);
    printf("expected: %d, actual: %d\n", sexpr->num, num);
    exit(1);
  }
}

void test_parse_num() {
  char *src = "1";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);

  SExpr *sexpr = parse_sexpr(p);
  expect_sexpr_int(__FILE__, __LINE__, sexpr, 1);
}

void test_parse_nil() {
  char *src = "()";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);

  SExpr *sexpr = parse_sexpr(p);
  expect_sexpr_nil(__FILE__, __LINE__, sexpr);
}

void test_parse_sexpr() {
  char *src = "(1 2 3 4)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);

  SExpr *sexpr = parse_sexpr(p);
  expect_sexpr_int(__FILE__, __LINE__, sexpr->car, 1);
  printf("%d\n", __LINE__);
  expect_sexpr_int(__FILE__, __LINE__, sexpr->cdr->car, 2);
  printf("%d\n", __LINE__);
  expect_sexpr_int(__FILE__, __LINE__, sexpr->cdr->cdr->car, 3);
  printf("%d\n", __LINE__);
  expect_sexpr_int(__FILE__, __LINE__, sexpr->cdr->cdr->cdr, 4);
}

void test_parser() {
  printf("*test_parser*\n");
  test_parse_num();
  test_parse_nil();
  test_parse_sexpr();
  printf("OK\n");
}
