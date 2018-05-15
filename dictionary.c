#include "dictionary.h"

#include <stdlib.h>
#include <string.h>

dictionary_t* dictionary_new() {
  dictionary_t* dic = (dictionary_t*)malloc(sizeof(dictionary_t));
  dic->len = 0;
  int i;
  for (i = 0 ; i < 256 ; ++i) {
    array_t* a = array_new();
    array_add(a, i);
    dictionary_add(dic, a);
  }
  return dic;
}

void dictionary_add(dictionary_t* dic, const array_t* e) {
  dic->content[dic->len] = array_new_from(e);
  ++(dic->len);
}

bool dictionary_is_in(const dictionary_t* dic, const array_t* e) {
  return dictionary_get_code(dic, e) != -1;
}

int dictionary_get_code(const dictionary_t* dic, const array_t* e) {
  size_t i;
  for (i = 0 ; i < dic->len ; ++i) {
    if (array_is_equal(dic->content[i], e)) {
      return i;
    }
  }
  return -1;
}

const array_t* dictionary_get_entry(const dictionary_t* dic, int code) {
  return dic->content[code];
}

void dictionary_free(dictionary_t* dic) {
  size_t i;
  for (i = 0 ; i < dic->len ; ++i) {
    array_free(dic->content[i]);
  }
  free(dic);
}
