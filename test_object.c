#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "formulae.h"

static void expect_obj_nil(char *file, int line, Object *obj) {
  if(obj->kind != OBJ_NIL) {
    printf("%s: %d\n", file, line);
    printf("object is not NIL, but %d\n", obj->kind);
    exit(1);
  }
}

static void expect_obj_num(char *file, int line, Object *obj, int num) {
  if(obj->kind != OBJ_NUM) {
    printf("%s: %d\n", file, line);
    printf("object is not INT, but %d\n", obj->kind);
    exit(1);
  }
  if(obj->num != num) {
    printf("%s: %d\n", file, line);
    printf("expected: %d, actual: %d\n",num, obj->num);
    exit(1);
  }
}

static void expect_obj_str(char *file, int line, Object *obj, char *str) {
  if(obj->kind != OBJ_STRING) {
    printf("%s: %d\n", file, line);
    printf("object is not STRING, but %d\n", obj->kind);
    exit(1);
  }
  if(strcmp(obj->str, str) != 0) {
    printf("%s: %d\n", file, line);
    printf("expected: %s, actual: %s\n",str, obj->str);
    exit(1);
  }
}

static void test_sexpr() {
  Object *obj = FML_PAIR(
			 FML_PAIR(FML_NUM(1), FML_NUM(2)),
			 FML_PAIR(FML_STR("foo"), FML_NIL())
			 );
  expect_obj_num(__FILE__, __LINE__, FML_CAAR(obj), 1);
  expect_obj_str(__FILE__, __LINE__, FML_CADR(obj), "foo");
  expect_obj_nil(__FILE__, __LINE__, FML_CDDR(obj));
}

void test_object() {
  printf("*test_object*\n");
  test_sexpr();
  printf("OK\n");
}
