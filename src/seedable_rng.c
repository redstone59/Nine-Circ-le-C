#include <stdint.h>

typedef struct SeedableRNG {
    uint32_t state;
} SeedableRNG;

uint32_t SeedableRNG_Next(SeedableRNG* rng) {
    // XORShift32 from https://en.wikipedia.org/wiki/Xorshift
    uint32_t x = rng->state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng->state = x;
    return x;
}