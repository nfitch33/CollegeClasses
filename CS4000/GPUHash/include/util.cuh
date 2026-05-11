#pragma once

__device__ int compare_strings(const char *a, const char *b);
__device__ void idx_to_password(int idx, const char *charset, int charset_len,
                                int len, char *out);