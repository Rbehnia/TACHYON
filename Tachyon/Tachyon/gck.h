#include "params.h"
#include "ntt.h"

void gck_ntt(uint32_t input[N*mu]);
void gck_linearComb(const uint32_t input[N*mu], uint32_t result[N]);