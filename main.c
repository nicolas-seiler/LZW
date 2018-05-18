#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lzw.h"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    printf("Mauvais nombre d'arguments (nombre attendu: 3)\n");
    return EXIT_FAILURE;
  }
  if (!strcmp(argv[1], "-c")) {
    lzw_code(argv[2], argv[3]);
    return EXIT_SUCCESS;
  }
  if (!strcmp(argv[1], "-d")) {
    lzw_decode(argv[2], argv[3]);
    return EXIT_SUCCESS;
  }
  printf("Second argument non reconnu (\"-c\" pour encoder, \"-d\" pour decoder)\n");
  return EXIT_FAILURE;
}
