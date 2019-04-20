#ifndef FORMULAE_H
#define FORMULAE_H

#include <stddef.h>
#include "formulae.h"

// token.c
typedef enum {
  TOK_ILLEGAL = 256,
  TOK_EOF,
  
  TOK_IDENT,    
  TOK_NUM,

  TOK_ASSIGN,   // =
  TOK_PLUS,     // +
  TOK_MINUS,    // -
  TOK_BANG,     // !
  TOK_ASTERISK, // *
  TOK_SLASH,    // /
  TOK_DOT,      // .

  TOK_LT,       // <
  TOK_LTE,      // <=
  TOK_GT,       // >
  TOK_GTE,      // >=
  
  TOK_LPAREN,   // (
  TOK_RPAREN,   // )

  TOK_SEMICOLON,    // ;
  TOK_SINGLE_QUOTE, // '
  TOK_BACK_QUOTE,   // `
  TOK_COMMA,        // ,
  TOK_AT,           // @
  TOK_DOUBLE_QUOTE, // "
  TOK_BACK_SLASH,   // 
  TOK_LBRACE,       // {
  TOK_RBRACE,       // }
  TOK_LBRACKET,     // [
  TOK_RBRACKET,     // ]
  TOK_SHARP,        // #

  TOK_LAMBDA,   // lambda
  TOK_DEFINE,   // define
  TOK_LET,      // let
  TOK_LETREC,   // letrec
  TOK_DO,       // do
  TOK_QUOTE,    // quote

  TOK_CAR,      // car
  TOK_CDR,      // cdr
  
  TOK_AND,      // and
  TOK_OR,       // or

  TOK_TRUE,     // #t
  TOK_FALSE,    // #f
  TOK_NIL,      // nil
  
  TOK_IF,       // if
  TOK_COND,     // cond
} TokenKind;

typedef struct Token{
  TokenKind kind;
  char *lit;
} Token;

Token *new_token(TokenKind kind, char *lit);
char *inspect_token_kind(TokenKind kind);

// lexer.c
typedef struct Lexer{
  char *src;
  size_t pos;
} Lexer;

Lexer *new_lexer(char *src);
Token *next_token_lexer(Lexer *l);

// sexpr.c
typedef enum {
  SE_LIST,
  SE_SYMBOL,
  SE_STRING,
  SE_INT,
  SE_FLOAT,
  SE_NIL,
} SExprKind;

typedef struct SExpr{
  SExprKind kind;
  union {
    // list
    struct {
      struct SExpr *car;
      struct SExpr *cdr;
    };

    // symbol
    Token *symbol;

    // string
    char *str;

    // integer
    int num;

    // float
    float fnum;
  };
} SExpr;

SExpr *new_sexpr(SExpr *car, SExpr *cdr);
SExpr *new_sexpr_symbol(Token *tok);
SExpr *new_sexpr_str(char *str);
SExpr *new_sexpr_int(int num);
SExpr *new_sexpr_float(float fnum);
SExpr *new_sexpr_nil();
void sexpr_append(SExpr *sepxr, SExpr *cdr);
char *inspect_sexpr(SExpr *sexpr);

// parser.c
typedef struct Parser{
  Lexer *l;
  Token *curTok;
  Token *peekTok;
} Parser;

Parser *new_parser(Lexer *l);
void next_token_parser(Parser *p);
SExpr *parse_sexpr(Parser *p);

// repl.c
void repl();

#endif
