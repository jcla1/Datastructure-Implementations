#include <stdio.h>
#include "bloom_filter.h"

int my_hash(void *item, size_t item_len) {
  char *c = item;
  int sum = 0;

  int i = -1;
  while(c[++i] != 0) {
    sum += c[i];
  }

  return sum;
}

int main(void) {
  bloom_filter *bf;

  bf = bloom_filter_create(8, 1, my_hash);
  bloom_filter_add(bf, "hello, world!", 14);
  printf("\"hello, world!\" is in bloom filter: %d\n", bloom_filter_check(bf, "hello, world!", 14));
  bloom_filter_destroy(bf);

  return 0;
}