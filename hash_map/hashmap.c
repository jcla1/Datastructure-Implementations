#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"

void pair_destroy(pair *p) {
  // TODO: Look into who is responsible for free-ing key & value
  free(p);
}

hash_map *hash_map_create(int num_buckets, hash_fn_t hash_fn, cmp_fn_t cmp_fn) {
  hash_map *hm = (hash_map*)calloc(1, sizeof(hash_map));
  if (hm == NULL)
    return NULL;

  hm->buckets = (pair**)calloc(num_buckets, sizeof(pair*));
  if (hm->buckets == NULL) {
    free(hm);
    return NULL;
  }

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

void hash_map_set(hash_map *hm, const void *key, const void *value) {
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
  hm->ocupied_buckets++;
}

const void *hash_map_get(const hash_map *hm, const void *key) {
  int idx = hash_map_get_index(hm, key, 0);

  if(idx < 0) {
    fprintf(stderr, "[hash_map_get]: key not found in table\n");
    return NULL;
  }

  return hm->buckets[idx]->snd;
}

void hash_map_delete(hash_map *hm, const void *key) {
  pair **p;
  int idx = hash_map_get_index(hm, key, 0);

  if(idx < 0)
    return;

  p = &hm->buckets[idx];
  pair_destroy(*p);
  *p = NULL;

  hm->ocupied_buckets--;
}

void hash_map_traverse(hash_map *hm, traverse_fn_t fn, void *arg) {
  pair *p;

  for(int i = 0; i < hm->num_buckets; i++) {
    p = hm->buckets[i];
    if(p != NULL)
      fn(p->fst, p->snd, arg);
  }
}

// Allocate space for n additional elements
// Warning: may copy all/rehash.
void hash_map_resize(hash_map *hm, int n) {
  hash_map *tmp_hm;
  int buckets_left;

  // If we've still got enough space, exit early
  buckets_left = hm->num_buckets - hm->ocupied_buckets;
  if(buckets_left >= n || n < 0) {
    return;
  }


  if((tmp_hm = hash_map_create(hm->num_buckets + n - buckets_left, hm->hash_fn, hm->cmp_fn)) == NULL) {
    fprintf(stderr, "[hash_map_resize]: error allocating temp hash map\n");
    return;
  }

  pair *p;
  for(int i = 0; i < hm->num_buckets; i++) {
    if((p = hm->buckets[i]) != NULL) {
      hash_map_set(tmp_hm, p->fst, p->snd);
    }
  }

  hm->num_buckets += n - buckets_left;
  tmp_hm->num_buckets -= n - buckets_left;

  pair **old_buckets = hm->buckets;
  hm->buckets = tmp_hm->buckets;
  tmp_hm->buckets = old_buckets;

  hash_map_destroy(tmp_hm);
}

// the is_free parameter states if the cell searched for is allowed to be NULL
static int hash_map_get_index(const hash_map *hm, const void *key, int is_free) {
  int hash = hm->hash_fn(key);
  int orig_idx = hash % hm->num_buckets;
printf("%s\n", key);
  if((hm->buckets[orig_idx] == NULL && is_free)
      || (!is_free && hm->buckets[orig_idx] != NULL && hm->cmp_fn(hm->buckets[orig_idx]->fst, key) == 0))
      return orig_idx;

  for(int idx = orig_idx + 1; idx != orig_idx; idx++) {
    if(idx == hm->num_buckets) {
      idx = -1;
      continue;
    }

    if((hm->buckets[idx] == NULL && is_free)
      || (!is_free && hm->buckets[idx] != NULL && hm->cmp_fn(hm->buckets[idx]->fst, key) == 0))
      return idx;
  }

  return -1; // no free space or key not found
}
