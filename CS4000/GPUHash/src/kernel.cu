#include "kernel.cuh"
#include "util.cuh"
#include "common.h"

__device__ void dummy_hash(const char *input, char *output) {
    // TODO: Replace with SHA256 or SHA256-crypt GPU implementation
    // For now this is just a placeholder so project compiles
    int i = 0;
    while (input[i]) {
        output[i] = input[i];
        i++;
    }
    output[i] = '\0';
}

__global__ void brute_kernel(
    const char *charset,
    int charset_len,
    int password_len,
    const char *salt,
    const char *target_hash,
    int *found,
    char *result
) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (*found) return;

    char candidate[MAX_PASSWORD_LEN];
    char hash_output[MAX_PASSWORD_LEN];

    idx_to_password(idx, charset, charset_len, password_len, candidate);

    dummy_hash(candidate, hash_output);

    if (compare_strings(hash_output, target_hash)) {
        *found = 1;

        for (int i = 0; i < password_len; i++) {
            result[i] = candidate[i];
        }
    }
}