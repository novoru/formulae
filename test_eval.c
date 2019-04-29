#include <stdio.h>
#include "formulae.h"

static void test_eval_builtin() {
  // add
  char *src = "(+ 1 2 3)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);
  Object *obj = parse_expr(p);
  Object *result = eval(obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "6");

  // sub
  src = "(- 10 2 3)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "5");

  // mult
  src = "(* 3 2 4)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "24");

  // div
  src = "(/ 24 3 2)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "4");

  //
  src = "(+ (- 2 5) (* 2 3) (/ 9 3))";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "6");
}

void test_eval() {
  printf("*test_eval*\n");
  test_eval_builtin();
  printf("OK\n");
}
