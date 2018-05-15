#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include "array.h"

typedef struct {
  array_t* content[4096];
  size_t len;
} dictionary_t;

dictionary_t* dictionary_new();
dictionary_t* dictionary_add(dictionary_t* dic, const array_t* e);
bool dictionary_is_in(const dictionary_t* dic, const array_t* e);
int dictionary_get_code(const dictionary_t* dic, const array_t* e);
const array_t* dictionary_get_entry(const dictionary_t* dic, int code);
void dictionary_free(dictionary_t* dic);

#endif
