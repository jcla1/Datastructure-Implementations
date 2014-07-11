#ifndef DATASTRUCTURES_BLOOM_FILTER_H_
#define DATASTRUCTURES_BLOOM_FILTER_H_

typedef int (*hash_fn)(void *, size_t);

typedef struct bloom_filter {
    int num_bits;
    int num_hash_fn;
    hash_fn *hash_funcs;
    unsigned char *bits;
} bloom_filter;

bloom_filter *bloom_filter_create(int num_bits, int num_hash_fn, ...);
void bloom_filter_destroy(bloom_filter *bf);
void bloom_filter_add(bloom_filter *bf, void *item, size_t item_len);
int bloom_filter_check(bloom_filter *bf, void *item, size_t item_len);

static void bloom_filter_get_hashes(bloom_filter *bf, void *item, size_t item_len, int *hashes);
static void bloom_filter_set_bits(bloom_filter *bf, int *hashes);
static int bloom_filter_get_bits(bloom_filter *bf, int *hashes);

#endif // DATASTRUCTURES_BLOOM_FILTER_H_