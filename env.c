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

  if(obj == NULL && env->outer != NULL)
    obj = map_get(env->outer->store, name);

  return obj;
}

Object *set_env(Env *env, char *name, Object *obj) {
  map_push(env->store, name, (void *)obj);

  return obj;
}

char *inspect_env(Env *env) {
  if(env->store == NULL)
    return "";

  char *s = "";

  if(env->outer != NULL)
    s = format("%s\n", inspect_env(env->outer));

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