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
  int val, forty_two;
  hash_map *hm;

  hm = hash_map_create(1, sum_chars, my_cmp);

  forty_two = 42;
  hash_map_set(hm, "hello, world!", &forty_two);

  val = *(int*)hash_map_get(hm, "hello, world!");
  printf("Got value: %d\n", val);

  hash_map_delete(hm, "hello, world!");
  hash_map_destroy(hm);
  return 0;
}