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
    dest = array_add(dest, src->content[i]);
  }
  return dest;
}

array_t* array_add(array_t* a, int n) {
  if (a->len == a->capacity) {
    a->capacity *= GROWING_FACTOR;
    a->content = (int*)realloc(a->content, a->capacity*sizeof(int));
  }
  a->content[a->len] = n;
  a->len++;
  return a;
}

array_t* array_ints_to_bytes(array_t* a) {
  array_t* tmp = array_new();
  int* src = a->content;
  size_t i;
  for (i = 0 ; i < (a->len - 1) ; i += 2) {
    tmp = array_add(tmp, src[i] >> 4);
    tmp = array_add(tmp, ((src[i] << 4) | ((src[i+1] & 0xF00) >> 8)) & 0xFF);
    tmp = array_add(tmp, src[i] & 0xFF);
  }
  if (a->len % 2 != 0) {
    tmp = array_add(tmp, 10);
  }
  array_free(a);
  return tmp;
}

array_t* array_bytes_to_ints(array_t* a) {
  array_t* tmp = array_new();
  int* src = a->content;
  size_t i;
  for (i = 0 ; i < (a->len - 2) ; i += 3) {
    tmp = array_add(tmp, (src[i] << 4) | (src[i+1] >> 4));
    tmp = array_add(tmp, ((src[i+1] & 0x0F) << 8) & src[i+2]);
  }
  array_free(a);
  return tmp;
}

array_t* array_clear(array_t* a) {
  array_free(a);
  return array_new();
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

void array_free(array_t* a) {
  free(a->content);
  free(a);
}
