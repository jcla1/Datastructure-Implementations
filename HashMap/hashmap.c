#include <stdlib.h>
#include "hashmap.h"

hash_map *hash_map_create(int num_buckets, hash_fn_t fn) {
  hash_map *hm = (hash_map*)malloc(sizeof (hash_map));

  hm->buckets = (pair**)malloc(num_buckets * sizeof(pair*));
  hm->num_buckets = num_buckets;
  hm->fn = fn;

  return hm;
}

void hash_map_set(hash_map *hm, void *key, void *value) {
  pair *p;
  int hash = hm->fn(key);

  p = (pair*)malloc(sizeof(pair));
  p->fst = key;
  p->snd = value;


  hm->buckets[(hash % hm->num_buckets) * sizeof(pair*)] = p;
}

void *hash_map_get(hash_map *hm, void *key) {
  pair *p;
  int hash = hm->fn(key);

  p = hm->buckets[(hash % hm->num_buckets) * sizeof(pair*)];

  return p->snd;
}