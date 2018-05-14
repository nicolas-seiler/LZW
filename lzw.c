#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"
#include "converter.h"
#include "buffer.h"

void lzw_encode(const char* src_path, const char* dest_path) {
// -- Initialisation -----------------------------------------------------------
  // Ouverture des fichiers
  FILE* src_file = fopen(src_path, "r"),
      * dest_file = fopen(dest_path, "w+");
  // Tampons
  word_t w; WORD_RESET(w);
  int int_buf[2]; INT_BUF_RESET(int_buf);
  octet_t byte_buf[3], c;

// -- Exécution ----------------------------------------------------------------
  while ((c = fgetc(src_file)) != EOF) {
    WORD_ADD(w, c);
    if (!dic_is_entry_existent(&w)) {
      dic_add_entry(&w);
      INT_BUF_ADD(int_buf, dic_get_entry_code(&w));
      WORD_RESET(w);
      WORD_ADD(w, c);
      /* Si on a 24 bits dans le tampon qui contient des entiers, on convertit
      ** ces entiers en byte et on écrit le tout dans le fichier de destination
      */
      if (INT_BUF_IS_FULL(int_buf)) {
        CONV_INTS_TO_BYTES(int_buf, byte_buf);
        INT_BUF_RESET(int_buf);
        fwrite(byte_buf, 1, 3, dest_file);
      }
    }
  }
  // S'il reste un dernier entier dans le tampon, il faut également l'écrire
  if (!INT_BUF_IS_EMPTY(int_buf)) {
    INT_BUF_ADD(int_buf, 10);
    CONV_INTS_TO_BYTES(int_buf, byte_buf);
    fwrite(byte_buf, 1, 3, dest_file);
  }

// -- Fermeture des fichiers et sortie -----------------------------------------
  fclose(src_file);
  fclose(dest_file);
}

void lzw_decode(const char* src_path, const char* dest_path) {
// -- Initialisation -----------------------------------------------------------
  // Ouverture des fichiers
  FILE* src_file = fopen(src_path, "r"),
      * dest_file = fopen(dest_path, "w+");
  // Tampons
  word_t w; WORD_RESET(w);
  int int_buf[2];
  octet_t byte_buf[3], c;

// -- Exécution ----------------------------------------------------------------
  while ((byte_buf[0] = fgetc(src_file)) != EOF) {
    int_buf[1] = fgetc(src_file);
    int_buf[2] = fgetc(src_file);
    CONV_BYTES_TO_INTS(byte_buf, int_buf);
  }
}
