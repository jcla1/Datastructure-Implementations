#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include "murmur3.h"
#include "bloom_filter.h"

bloom_filter *bloom_filter_create(int num_bits, int num_hash_fn) {
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

  bf->num_bits = num_bits;
  bf->num_hash_fn = num_hash_fn;

  return bf;
}

void bloom_filter_destroy(bloom_filter *bf) {
  free(bf->bits);
  free(bf);
}

void bloom_filter_add(bloom_filter *bf, void *item, size_t item_len) {
  uint64_t hash1, hash2, combined_hash;
  uint64_t hash[2];
  int bit_index;

  MurmurHash3_x64_128(item, item_len, MURMUR_SEED, hash);

  hash1 = hash[0];
  hash2 = hash[1];

  combined_hash = hash1;
  for(int i = 0; i < bf->num_hash_fn; i++) {
    bit_index = (combined_hash & UINT64_MAX) % bf->num_bits;
    bf->bits[bit_index / 8] |= 1 << (bit_index % 8);
    combined_hash += hash2;
  }
}

int bloom_filter_check(bloom_filter *bf, void *item, size_t item_len) {
  uint64_t hash1, hash2, combined_hash;
  uint64_t hash[2];
  int bit_index;

  MurmurHash3_x64_128(item, item_len, MURMUR_SEED, hash);

  hash1 = (uint64_t)hash[0];
  hash2 = (uint64_t)hash[1];

  combined_hash = hash1;
  for(int i = 0; i < bf->num_hash_fn; i++) {
    bit_index = (combined_hash & UINT64_MAX) % bf->num_bits;
    if((bf->bits[bit_index / 8] & 1 << (bit_index % 8)) == 0)
      return 0;
    combined_hash += hash2;
  }

  return 1;
}

int bloom_filter_copy(bloom_filter *in, bloom_filter *out) {
  // Both filters have to have the same size
  if(in->num_bits != out->num_bits)
    return 0;

  // Both filters should to have the same number of hash functions
  if(in->num_hash_fn != out->num_hash_fn)
    return 0;

  for(int i = in->num_bits >> 3; i >= 0; i--)
    out->bits[i] |= in->bits[i];

  return 1;
}