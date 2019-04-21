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
  if((int)sexpr->car != num) {
    printf("%s: %d\n", file, line);
    printf("expected: %d, actual: %d\n",num, (int)sexpr->car);
    exit(1);
  }
}

void expect_sexpr_symbol(char *file, int line, SExpr *sexpr, char *symbol) {
  if(sexpr->kind != SE_SYMBOL) {
    printf("%s: %d\n", file, line);
    printf("s-expression is not SYMBOL, but %d\n", sexpr->kind);
    exit(1);
  }
  if(strcmp(((Token*)sexpr->car)->lit, symbol)) {
    printf("%s: %d\n", file, line);
    printf("expected: %s, actual: %s\n",symbol, (char*)((Token*)(sexpr->car))->lit);
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

void test_parse_sexpr_num() {
  char *src = "(1 2 3 4)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);

  SExpr *sexpr = parse_sexpr(p);
  expect_sexpr_int(__FILE__, __LINE__, (SExpr*)sexpr->car, 1);
  expect_sexpr_int(__FILE__, __LINE__, (SExpr*)sexpr->cdr, 2);
  expect_sexpr_int(__FILE__, __LINE__, (SExpr*)((SExpr*)sexpr->cdr)->cdr, 3);
  expect_sexpr_int(__FILE__, __LINE__, (SExpr*)((SExpr*)((SExpr*)sexpr->cdr)->cdr)->cdr, 4);
}

void test_parse_sexpr_symbol() {
  char *src = "(lambda x y)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);

  SExpr *sexpr = parse_sexpr(p);

  expect_sexpr_symbol(__FILE__, __LINE__, (SExpr*)sexpr->car, "lambda");
  expect_sexpr_symbol(__FILE__, __LINE__, (SExpr*)sexpr->cdr, "x");
  expect_sexpr_symbol(__FILE__, __LINE__, (SExpr*)((SExpr*)sexpr->cdr)->cdr, "y");
}

void test_parser() {
  printf("*test_parser*\n");
  test_parse_num();
  test_parse_nil();
  test_parse_sexpr_num();
  test_parse_sexpr_symbol();
  printf("OK\n");
}
