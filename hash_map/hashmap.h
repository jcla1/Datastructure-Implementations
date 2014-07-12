#ifndef DATASTRUCTURES_HASHMAP_HASHMAP_H_
#define DATASTRUCTURES_HASHMAP_HASHMAP_H_

typedef int (*hash_fn_t)(const void *);
typedef int (*cmp_fn_t)(const void *, const void *);
typedef void (*traverse_fn_t)(const void *, const void *, void *arg);

typedef struct pair {
  const void *fst;
  const void *snd;
} pair;

typedef struct hash_map {
  int ocupied_buckets;
  int num_buckets;

  hash_fn_t hash_fn;
  cmp_fn_t cmp_fn;

  pair **buckets;
} hash_map;

hash_map *hash_map_create(int num_buckets, hash_fn_t hash_fn, cmp_fn_t cmp_fn);
void hash_map_destroy(hash_map *hm);
void hash_map_set(hash_map *hm, const void *key, const void *value);
const void *hash_map_get(const hash_map *hm, const void *key);
void hash_map_delete(hash_map *hm, const void *key);
void hash_map_traverse(hash_map *hm, traverse_fn_t fn, void *arg);
void hash_map_resize(hash_map *hm, int n);

static int hash_map_get_index(const hash_map *hm, const void *key, int is_free);

#endif // DATASTRUCTURES_HASHMAP_HASHMAP_H_