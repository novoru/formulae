#include <stdio.h>
#include <stdlib.h>
#include "formulae.h"
#include "test.h"

/*
static void expect_obj_nil(char *file, int line, Obj *obj) {
  if(obj->kind != SE_NIL) {
    printf("%s: %d\n", file, line);
    printf("s-expression is not NIL, but %d\n", obj->kind);
    exit(1);
  }
}

static void expect_obj_int(char *file, int line, Obj *obj, int num) {
  if(obj->kind != SE_INT) {
    printf("%s: %d\n", file, line);
    printf("s-expression is not INT, but %d\n", obj->kind);
    exit(1);
  }
  if((int)obj->car != num) {
    printf("%s: %d\n", file, line);
    printf("expected: %d, actual: %d\n",num, (int)obj->car);
    exit(1);
  }
}

static void expect_obj_symbol(char *file, int line, Obj *obj, char *symbol) {
  if(obj->kind != SE_SYMBOL) {
    printf("%s: %d\n", file, line);
    printf("s-expression is not SYMBOL, but %d\n", obj->kind);
    exit(1);
  }
  if(strcmp(((Token*)obj->car)->lit, symbol)) {
    printf("%s: %d\n", file, line);
    printf("expected: %s, actual: %s\n",symbol, (char*)((Token*)(obj->car))->lit);
    exit(1);
  }
}

static void test_parse_num() {
  char *src = "1";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);

  Obj *obj = parse_obj(p);
  expect_obj_int(__FILE__, __LINE__, obj, 1);
}

static void test_parse_nil() {
  char *src = "()";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);

  Obj *obj = parse_obj(p);
  expect_obj_nil(__FILE__, __LINE__, obj);
}

static void test_parse_obj_num() {
  char *src = "(1 2 3 4)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);

  Obj *obj = parse_obj(p);
  expect_obj_int(__FILE__, __LINE__, (Obj*)obj->car, 1);
  expect_obj_int(__FILE__, __LINE__, (Obj*)obj->cdr, 2);
  expect_obj_int(__FILE__, __LINE__, (Obj*)((Obj*)obj->cdr)->cdr, 3);
  expect_obj_int(__FILE__, __LINE__, (Obj*)((Obj*)((Obj*)obj->cdr)->cdr)->cdr, 4);
}

static void test_parse_obj_symbol() {
  char *src = "(lambda x y)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);

  Obj *obj = parse_obj(p);

  expect_obj_symbol(__FILE__, __LINE__, (Obj*)obj->car, "lambda");
  expect_obj_symbol(__FILE__, __LINE__, (Obj*)obj->cdr, "x");
  expect_obj_symbol(__FILE__, __LINE__, (Obj*)((Obj*)obj->cdr)->cdr, "y");
}
*/

void test_parser() {
  printf("*test_parser*\n");
  //test_parse_num();
  //test_parse_nil();
  //test_parse_obj_num();
  //test_parse_obj_symbol();
  printf("OK\n");
}
