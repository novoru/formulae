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

static Object *plus(Object *list) {
  Object *result = new_obj_num(FML_CAR(list)->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num += FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

static Object *minus(Object *list) {
  Object *result = new_obj_num(FML_CAR(list)->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num -= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

static Object *mult(Object *list) {
  Object *result = new_obj_num(FML_CAR(list)->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num *= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
}

static Object *divide(Object *list) {
  Object *result = new_obj_num(FML_CAR(list)->num);
  Object *cdr = FML_CDR(list);
  
  while(!IS_NIL(cdr)) {
    result->num /= FML_CAR(cdr)->num;
    cdr = FML_CDR(cdr);
  }
    
  return result;
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

static void test_proc() {
  // (+ 1 2 3 ) = 6
  Object *obj = FML_PAIR(FML_STR("+"), 
			 FML_PAIR(FML_NUM(1),
				  FML_PAIR(FML_NUM(2),
					   FML_PAIR(FML_NUM(3),
						    FML_NIL())
					   )
				  )
			 );
  
  init_proctbl();
  register_proc(FML_CAR(obj)->str, (void *)plus);
  Object* (*proc)(Object *) = get_proc(FML_CAR(obj)->str);
  Object *result = proc(FML_CDR(obj));

  expect_obj_num(__FILE__, __LINE__, result, 6);

  // (- 5 3 1) = 1
  obj = FML_PAIR(FML_STR("-"), 
		 FML_PAIR(FML_NUM(5),
			  FML_PAIR(FML_NUM(3),
				   FML_PAIR(FML_NUM(1),
					    FML_NIL())
				   )
			  )
		 );
  
  register_proc(FML_CAR(obj)->str, (void *)minus);
  proc = get_proc(FML_CAR(obj)->str);
  result = proc(FML_CDR(obj));

  expect_obj_num(__FILE__, __LINE__, result, 1);

  // (* 1 2 3) = 6
  obj = FML_PAIR(FML_STR("*"), 
		 FML_PAIR(FML_NUM(1),
			  FML_PAIR(FML_NUM(2),
				   FML_PAIR(FML_NUM(3),
					    FML_NIL())
				   )
			  )
		 );
  
  register_proc(FML_CAR(obj)->str, (void *)mult);
  proc = get_proc(FML_CAR(obj)->str);
  result = proc(FML_CDR(obj));

  expect_obj_num(__FILE__, __LINE__, result, 6);

  // (/ 12 2 3) = 2
  obj = FML_PAIR(FML_STR("/"), 
		 FML_PAIR(FML_NUM(12),
			  FML_PAIR(FML_NUM(2),
				   FML_PAIR(FML_NUM(3),
					    FML_NIL())
				   )
			  )
		 );
  
  register_proc(FML_CAR(obj)->str, (void *)divide);
  proc = get_proc(FML_CAR(obj)->str);
  result = proc(FML_CDR(obj));

  expect_obj_num(__FILE__, __LINE__, result, 2);
}

static void test_inspect_obj() {
  Object *obj = FML_PAIR(FML_STR("+"), 
			 FML_PAIR(FML_NUM(1),
				  FML_PAIR(FML_NUM(2),
					   FML_PAIR(FML_NUM(3),
						    FML_NIL())
					   )
				  )
			 );
  
  expect_str(__FILE__, __LINE__, inspect_obj(obj), "(+ . (1 . (2 . (3 . ()))))");
}

static void test_append() {
  // (1 2 3)
  Object *obj1 = FML_PAIR(FML_NUM(1),
			  FML_PAIR(FML_NUM(2),
				   FML_PAIR(FML_NUM(3),
					    FML_NIL()
					    )
				   )
			  );

  // (4 5)
  Object *obj2 = FML_PAIR(FML_NUM(4),
			  FML_PAIR(FML_NUM(5),
				   FML_NIL()
				   )
			  );

  // (1 2 3 4 5)
  Object *concat = append(obj1, obj2);

  expect_obj_num(__FILE__, __LINE__, FML_CAR(concat), 1);
  expect_obj_num(__FILE__, __LINE__, FML_CADR(concat), 2);
  expect_obj_num(__FILE__, __LINE__, FML_CADDR(concat), 3);
  expect_obj_num(__FILE__, __LINE__, FML_CADDDR(concat), 4);
  expect_obj_num(__FILE__, __LINE__, FML_CADDDDR(concat), 5);
  expect_obj_nil(__FILE__, __LINE__, FML_CDDDDDR(concat));
}

void test_object() {
  printf("*test_object*\n");
  test_sexpr();
  test_proc();
  test_inspect_obj();
  test_append();
  printf("OK\n");
}
