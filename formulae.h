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

// obj.c
typedef enum {
  OBJ_PAIR,
  OBJ_SYMBOL,
  OBJ_STRING,
  OBJ_NUM,
  OBJ_FLOAT,
  OBJ_NIL,
} ObjKind;

typedef struct Object{
  ObjKind kind;

  union {
    // pair
    struct {
      struct Object *car;
      struct Object *cdr;
    };

    // symbol
    Token *tok;

    // string
    char *str;

    // number
    int num;

    // floating point number
    float fnum;
  };
  
} Object;

#define FML_CAR(obj)        (obj->car)
#define FML_CDR(obj)        (obj->cdr)
#define FML_CAAR(obj)       (FML_CAR(FML_CAR(obj)))
#define FML_CADR(obj)       (FML_CAR(FML_CDR(obj)))
#define FML_CDAR(obj)       (FML_CDR(FML_CAR(obj)))
#define FML_CDDR(obj)       (FML_CDR(FML_CDR(obj)))
#define FML_PAIR(car, cdr)  (new_obj_pair(car, cdr))
#define FML_SYMBOL(tok)     (new_obj_symbol(tok))
#define FML_STR(str)        (new_obj_str(str))
#define FML_NUM(num)        (new_obj_num(num))
#define FML_FLOAT(fnum)     (new_obj_float(fnum))
#define FML_NIL()           (new_obj_nil())

Object *new_obj_pair(Object *car, Object *cdr);
Object *new_obj_symbol(Token *tok);
Object *new_obj_str(char *s);
Object *new_obj_num(int n);
Object *new_obj_float(float f);
Object *new_obj_nil();
void obj_append(Object *obj, Object *cdr);
char *inspect_obj(Object *obj);
Object *apply_proc(Object *proc, Object *list);

// parser.c
typedef struct Parser{
  Lexer *l;
  Token *curTok;
  Token *peekTok;
} Parser;

Parser *new_parser(Lexer *l);
void next_token_parser(Parser *p);
Object *parse_sexpr(Parser *p);

// repl.c
void repl();

// eval.c
Object *eval(Object *sexpr);

#endif
