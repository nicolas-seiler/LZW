#include "lzw.h"

#include <stdio.h>
#include "array.h"
#include "dictionary.h"

static void _write_array(const char* dest_path, const array_t* a) {
  FILE* dest_file = fopen(dest_path, "w+");
  size_t i;
  for (i = 0 ; i < a->len ; ++i) {
    fwrite((a->content)+i, sizeof(char), 1, dest_file);
  }
  fclose(dest_file);
}

void lzw_code(const char* src_path, const char* dest_path) {
  // Ouverture du fichier source
  FILE* src_file = fopen(src_path, "r");

  // Initialisation des varaibles temporaires
  array_t* encoded_file = array_new(),
         * w = array_new(),
         * p = array_new();
  dictionary_t* dic = dictionary_new();
  int c;

  // Encodage
  while ((c = fgetc(src_file)) != EOF) {
    array_add(p, c);
    if (dictionary_is_in(dic, p)) {
      array_add(w, c);
    }
    else {
      dictionary_add(dic, p);
      array_add(encoded_file, dictionary_get_code(dic, w));
      array_clear(w);
      array_clear(p);
    }
  }

  // Copie de l'encodage vers le fichier destination
  array_ints_to_bytes(encoded_file);
  _write_array(dest_path, encoded_file);

  // Fermeture du fichier source
  fclose(src_file);

  // Libération des variables temporaires
  array_free(encoded_file);
  array_free(w);
  array_free(p);
  dictionary_free(dic);
}

void lzw_decode(const char* src_path, const char* dest_path) {
}
