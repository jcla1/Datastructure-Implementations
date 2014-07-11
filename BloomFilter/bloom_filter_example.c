#include <stdio.h>
#include "bloom_filter.h"

int main(void) {
  bloom_filter *bf;

  bf = bloom_filter_create(128, 3);
  bloom_filter_add(bf, "hello, world", 14);
  printf("\"hello, world!\" is in bloom filter: %d\n", bloom_filter_check(bf, "hello, world!", 14));
  bloom_filter_destroy(bf);

  return 0;
}