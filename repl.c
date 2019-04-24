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
  }
}
