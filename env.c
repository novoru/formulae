#include <stdio.h>
#include "formulae.h"
#include "util.h"

Env *new_env() {
  Env *env = malloc(sizeof(Env));
  env->store = new_map();

  return env;
}

Env *new_enclosed_env(Env *outer) {
  Env *env = new_env();
  env->outer = outer;

  return env;
}

Object *get_env(Env *env, char *name) {
  Object *obj = (Object *)map_get(env->store, name);
  Env *tmp = env->outer;
    
  while(obj == NULL && tmp!= NULL) {
    obj = map_get(tmp->store, name);
    if(tmp->outer != NULL)
      tmp = tmp->outer;
    else
      break;
  }
  
  return obj;
}

Object *set_env(Env *env, char *name, Object *obj) {
  map_push(env->store, name, (void *)obj);

  return obj;
}

void init_env(Env *env) {
  register_builtin(env, "+", -1, (void *)builtin_add);
  register_builtin(env, "-", -1, (void *)builtin_sub);
  register_builtin(env, "*", -1, (void *)builtin_mult);
  register_builtin(env, "/", -1, (void *)builtin_div);
  register_builtin(env, "=", -1, (void *)builtin_eq);
  register_builtin(env, "<", -1, (void *)builtin_lt);
  register_builtin(env, ">", -1, (void *)builtin_gt);

  register_builtin(env, "length", 1, (void *)builtin_length);
  register_builtin(env, "cons", 2, (void *)builtin_cons);
  register_builtin(env, "car", 1, (void *)builtin_car);
  register_builtin(env, "cdr", 1, (void *)builtin_cdr);
  register_builtin(env, "define", 2, (void *)builtin_define);
  register_builtin(env, "lambda", 2, (void *)builtin_lambda);
  register_builtin(env, "if", -1, (void *)builtin_if);
}

char *inspect_env(Env *env) {
  if(env->store == NULL)
    return "";

  char *s = "";

  if(env->outer != NULL)
    s = format("outer->%s\n", inspect_env(env->outer));

  s = format("{%s ", s);

  for(int i = 0; i < env->store->keys->len; i++) {
    char *key = (char *)env->store->keys->data[i];
    Object *val = (Object *)env->store->vals->data[i];

    if(i == 0)
      s = format("%s%s: %s", s, key, inspect_obj(val));
    else
      s = format("%s, %s: %s", s, key, inspect_obj(val));
  }

  return format("%s }", s);
}
