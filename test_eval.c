#include <stdio.h>
#include "formulae.h"

static void test_eval_builtin() {
  // add
  char *src = "(+ 1 2 3)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);
  Object *obj = parse_expr(p);
  Env *env = new_env();
  init_env(env);
  Object *result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "6");

  // sub
  src = "(- 10 2 3)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "5");

  // mult
  src = "(* 3 2 4)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "24");

  // div
  src = "(/ 24 3 2)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "4");

  //
  src = "(+ (- 2 5) (* 2 3) (/ 9 3))";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "6");

  // cons
  src = "(cons 1 2)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "(1 . 2)");

  // car
  src = "(car (1 2))";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "1");

  // cdr
  src = "(cdr (1 2))";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "(2 . ())");

  // length
  src = "(length ())";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "0");
}

/*
static void test_eval_closure() {
  char *src = "(define square (lambda (a) (* a a)))(square 2)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);
  Object *obj = parse_expr(p);
  Env *env = new_env();
  init_env(env);
  Object *result = eval(env, obj);

  expect_int(__FILE__, __LINE__, inspect_obj(result), "4");
}
*/

void test_eval() {
  printf("*test_eval*\n");
  test_eval_builtin();
  //test_eval_closure();
  printf("OK\n");
}
