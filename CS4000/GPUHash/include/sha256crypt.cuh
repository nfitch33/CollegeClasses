#pragma once

#include <stdint.h>

#define SHA256_DIGEST_LENGTH 32
#define SHA256_CRYPT_OUTPUT_LEN 64

// ----------------------------------------------------
// GPU context for SHA256-crypt ($5$)
// ----------------------------------------------------
typedef struct {
    uint32_t H[8];
    uint32_t total[2];
    uint32_t buflen;
    unsigned char buffer[64];
} SHA256_CTX_GPU;

// ----------------------------------------------------
// DEVICE API (raw SHA256 core)
// ----------------------------------------------------
__device__ void sha256_init(SHA256_CTX_GPU *ctx);

__device__ void sha256_update(SHA256_CTX_GPU *ctx, const unsigned char *data, int len);

__device__ void sha256_final(SHA256_CTX_GPU *ctx, unsigned char out[32]);

// ----------------------------------------------------
// DEVICE API (FULL $5$ SHA256-crypt)
// ----------------------------------------------------
// This is the function your kernel will call per password
__device__ void sha256_crypt_5(
    const char *key,
    const char *salt,
    char output[64]
);