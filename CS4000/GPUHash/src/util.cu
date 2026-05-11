#include "util.cuh"
#include "common.h"

__device__ int compare_strings(const char *a, const char *b) {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}

// Converts integer index into password using charset (base-N encoding)
__device__ void idx_to_password(int idx, const char *charset, int charset_len,
                                int len, char *out) {
    for (int i = len - 1; i >= 0; i--) {
        out[i] = charset[idx % charset_len];
        idx /= charset_len;
    }
}