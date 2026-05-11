#include <cuda_runtime.h>

__global__ void generate_indices(unsigned long long start,
                                  unsigned long long *out,
                                  int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
        out[i] = start + i;
}