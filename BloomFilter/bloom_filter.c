#include <stdlib.h>
#include "bloom_filter.h"

bloom_filter *bloom_filter_create(int num_bits) {
    // We only allow a number of bits that are
    // a multiple of 8 (because char == 8 bits)
    if(num_bits & 7 != 0)
        return NULL;

    bloom_filter *bf = malloc(sizeof(bloom_filter));
    if(bf == NULL)
        return NULL;

    bf->bits = calloc(num_bits / 8, 1);
    if(bf->bits == NULL) {
        free(bf);
        return NULL;
    }

    bf->num_bits = num_bits;

    return bf;
}

void bloom_filter_destroy(bloom_filter *bf) {
    free(bf->bits);
    free(bf);
}