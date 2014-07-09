#include <stdio.h>
#include <string.h>
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

int my_cmp(void *s1, void *s2) {
  return strcmp((char*)s1, (char*)s2);
}

int main() {
  hash_map *hm = hash_map_create(15, sum_chars, my_cmp);

  int forty_two = 42;
  hash_map_set(hm, "hello, world!", &forty_two);

  int val = *(int*)hash_map_get(hm, "hello, world!");

  hash_map_destroy(hm);

  printf("Got value: %d\n", val);
  return 0;
}