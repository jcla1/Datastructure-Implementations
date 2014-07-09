#include <stdio.h>
#include "hashmap.h"

int sum_chars(void *str) {
  char *c = (char*)str;
  int sum = 0;

  int i = -1;
  while(c[++i] != 0) {
    sum += c[i];
  }

  return sum;
}

int main() {
  hash_map *hm = hash_map_create(15, sum_chars);

  int forty_two = 42;
  hash_map_set(hm, "hello, world!", &forty_two);

  int val = *(int*)hash_map_get(hm, "hello, world!");

  hash_map_destroy(hm);

  printf("Got value: %d\n", val);
  return 0;
}