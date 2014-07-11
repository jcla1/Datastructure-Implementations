#ifndef DATASTRUCTURES_BLOOM_FILTER_H_
#define DATASTRUCTURES_BLOOM_FILTER_H_

typedef struct bloom_filter {
    int num_bits;
    unsigned char *bits;
} bloom_filter;

#endif // DATASTRUCTURES_BLOOM_FILTER_H_