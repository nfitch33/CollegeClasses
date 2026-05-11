#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __CUDACC__
#define HD __host__ __device__
#else
#define HD
#endif

// SHA256 context
typedef struct {
    uint32_t state[8];
    uint64_t bitlen;
    uint8_t data[64];
    uint32_t datalen;
} sha256_ctx;

// Core API (shared CPU/GPU-safe signatures)
HD void sha256_init(sha256_ctx *ctx);
HD void sha256_update(sha256_ctx *ctx, const uint8_t *data, size_t len);
HD void sha256_final(sha256_ctx *ctx, uint8_t hash[32]);

// helper for your $5$ crypt usage
void sha256_hash_string(char out[65], const char *input);