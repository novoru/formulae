#include <stdio.h>
#include <editline/readline.h>
#include <editline/history.h>
#include <setjmp.h>
#include "formulae.h"
#include "util.h"

#define PROMPT ">> "

void repl() {
  Env *env = new_env();

  while(1) {
    if(setjmp(err_env) != 0)
      printf("continue...\n");
    
    char *input = readline(PROMPT);
    add_history(input);

    Lexer *l = new_lexer(input);
    Parser *p = new_parser(l);
    Object *obj = parse_expr(p);

    if(obj == NULL)
      continue;
    
    printf("%s\n", inspect_obj(obj));

    Object *result = eval(env, obj);

    if(obj == NULL)
      continue;
    
    printf("%s\n", inspect_obj(result));
  }
}
