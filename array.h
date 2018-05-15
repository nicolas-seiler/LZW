#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct {
  int* content;
  size_t len, capacity;
} array_t;

array_t* array_new();
array_t* array_new_from(const array_t* src);
array_t* array_add(array_t* a, int n);
array_t* array_ints_to_bytes(array_t* a);
array_t* array_bytes_to_ints(array_t* a);
array_t* array_clear(array_t* a);
bool array_is_equal(const array_t* a0, const array_t* a1);
void array_free(array_t* a);

#endif
