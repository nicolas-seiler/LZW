#include <stdio.h>

int main(int argc, char* argv[]) {
  FILE* d = fopen("d", "w+");
  int i = 'A';
  fwrite(&i, sizeof(char), 1, d);
  return 0;
}
