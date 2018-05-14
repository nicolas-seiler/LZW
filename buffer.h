#ifndef _BUFFER_H_
#define _BUFFER_H_

#define INT_BUF_IS_FULL(b) \
  (b[1] != -1)

#define INT_BUF_IS_EMPTY(b) \
  (b[0] == -1)

#define INT_BUF_RESET(b) \
  do { \
    b[0] = -1; \
    b[1] = -1; \
  } while (0)

#define INT_BUF_ADD(b, n) \
  (b[0] == -1) ? (b[0] = n) : (b[1] = n)

#endif
