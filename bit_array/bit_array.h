#include <stdint.h>

#ifndef DATASTRUCUTRES_BIT_ARRAY_H_
#define DATASTRUCUTRES_BIT_ARRAY_H_

typedef struct bit_array bit_array;
struct bit_array {
  uint32_t num_bits;
  uint8_t *bits;
};

bit_array *bit_array_create(uint32_t num_bits);
void bit_array_destroy(bit_array *ba);
int bit_array_get(bit_array *ba, uint32_t index);
int bit_array_set(bit_array *ba, uint32_t index);
int bit_array_unset(bit_array *ba, uint32_t index);
int bit_array_copy(bit_array *in, bit_array *out);

#endif // DATASTRUCUTRES_BIT_ARRAY_H_