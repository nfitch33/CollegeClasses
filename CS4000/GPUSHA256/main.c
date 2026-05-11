#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <cuda_runtime.h>

#include "hash_cracker.h"

#define BATCH 1000000

__global__ void generate_indices(unsigned long long start,
                                  unsigned long long *out,
                                  int n);

int main()
{
    char salt[256], target[256], alphabet[256];
    int len;

    scanf("%s %s %s %d", salt, target, alphabet, &len);

    int base = strlen(alphabet);

    unsigned long long total = 1;
    for (int i = 0; i < len; i++)
        total *= base;

    unsigned long long *d_out;
    unsigned long long *h_out =
        (unsigned long long*)malloc(BATCH * sizeof(unsigned long long));

    // 🔥 FIXED cudaMalloc (CAST FIX)
    cudaMalloc((void**)&d_out, BATCH * sizeof(unsigned long long));

    int found = 0;

    #pragma omp parallel shared(found)
    {
        char guess[256];
        char hashbuffer[256];

        #pragma omp for schedule(dynamic, 5000)
        for (unsigned long long start = 0; start < total; start += BATCH)
        {
            if (found) continue;

            int size = (start + BATCH > total) ? (total - start) : BATCH;

            generate_indices<<<(size+255)/256, 256>>>(start, d_out, size);
            cudaDeviceSynchronize();

            cudaMemcpy(h_out, d_out,
                       size * sizeof(unsigned long long),
                       cudaMemcpyDeviceToHost);

            for (int i = 0; i < size && !found; i++)
            {
                ix_to_password(alphabet, len, h_out[i], guess);
                calculate_hash(hashbuffer, salt, guess);

                if (strcmp(hashbuffer, target) == 0)
                {
                    #pragma omp critical
                    {
                        if (!found)
                        {
                            found = 1;
                            printf("\nFOUND: %s\n", guess);
                            printf("INDEX: %llu\n", h_out[i]);
                        }
                    }
                }
            }
        }
    }

    if (!found)
        printf("not found\n");

    cudaFree(d_out);
    free(h_out);

    return 0;
}