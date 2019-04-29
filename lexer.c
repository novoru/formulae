#include "formulae.h"
#include "util.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Lexer *new_lexer(char *src) {
  Lexer *l = malloc(sizeof(Lexer));
  l->src = src;
  l->pos = 0;

  return l;
}

void skip(Lexer *l) {
  while( l->src[l->pos] == ' '  || l->src[l->pos] == '\n' ||
	 l->src[l->pos] == '\r' || l->src[l->pos] == '\t')
    l->pos++;
}

char *read_num(Lexer *l) {
  size_t start = l->pos;
  while(isdigit(l->src[l->pos])) {
    l->pos++;
    if(l->src[l->pos] == '\0') {
      break;
    }
  }

  return substr(l->src, start, l->pos-start);
}

char *read_ident(Lexer *l) {
  size_t start = l->pos;
  while(isalnum(l->src[l->pos]) || strchr("!$%&*+-./:<=>?@^_~", l->src[l->pos])) {
    l->pos++;
    if(l->src[l->pos] == '\0')
      break;
  }

  return substr(l->src, start, l->pos-start);
}

Token *next_token_lexer(Lexer *l) {
  skip(l);
  Token *tok;

  switch(l->src[l->pos]) {
  case '(':
    tok = new_token(TOK_LPAREN, "(");
    break;
  case ')':
    tok = new_token(TOK_RPAREN, ")");
    break;
  case ';':
    tok = new_token(TOK_SEMICOLON, ";");
    break;
  case '\'':
    tok = new_token(TOK_SINGLE_QUOTE, "\'");
    break;
  case '`':
    tok = new_token(TOK_BACK_QUOTE, "`");
    break;
  case ',':
    tok = new_token(TOK_COMMA, ",");
    break;
  case '@':
    tok = new_token(TOK_AT, "@");
    break;
  case '"':
    tok = new_token(TOK_DOUBLE_QUOTE, "\"");
    break;
  case '\\':
    tok = new_token(TOK_BACK_SLASH, "\\");
    break;
  case '{':
    tok = new_token(TOK_LBRACE, "{");
    break;
  case '}':
    tok = new_token(TOK_RBRACE, "}");
    break;
  case '[':
    tok = new_token(TOK_LBRACKET, "[");
    break;
  case ']':
    tok = new_token(TOK_RBRACKET, "]");
    break;
  case '#':
    if(l->src[l->pos+1] == 't') {
      tok = new_token(TOK_TRUE, "#t");
      l->pos++;
    }
    else if(l->src[l->pos+1] == 'f') {
      tok = new_token(TOK_FALSE, "#f");
      l->pos++;
    }
    else
      tok = new_token(TOK_SHARP, "#");
    break;
  case '\0':
    tok = new_token(TOK_EOF, "\0");
    return tok;    
  default:
    if(isdigit(l->src[l->pos])) {
      char *lit = read_num(l);
      tok = new_token(TOK_NUM, lit);
      return tok;
    }
    else if(isalnum(l->src[l->pos]) || strchr("!$%&*+-./:<=>?@^_~", l->src[l->pos])) {
      char *lit = read_ident(l);
      tok = new_token(TOK_IDENT, lit);
      return tok;
    }
    else
      tok = new_token(TOK_ILLEGAL, "");
    break;
  }

  l->pos++;
  
  return tok;
}
