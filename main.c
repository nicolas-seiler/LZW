#include "lzw.h"

int main(int argc, char* argv[]) {
  lzw_code("test", "testc");
  lzw_decode("testc", "testdc");
  return 0;
}
