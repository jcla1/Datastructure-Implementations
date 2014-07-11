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

#endif // DATASTRUCTURES_BLOOM_FILTER_H_