#include "dictionary.h"

#include <stdio.h>
#include <string.h>

static char* dico[3840];
static size_t nb_of_entry = 0;

bool dic_is_entry_existent(const word_t* w) {
  return dic_get_entry_code(w) != -1;
}

int dic_get_entry_code(const word_t* w) {
  if (w->size == 1) {
    return w->seq[0];
  }
  size_t i = 0;
  while (i < nb_of_entry) {
    if (!strncmp(dico[i], w->seq, w->size-1)) {
      return 255+i;
    }
  }
  return -1;
}

int dic_add_entry(const word_t* w) {
  dico[nb_of_entry] = (char*)malloc((w->size)*sizeof(char));
  strcpy(dico[nb_of_entry], w->seq);
  nb_of_entry++;
  return nb_of_entry;
}
