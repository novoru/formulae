#include <string.h>
#include <stdlib.h>
#include "formulae.h"
#include "test.h"

int main(int argc, char **argv) {
  if(argc == 1) {
    repl();
    exit(0);
  }
  
  if(argc < 2)
    exit(1);

  if(argc == 2 && !strcmp(argv[1], "-test")) {
    test_util();
    test_lexer();
    test_object();
    test_parser();
    test_eval();
    exit(0);
  }

  return 0;
}
