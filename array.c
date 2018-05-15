#include "array.h"

#include <stdlib.h>

#define BASE_CAPACITY 1
#define GROWING_FACTOR 2

array_t* array_new() {
  array_t* a = (array_t*)malloc(sizeof(array_t));
  a->content = (int*)malloc(BASE_CAPACITY*sizeof(int));
  a->len = 0;
  a->capacity = BASE_CAPACITY;
  return a;
}

array_t* array_new_from(const array_t* src) {
  array_t* dest = array_new();
  size_t i;
  for (i = 0 ; i < src->len ; ++i) {
    array_add(dest, src->content[i]);
  }
  return dest;
}

void array_add(array_t* a, int n) {
  if (a->len == a->capacity) {
    a->capacity *= GROWING_FACTOR;
    a->content = (int*)realloc(a->content, a->capacity*sizeof(int));
  }
  a->content[a->len] = n;
  a->len++;
}

bool array_is_equal(const array_t* a0, const array_t* a1) {
  if (a0->len != a1->len) {
    return false;
  }
  size_t i;
  for (i = 0 ; i < a0->len ; ++i) {
    if (a0->content[i] != a1->content[i]) {
      return false;
    }
  }
  return true;
}

void array_ints_to_bytes(array_t* a);
void array_bytes_to_ints(array_t* a);

void array_clear(array_t* a) {
  a->content = (int*)realloc(a->content, BASE_CAPACITY);
  a->len = 0;
  a->capacity = BASE_CAPACITY;
}

void array_free(array_t* a) {
  free(a->content);
  free(a);
}
