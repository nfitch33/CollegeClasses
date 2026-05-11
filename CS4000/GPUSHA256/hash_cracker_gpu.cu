#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

#define BUF 256

__device__ void ix_to_password(const char *alphabet,
                               int len,
                               unsigned long long ix,
                               char *out)
{
    int base = 0;
    while (alphabet[base]) base++;

    for (int i = len - 1; i >= 0; i--) {
        out[i] = alphabet[ix % base];
        ix /= base;
    }
    out[len] = '\0';
}

__global__ void generate_passwords(const char *alphabet,
                                  int len,
                                  unsigned long long total,
                                  char *out,
                                  unsigned long long *found_idx,
                                  int *found_flag)
{
    unsigned long long ix =
        (unsigned long long)blockIdx.x * blockDim.x + threadIdx.x;

    if (ix >= total || *found_flag) return;

    char pwd[32];

    ix_to_password(alphabet, len, ix, pwd);

    // store candidate (CPU will validate later)
    if (ix == 0) {
        // only placeholder kernel (real verification happens on CPU)
        *found_idx = ix;
    }
}