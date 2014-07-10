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

int main() {
  int val, forty_two;
  hash_map *hm;

  hm = hash_map_create(20, sum_chars, my_cmp);

  forty_two = 42;
  hash_map_set(hm, "ad", &forty_two);

  val = *(int*)hash_map_get(hm, "ad");
  printf("Got value: %d\n", val);

  hash_map_destroy(hm);
  return 0;
}