#include <stdio.h>
#include <stdint.h>
#include "formulae.h"
#include "util.h"

void test_substr() {
  char *s1 = "foo bar";
  expect_str(__FILE__, __LINE__, substr(s1, 0, 3), "foo");
  expect_str(__FILE__, __LINE__, substr(s1, 3, 1), " ");
  expect_str(__FILE__, __LINE__, substr(s1, 4, 3), "bar");
}

void test_vec() {
  Vector *vec = new_vec();
  vec_push(vec, (void*) 0);
  vec_push(vec, (void*) "Hello");
  vec_push(vec, (void*) 10);

  expect_int(__FILE__, __LINE__, (intptr_t)vec->data[0], 0);
  expect_str(__FILE__, __LINE__, (char*)vec->data[1], "Hello");
  expect_int(__FILE__, __LINE__, (intptr_t)vec->data[2], 10);
}

void test_map() {
  Map *map = new_map();
  map_push(map, "foo", (void*)10);
  map_push(map, "bar", (void*)100);
  map_push(map, "fizz", (void*)"hello");
  map_push(map, "buzz", (void*)"world");
  map_push(map, "test1", (void*)"test1");
  map_push(map, "test2", (void*)"test2");
  map_push(map, "test3", (void*)"test3");
  map_push(map, "test4", (void*)"test4");
  map_push(map, "test5", (void*)"test5");
  map_push(map, "test6", (void*)"test6");
  map_push(map, "test7", (void*)"test7");
  map_push(map, "test8", (void*)"test8");

  expect_int(__FILE__, __LINE__, (intptr_t)map_get(map, "foo"), 10);
  expect_int(__FILE__, __LINE__, (intptr_t)map_get(map, "bar"), 100);
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "fizz"), "hello");
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "buzz"), "world");
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "test1"), "test1");
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "test2"), "test2");
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "test3"), "test3");
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "test4"), "test4");
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "test5"), "test5");
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "test6"), "test6");
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "test7"), "test7");
  expect_str(__FILE__, __LINE__, (char*)map_get(map, "test8"), "test8");
}

void test_util() {
  printf("*test_util*\n");
  test_substr();
  test_vec();
  test_map();
  printf("OK\n");
}
