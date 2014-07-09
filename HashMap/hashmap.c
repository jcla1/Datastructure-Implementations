#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"

hash_map *hash_map_create(int num_buckets, hash_fn_t hash_fn, cmp_fn_t cmp_fn) {
  hash_map *hm = (hash_map*)malloc(sizeof(hash_map));
  if (hm == NULL)
    return NULL;

  hm->buckets = (pair**)calloc(num_buckets, sizeof(pair*));
  if (hm->buckets == NULL) {
    free(hm);
    return NULL;
  }

  hm->ocupied_buckets = 0;
  hm->num_buckets = num_buckets;
  hm->hash_fn = hash_fn;
  hm->cmp_fn = cmp_fn;

  return hm;
}

void hash_map_destroy(hash_map *hm) {
  if (hm == NULL)
    return;

  pair *p;

  for (int i = 0; i < hm->num_buckets; i++) {
    if ((p = (hm->buckets[i])) != NULL) {
      free(p);
    }
  }

  free(hm->buckets);
  free(hm);
}

void hash_map_set(hash_map *hm, void *key, void *value) {
  pair *p;
  int hash;

  p = (pair*)malloc(sizeof(pair));
  if (p == NULL) {
      fprintf(stderr, "[hash_map_set]: error allocating pair\n");
      return;
  }

  p->fst = key;
  p->snd = value;

  hash = hm->hash_fn(key);

  hm->buckets[hash % hm->num_buckets] = p;
}

void *hash_map_get(hash_map *hm, void *key) {
  pair *p;
  int hash;

  hash = hm->hash_fn(key);
  p = hm->buckets[hash % hm->num_buckets];

  if (p == NULL || hm->cmp_fn(p->fst, key) != 0) {
    fprintf(stderr, "[hash_map_get]: key not found in table\n");
    return NULL;
  }


  return p->snd;
}