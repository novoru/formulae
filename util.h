#ifndef UTIL_H
#define UTIL_H

#include <setjmp.h>
#include <stdnoreturn.h>
#include <gc.h>

#define malloc GC_MALLOC

// Vector
#define INIT_VEC_SIZE 8

typedef struct Vector{
  void **data;
  size_t len;
  size_t size;
} Vector;

Vector *new_vec();
void vec_push(Vector *vec, void *data);

// Map
typedef struct Map{
  Vector *keys;
  Vector *vals;
} Map;

Map *new_map();
void map_push(Map *map, char *key, void *val);
void *map_get(Map *map, char *key);

// error

enum {
  ERR_WARNING = 1,
  ERR_ERROR = 2,
  ERR_FATAL = 3,
};
extern jmp_buf err_env;
noreturn void error(char *fmt, ...) __attribute__((format(printf, 1, 2)));

// formatter
char *format(char *fmt, ...) __attribute__((format(printf, 1, 2)));

// string
char *substr(char *str, size_t start, size_t len);

// test
void expect_int(char *file, int line, int actual, int expected);
void expect_str(char *file, int line, char *actual, char *expected);

#endif
