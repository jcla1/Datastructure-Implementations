#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "bloom_filter.h"

bloom_filter *bloom_filter_create(int num_bits, int num_hash_fn, ...) {
    va_list funcs;
    bloom_filter *bf;
    // We only allow a number of bits that are
    // a multiple of 8 (because char == 8 bits)
    if((num_bits & 7) != 0)
        return NULL;

    // The bloom filter is of no use, when there
    // are no hash functions.
    if(num_hash_fn < 1)
        return NULL;

    bf = malloc(sizeof(bloom_filter));
    if(bf == NULL)
        return NULL;

    bf->bits = calloc(num_bits / 8, 1);
    if(bf->bits == NULL) {
        free(bf);
        return NULL;
    }

    bf->hash_funcs = malloc(sizeof(hash_fn) * num_hash_fn);
    if(bf->hash_funcs == NULL) {
        free(bf->bits);
        free(bf);
        return NULL;
    }

    va_start(funcs, num_hash_fn);
    for(int i = 0; i < num_hash_fn; i++) {
        bf->hash_funcs[i] = va_arg(funcs, hash_fn);
    }
    va_end(funcs);

    bf->num_bits = num_bits;
    bf->num_hash_fn = num_hash_fn;

    return bf;
}

void bloom_filter_destroy(bloom_filter *bf) {
    free(bf->bits);
    free(bf->hash_funcs);
    free(bf);
}

void bloom_filter_add(bloom_filter *bf, void *item, size_t item_len) {
    int *hashes;

    hashes = malloc(sizeof(int) * bf->num_hash_fn);
    if(hashes == NULL) {
        fprintf(stderr, "[bloom_filter_add]: error allocating hash array.\n");
        return;
    }
    bloom_filter_set_hashes(bf, item, item_len, hashes);
}

int bloom_filter_check(bloom_filter *bf, void *item, size_t item_len) {
    return 0;
}

static void bloom_filter_set_hashes(bloom_filter *bf, void *item, size_t item_len, int *hashes) {
    for (int i = 0; i < bf->num_hash_fn; i++) {
        hashes[i] = bf->hash_funcs[i](item, item_len);
    }
}