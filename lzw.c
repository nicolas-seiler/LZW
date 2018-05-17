#include "lzw.h"

#include <stdio.h>
#include "array.h"
#include "dictionary.h"

static void _write_array(const char* dest_path, const array_t* a) {
  FILE* dest_file = fopen(dest_path, "w+");
  size_t i;
  for (i = 0 ; i < array_len(a) ; ++i) {
    fwrite(array_content(a)+i, sizeof(char), 1, dest_file);
  }
  fclose(dest_file);
}

void lzw_code(const char* src_path, const char* dest_path) {
  // Ouverture du fichier source
  FILE* src_file = fopen(src_path, "r");

  // Initialisation des variables temporaires
  int cursor;
  array_t* encoded_file = array_new(),
         * out = array_new(),
         * buf = array_new();
  dictionary_t* dic = dictionary_new();

  // Encodage
  while ((cursor = fgetc(src_file)) != EOF) {
    buf = array_add(buf, cursor);
    if (dictionary_is_entry_in(dic, buf)) {
      out = array_add(out, cursor);
    } else {
      dic = dictionary_add(dic, buf);
      encoded_file = array_add(encoded_file, dictionary_get_code(dic, out));
      out = array_clear(out);
      buf = array_clear(buf);
      out = array_add(out, cursor);
      buf = array_add(buf, cursor);
    }
  }

  // Copie de l'encodage vers le fichier destination
  encoded_file = array_ints_to_bytes(encoded_file);
  _write_array(dest_path, encoded_file);

  // Fermeture du fichier source
  fclose(src_file);

  // Libération des variables temporaires
  array_free(encoded_file);
  array_free(out);
  array_free(buf);
  dictionary_free(dic);
}

void lzw_decode(const char* src_path, const char* dest_path) {
  // Ouverture du fichier source
  FILE* src_file = fopen(src_path, "r");

  // Initialisation des variables temporaires
  int cursor;
  array_t* out = array_new(),
         * buf = array_new(),
         * encoded_file = array_new(),
         * decoded_file = array_new();
  dictionary_t* dic = dictionary_new();

  // Récupération du fichier
  while ((cursor = fgetc(src_file)) != EOF) {
    encoded_file = array_add(encoded_file, cursor);
  }
  encoded_file = array_bytes_to_ints(encoded_file);
  const int* src = array_content(encoded_file);

  // Décodage
  decoded_file = array_concat(decoded_file, dictionary_get_entry(dic, src[0]));
  buf = array_add(buf, src[0]);

  size_t i;
  for (i = 1 ; i < array_len(encoded_file) ; ++i) {
    cursor = src[i];
    if (dictionary_is_code_in(dic, cursor)) {
      out = array_copy(out, dictionary_get_entry(dic, cursor));
    } else {
      out = array_copy(out, buf);
      out = array_add(out, array_content(buf)[0]);
    }
    decoded_file = array_concat(decoded_file, out);
    buf = array_add(buf, array_content(out)[0]);
    dictionary_add(dic, buf);
    buf = array_copy(buf, out);
  }
  _write_array(dest_path, decoded_file);

  // Fermeture du fichier source
  fclose(src_file);

  // Libération des variables temporaires
  array_free(encoded_file);
  array_free(decoded_file);
  array_free(out);
  array_free(buf);
  dictionary_free(dic);
}
