#include <stdlib.h>
#include <stdint.h>

#include "bit_array.h"

bit_array *bit_array_create(uint32_t num_bits) {
  bit_array *ba;

  ba = malloc(sizeof(bit_array));
  if(ba == NULL)
    return NULL;

  ba->bits = calloc(num_bits / 8, sizeof(uint8_t));
  if(ba->bits == NULL) {
    free(ba);
    return NULL;
  }

  ba->num_bits = num_bits;

  return ba;
}

void bit_array_destroy(bit_array *ba) {
  free(ba->bits);
  free(ba);
}

int bit_array_get(bit_array *ba, uint32_t index) {
  return (ba->bits[index / 8] & (1 << (index % 8))) > 0;
}

int bit_array_set(bit_array *ba, uint32_t index) {
  if(bit_array_get(ba, index))
    return 0;

  return ba->bits[index / 8] |= 1 << (index % 8);
}

int bit_array_unset(bit_array *ba, uint32_t index) {
  if(bit_array_get(ba, index))
    return ba->bits[index / 8] &= ~(uint8_t)(1 << (index % 8));

  return 0;
}