#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formulae.h"
#include "test.h"

static void expect_token(char *file, int line, Token *tok, TokenKind kind, char *lit) {
  if(tok->kind != kind || strcmp(tok->lit, lit)) {
    printf("%s: %d\n", file, line);
    printf("expected kind of token: %d, actual: %d\n", kind, tok->kind);
    printf("expected literal: %s, actual: %s,\n", lit, tok->lit);
    exit(1);
  }
}

static void test_op() {
  char *src = "+-*/<><=>=";
  Lexer *l = new_lexer(src);

  Token *plus = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, plus, TOK_PLUS, "+");

  Token *minus = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, minus, TOK_MINUS, "-");
  
  Token *asterisk = next_token_lexer(l); 
  expect_token(__FILE__, __LINE__, asterisk, TOK_ASTERISK, "*");
  
  Token *slash = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, slash, TOK_SLASH, "/");

  Token *lt = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, lt, TOK_LT, "<");

  Token *gt = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, gt, TOK_GT, ">");

  Token *lte = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, lte, TOK_LTE, "<=");

  Token *gte = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, gte, TOK_GTE, ">=");
}

static void test_skip() {
  char *src = "+ -\n*\t/<\r>";
  Lexer *l = new_lexer(src);

  Token *plus = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, plus, TOK_PLUS, "+");

  Token *minus = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, minus, TOK_MINUS, "-");
  
  Token *asterisk = next_token_lexer(l); 
  expect_token(__FILE__, __LINE__, asterisk, TOK_ASTERISK, "*");
  
  Token *slash = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, slash, TOK_SLASH, "/");

  Token *lt = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, lt, TOK_LT, "<");

  Token *gt = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, gt, TOK_GT, ">");
}

static void test_int() {
  char *src = "0 10 100 1000";
  Lexer *l = new_lexer(src);

  Token *zero = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, zero, TOK_NUM, "0");

  Token *ten = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, ten, TOK_NUM, "10");

  Token *hundred = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, hundred, TOK_NUM, "100");

  Token *thousand = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, thousand, TOK_NUM, "1000");
}

static void test_ident() {
  char *src = "foo 100 bar uint32_t";
  Lexer *l = new_lexer(src);

  Token *foo = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, foo, TOK_IDENT, "foo");  

  next_token_lexer(l);
  
  Token *bar = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, bar, TOK_IDENT, "bar");

  Token *_uint32_t = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _uint32_t, TOK_IDENT, "uint32_t");
}

static void test_eof() {
  char *src = "100";
  Lexer *l = new_lexer(src);

  next_token_lexer(l);

  Token *eof = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, eof, TOK_EOF, "\0");  
}

static void test_keyword() {
  char *src = "lambda define let letrec do quote car cdr and or if cond #t #f nil";
  Lexer *l = new_lexer(src);

  Token *lambda = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, lambda, TOK_LAMBDA, "lambda");  

  Token *define = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, define, TOK_DEFINE, "define");  
  Token *let = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, let, TOK_LET, "let");  

  Token *letrec = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, letrec, TOK_LETREC, "letrec");  

  Token *_do = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _do, TOK_DO, "do");  

  Token *quote = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, quote, TOK_QUOTE, "quote");  

  Token *car = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, car, TOK_CAR, "car");  

  Token *cdr = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, cdr, TOK_CDR, "cdr");  

  Token *and = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, and, TOK_AND, "and");  

  Token *or = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, or, TOK_OR, "or");  

  Token *_if = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _if, TOK_IF, "if");  

  Token *cond = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, cond, TOK_COND, "cond");  
  Token *_true = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _true, TOK_TRUE, "#t");

  Token *_false = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _false, TOK_FALSE, "#f"); 

  Token *nil = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, nil, TOK_NIL, "nil"); }

void test_lexer() {
  printf("*test_lexer*\n");
  test_op();
  test_skip();
  test_int();
  test_ident();
  test_eof();
  test_keyword();
  printf("OK\n");
}
