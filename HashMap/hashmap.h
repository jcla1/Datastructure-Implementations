typedef int (*hash_fn_t)(void *);
typedef int (*cmp_fn_t)(void *, void *);

typedef struct pair {
  void *fst;
  void *snd;
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
void hash_map_set(hash_map *hm, void *key, void *value);
void *hash_map_get(hash_map *hm, void *key);