#include <stdio.h>
#include <string.h>
#include "sha256.cuh"

void sha256_hash_string(char out[65], const char *input) {
    sha256_ctx ctx;
    uint8_t hash[32];

    sha256_init(&ctx);
    sha256_update(&ctx, (const uint8_t*)input, strlen(input));
    sha256_final(&ctx, hash);

    for (int i=0;i<32;i++)
        sprintf(out + i*2, "%02x", hash[i]);

    out[64] = 0;
}