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
    Object *obj = parse_expr(p);
    Object *result = eval(obj);

    if(obj != NULL) {
      printf("%s\n", inspect_obj(obj));
      if(result != NULL)
	printf("%s\n", inspect_obj(result));
    }
  }
}
