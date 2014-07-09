typedef int (*hash_fn_t)(void *);

typedef struct pair {
  void *fst;
  void *snd;
} pair;

typedef struct hash_map {
  int num_buckets;
  hash_fn_t fn;

  pair **buckets;
} hash_map;

hash_map *hash_map_create(int num_buckets, hash_fn_t fn);
void hash_map_set(hash_map *hm, void *key, void *value);
void *hash_map_get(hash_map *hm, void *key);