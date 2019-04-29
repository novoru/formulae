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
  //  char *src = "foo 100 bar uint32_t";
  char *src = "foo";
  Lexer *l = new_lexer(src);

  Token *foo = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, foo, TOK_IDENT, "foo");  
  /*
  next_token_lexer(l);
  
  Token *bar = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, bar, TOK_IDENT, "bar");

  Token *_uint32_t = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _uint32_t, TOK_IDENT, "uint32_t");
  */
}

static void test_eof() {
  char *src = "100";
  Lexer *l = new_lexer(src);

  next_token_lexer(l);

  Token *eof = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, eof, TOK_EOF, "\0");  
}


static void test_keyword() {
  char *src = "+ - * / lambda define let letrec do quote car cdr and or if cond #t #f nil";
  Lexer *l = new_lexer(src);

  Token *plus = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, plus, TOK_IDENT, "+");  

  Token *minus = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, minus, TOK_IDENT, "-");  

  Token *mult = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, mult, TOK_IDENT, "*");  

  Token *divide = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, divide, TOK_IDENT, "/");  

  Token *lambda = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, lambda, TOK_IDENT, "lambda");  

  Token *define = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, define, TOK_IDENT, "define");  
  Token *let = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, let, TOK_IDENT, "let");  

  Token *letrec = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, letrec, TOK_IDENT, "letrec");  

  Token *_do = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _do, TOK_IDENT, "do");  

  Token *quote = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, quote, TOK_IDENT, "quote");  

  Token *car = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, car, TOK_IDENT, "car");  

  Token *cdr = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, cdr, TOK_IDENT, "cdr");  

  Token *and = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, and, TOK_IDENT, "and");  

  Token *or = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, or, TOK_IDENT, "or");  

  Token *_if = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _if, TOK_IDENT, "if");  

  Token *cond = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, cond, TOK_IDENT, "cond");  
  Token *_true = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _true, TOK_TRUE, "#t");

  Token *_false = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, _false, TOK_FALSE, "#f"); 

  Token *nil = next_token_lexer(l);
  expect_token(__FILE__, __LINE__, nil, TOK_IDENT, "nil"); }

void test_lexer() {
  printf("*test_lexer*\n");
  test_int();
  test_ident();
  test_eof();
  test_keyword();
  printf("OK\n");
}
