#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef char octet_t;

typedef struct {
  octet_t seq[BUFSIZ];
  size_t size;
} word_t;

#define WORD_ADD(w, o) \
  do { \
    w.seq[w.size] = o; \
    w.size++; \
    w.seq[w.size] = '\0'; \
  } while (0)

#define WORD_RESET(w) \
  do { \
    w.seq[0] = '\0'; \
    w.size = 0; \
  } while (0)

  bool dic_is_entry_existent(const word_t* w);
  int dic_get_entry_code(const word_t* w);
  int dic_add_entry(const word_t* w);

#endif
