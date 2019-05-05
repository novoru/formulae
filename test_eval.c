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
  src = "(car (cons 1 2))";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "1");

  // cdr
  src = "(cdr (cons 1 2))";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "2");

  // length
  src = "(length ())";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "0");
}

static void test_eval_closure() {
  char *src = "(define square (lambda (a) (* a a)))(square 2)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);
  Object *obj = parse_expr(p);
  Env *env = new_env();
  init_env(env);
  Object *result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "4");

  src = "(define foo (lambda () (+ 1 2)))(foo)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "3");

  src = "(define foo (lambda (a) (car a)))(foo (cons 1 2))";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "1");

  src = "((lambda () (+ 1 2)))";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "3");

  src = "((lambda (a b) (+ a b)) 2 3)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "5");

  src = "(= 1 1)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#t");

  src = "(= 1 2)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#f");

  src = "(= () ())";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#t");

  src = "(define a 0)(define b 0)(= a b)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#t");

  src = "(define a (lambda () (+ 1 1)))(= a a)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#t");

  src = "(define a (lambda () (+ 1 1)))(define b (lambda () (+ 1 1)))(= a b)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#f");
}

static void test_eval_rec() {
  char *src = "(define foo (lambda (n) (if (= n 1) 1 (foo (- n 1)))))(foo 5)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);
  Object *obj = parse_expr(p);
  Env *env = new_env();
  init_env(env);
  Object *result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "1");
  
  src = "(define fact(lambda (n) (if (= n 1) 1 (* n (fact (- n 1))))))(fact 3)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "6");

  src = "(define fib(lambda (n) (if (< n 2) 1 (+ (fib (- n 1))(fib (- n 2))))))(fib 10)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "89");
}

static void test_eval_cmp() {
  char *src = "(< 1 2)";
  Lexer *l = new_lexer(src);
  Parser *p = new_parser(l);
  Object *obj = parse_expr(p);
  Env *env = new_env();
  init_env(env);
  Object *result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#t");

  src = "(< 2 1)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#f");

  src = "(> 2 1)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#t");

  src = "(> 1 2)";
  l = new_lexer(src);
  p = new_parser(l);
  obj = parse_expr(p);
  result = eval(env, obj);

  expect_str(__FILE__, __LINE__, inspect_obj(result), "#f");
}

void test_eval() {
  printf("*test_eval*\n");
  test_eval_builtin();
  test_eval_closure();
  test_eval_rec();
  test_eval_cmp();
  printf("OK\n");
}
