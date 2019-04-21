#include <stdio.h>
#include <editline/readline.h>
#include <editline/history.h>
#include "formulae.h"

#define PROMPT ">> "

void repl() {
  while(1) {
    char *input = readline(PROMPT);
    add_history(input);

    Lexer *l = new_lexer(input);
    Parser *p = new_parser(l);
    SExpr *sexpr = parse_sexpr(p);
    SExpr *result = eval(sexpr);

    if(sexpr != NULL)
      printf("%s\n", inspect_sexpr(result));
  }
}
