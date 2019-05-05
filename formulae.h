#ifndef FORMULAE_H
#define FORMULAE_H

#include <stddef.h>
#include "formulae.h"
#include "util.h"

// prototype declaration
typedef struct Env Env;

/*-- token.c --*/
typedef enum {
  TOK_ILLEGAL = 256,
  TOK_EOF,
  
  TOK_IDENT,    
  TOK_NUM,

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

  TOK_TRUE,     // #t
  TOK_FALSE,    // #f
  TOK_NIL,      // nil
  
} TokenKind;

typedef struct Token{
  TokenKind kind;
  char *lit;
} Token;

Token *new_token(TokenKind kind, char *lit);
char *inspect_token_kind(TokenKind kind);

/*-- lexer.c --*/
typedef struct Lexer{
  char *src;
  size_t pos;
} Lexer;

Lexer *new_lexer(char *src);
Token *next_token_lexer(Lexer *l);

/*-- object.c --*/
typedef enum {
  OBJ_PROGRAM,
  OBJ_PAIR,
  OBJ_BUILTIN,
  OBJ_CLOSURE,
  OBJ_SYMBOL,
  OBJ_STRING,
  OBJ_NUM,
  OBJ_FLOAT,
  OBJ_NIL,
} ObjKind;

typedef struct Object{
  ObjKind kind;

  union {
    // program
    struct Vector *program;
    
    // pair
    struct {
      struct Object *car;
      struct Object *cdr;
    };

    // function
    struct {
      struct Env *env;
      union {
	// builtin
	struct {
	  int nargs;
	  void *builtin;
	};
	// closure
	struct {
	  struct Object *args;
	  struct Object *closure;
	};
      };
    };

    // function
    
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

// constructor
#define FML_PROGRAM()       (new_obj_program())    
#define FML_PAIR(car, cdr)  (new_obj_pair(car, cdr))
#define FML_SYMBOL(tok)     (new_obj_symbol(tok))
#define FML_STR(str)        (new_obj_str(str))
#define FML_NUM(num)        (new_obj_num(num))
#define FML_FLOAT(fnum)     (new_obj_float(fnum))
#define FML_NIL()           (new_obj_nil())

// utility
#define FML_CAR(obj)        (obj->car)
#define FML_CDR(obj)        (obj->cdr)
#define FML_CAAR(obj)       (FML_CAR(FML_CAR(obj)))
#define FML_CADR(obj)       (FML_CAR(FML_CDR(obj)))
#define FML_CDAR(obj)       (FML_CDR(FML_CAR(obj)))
#define FML_CDDR(obj)       (FML_CDR(FML_CDR(obj)))
#define FML_CADDR(obj)      (FML_CAR(FML_CDDR(obj)))
#define FML_CDDDR(obj)      (FML_CDR(FML_CDDR(obj)))
#define FML_CADDDR(obj)     (FML_CAR(FML_CDDDR(obj)))
#define FML_CDDDDR(obj)     (FML_CDR(FML_CDDDR(obj)))
#define FML_CADDDDR(obj)    (FML_CAR(FML_CDDDDR(obj)))
#define FML_CDDDDDR(obj)    (FML_CDR(FML_CDDDDR(obj)))
#define IS_PAIR(obj)        (obj->kind == OBJ_PAIR)
#define IS_BUILTIN(obj)     (obj->kind == OBJ_BUILTIN)
#define IS_CLOSURE(obj)     (obj->kind == OBJ_CLOSURE)
#define IS_SYMBOL(obj)      (obj->kind == OBJ_SYMBOL)
#define IS_STRING(obj)      (obj->kind == OBJ_STRING)
#define IS_NUM(obj)         (obj->kind == OBJ_NUM)
#define IS_FNUM(obj)        (obj->kind == OBJ_FNUM)
#define IS_NIL(obj)         (obj->kind == OBJ_NIL)

typedef Object* (*Proc)(Object *list);

// global scope
struct Map *proctbl;  // procedure

enum {
  FML_LIST_DOTTED = -1,
  FML_LIST_CIRCULAR = -2,
};

Object *new_obj_program();
Object *new_obj_pair(Object *car, Object *cdr);
Object *new_obj_builtin(Env *outer, int nargs, void *b);
Object *new_obj_closure(Env *outer, Object *args, Object *c);
Object *new_obj_symbol(Token *tok);
Object *new_obj_str(char *s);
Object *new_obj_num(int n);
Object *new_obj_float(float f);
Object *new_obj_nil();
Object *append(Object *list, Object *cdr);
char *inspect_obj(Object *obj);
char *inspect_obj_kind(Object *obj);
int len_obj(Object *obj);

/*-- builtin.c --*/

Object *builtin_add(Env *env, Object *list);
Object *builtin_sub(Env *env, Object *list);
Object *builtin_mult(Env *env, Object *list);
Object *builtin_div(Env *env, Object *list);
Object *builtin_cons(Env *env, Object *list);
Object *builtin_car(Env *env, Object *list);
Object *builtin_cdr(Env *env, Object *list);
Object *builtin_length(Env *env, Object *list);
Object *builtin_define(Env *env, Object *list);
Object *builtin_lambda(Env *env, Object *list);
void register_builtin(Env *env, char *name, int nargs, void *b);

/*-- parser.c --*/
typedef struct Parser{
  Lexer *l;
  Token *curTok;
  Token *peekTok;
} Parser;

Parser *new_parser(Lexer *l);
void next_token_parser(Parser *p);
Object *parse_expr(Parser *p);

/*-- repl.c --*/
void repl();

/*-- eval.c --*/
Object *eval(Env *env, Object *obj);

/*-- env.c --*/ 
typedef struct Env{
  struct Env *outer;
  Map *store;
}Env;

Env *new_env();
Env *new_enclosed_env(Env *outer);
Object *get_env(Env *env, char *name);
Object *set_env(Env *env, char *name, Object *obj);
void init_env(Env *env);
char *inspect_env(Env *env);

#endif
