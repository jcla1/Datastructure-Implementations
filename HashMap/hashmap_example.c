#include <stdio.h>
#include <string.h>
#include "hashmap.h"

int sum_chars(const void *str) {
  char *c = (char*)str;
  int sum = 0;

  int i = -1;
  while(c[++i] != 0) {
    sum += c[i];
  }

  return sum;
}

int my_cmp(const void *s1, const void *s2) {
  return strcmp((char*)s1, (char*)s2);
}

void my_traverse(const void *key, const void *value) {
  printf("%s -> %d\n", (char*)key, *(int*)value);
}

int main() {
  int val, forty_two;
  hash_map *hm;

  hm = hash_map_create(20, sum_chars, my_cmp);

  forty_two = 42;
  hash_map_set(hm, "ad", &forty_two);

  hash_map_traverse(hm, my_traverse);

  hash_map_destroy(hm);
  return 0;
}