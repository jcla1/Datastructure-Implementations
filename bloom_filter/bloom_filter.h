#include "bit_array/bit_array.h"

#ifndef DATASTRUCTURES_BLOOM_FILTER_H_
#define DATASTRUCTURES_BLOOM_FILTER_H_

#define MURMUR_SEED 0

typedef struct bloom_filter bloom_filter;
struct bloom_filter {
    int num_hash_fn;
    bit_array *ba;
};

bloom_filter *bloom_filter_create(int num_bits, int num_hash_fn);
void bloom_filter_destroy(bloom_filter *bf);
void bloom_filter_add(bloom_filter *bf, void *item, size_t item_len);
int bloom_filter_check(bloom_filter *bf, void *item, size_t item_len);
int bloom_filter_copy(bloom_filter *in, bloom_filter *out);

#endif // DATASTRUCTURES_BLOOM_FILTER_H_