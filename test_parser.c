#include <stdio.h>
#include <stdlib.h>
#include "formulae.h"
#include "test.h"

static void test_parse_num() {
  char *src = "1";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);
  Object *result = parse_expr(p);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "1");
}

static void test_parse_nil() {
  char *src = "()";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);
  Object *result = parse_expr(p);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "()");
}

static void test_parse_list() {
  char *src = "(1 2 3)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);
  Object *result = parse_expr(p);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "(1 . (2 . (3 . ())))");
}

void test_parser() {
  printf("*test_parser*\n");
  test_parse_num();
  test_parse_nil();
  test_parse_list();
  printf("OK\n");
}
