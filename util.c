#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

noreturn error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

char *format(char *fmt, ...) {
  char buf[2048];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);

  return strdup(buf);
}

char *substr(char *str, size_t start, size_t len) {
  if(strlen(str) < len)
    return NULL;
  
  char *subs = malloc(sizeof(char)*len+1);
  strncpy(subs, str+start, len);
  subs[len] = '\0';

  return subs;
}

void expect_int(char *file, int line, int actual, int expected) {
  if(expected != actual) {
    printf("%s: %d\n", file, line);
    printf("expected: %d, actual: %d\n", expected, actual);
    exit(1);
  }
}

void expect_str(char *file, int line, char *actual, char *expected) {
  if(strcmp(expected, actual)) {
    printf("%s: %d\n", file, line);
    printf("expected: %s, actual: %s\n", expected, actual);
    exit(1);
  }
}

Vector *new_vec() {
  Vector *vec = malloc(sizeof(Vector));
  vec->data = malloc(sizeof(void*) * INIT_VEC_SIZE);
  vec->len = 0;
  vec->size = INIT_VEC_SIZE;

  return vec;
}

void vec_push(Vector *vec, void *data) {
  if(vec->len > vec->size-1) {
    vec->size *= 2;
    vec->data = realloc(vec->data, sizeof(void*) * vec->size);
  }

  vec->data[vec->len++] = data;
}

Map *new_map() {
  Map *map = malloc(sizeof(Map));
  map->keys = new_vec();
  map->vals = new_vec();

  return map;
}

void map_push(Map *map, char *key, void *val) {
  vec_push(map->keys, (void*)key);
  vec_push(map->vals, val);
}

void *map_get(Map *map, char *key) {
  for(int i = map->keys->len - 1 ; i >= 0; i--) {
    if(!strcmp((char*)map->keys->data[i], key))
      return map->vals->data[i];
  }

  return NULL;
}
