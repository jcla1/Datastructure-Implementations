#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"

void pair_destroy(pair *p) {
  // TODO: Look into who is responsible for free-ing key & value
  free(p);
}

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

  for(int i = 0; i < hm->num_buckets; i++) {
    if ((p = (hm->buckets[i])) != NULL) {
      pair_destroy(p);
    }
  }

  free(hm->buckets);
  free(hm);
}

void hash_map_set(hash_map *hm, void *key, void *value) {
  int idx;
  pair *p;

  p = (pair*)malloc(sizeof(pair));
  if (p == NULL) {
      fprintf(stderr, "[hash_map_set]: error allocating pair\n");
      return;
  }

  p->fst = key;
  p->snd = value;

  idx = hash_map_get_index(hm, key, 1);
  if(idx < 0) {
    fprintf(stderr, "[hash_map_set]: not enough space.\n");
    return;
  }

  hm->buckets[idx] = p;
}

void *hash_map_get(const hash_map *hm, void *key) {
  int idx = hash_map_get_index(hm, key, 0);

  if(idx < 0) {
    fprintf(stderr, "[hash_map_get]: key not found in table\n");
    return NULL;
  }

  return hm->buckets[idx]->snd;
}

void hash_map_delete(hash_map *hm, void *key) {
  int idx = hash_map_get_index(hm, key, 0);

  if(idx < 0)
    return;

  pair **p = &hm->buckets[idx];
  pair_destroy(*p);
  *p = NULL;
}

// the is_free parameter states if the cell searched for is allowed to be NULL
static int hash_map_get_index(const hash_map *hm, void *key, int is_free) {
  int hash = hm->hash_fn(key);
  int orig_idx = hash % hm->num_buckets;

  if((hm->buckets[orig_idx] == NULL && is_free)
      || (!is_free && hm->cmp_fn(hm->buckets[orig_idx]->fst, key) == 0))
      return orig_idx;


  for(int idx = orig_idx + 1; idx != orig_idx; idx++) {
    if(idx == hm->num_buckets) {
      idx = -1;
      continue;
    }

    if((hm->buckets[idx] == NULL && is_free)
      || (!is_free && hm->cmp_fn(hm->buckets[idx]->fst, key) == 0))
      return idx;
  }

  return -1; // no free space or key not found
}
