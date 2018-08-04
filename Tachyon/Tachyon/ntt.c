#include "ntt.h"

uint32_t montgomery_reduce(uint64_t a) {
  const uint64_t qinv = QINV; //QINV =  -q^(-1) mod 2^32
  uint64_t t;

  t = a * qinv;
  t &= (1ULL << 32) - 1;
  t *= Q;
  t = a + t;
  return t >> 32;
}

void ntt(uint32_t p[N]) {
  unsigned int len, start, j, k;
  uint32_t zeta, t;

  k = 1;
  for(len = 128; len > 0; len >>= 1) {
    for(start = 0; start < N; start = j + len) {
      zeta = zetas[k++]; // zetas -> /* Roots of unity in order needed by forward ntt */
      for(j = start; j < start + len; ++j) {
        t = montgomery_reduce((uint64_t)zeta * p[j + len]);
        p[j + len] = p[j] + 2*Q - t;
        p[j] = p[j] + t;
      }
    }
  }
}