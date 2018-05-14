#ifndef _CONVERTER_H_
#define _CONVERTER_H_

#define CONV_INTS_TO_BYTES(n, b) \
  do { \
    b[0] = (n[0] >> 4); \
    b[1] = (n[0] << 4) | ((n[1] & 0xF00) >> 8); \
    b[2] = n[1]; \
  } while (0)

#define CONV_BYTES_TO_INTS(b, n) \
  do { \
    n[0] = (b[0] << 4) & (b[1] >> 4); \
    n[1] = ((b[1] & 0xF) << 8) & b[2]; \
  } while (0)

#endif
