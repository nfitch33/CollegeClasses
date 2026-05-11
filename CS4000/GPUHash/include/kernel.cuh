#pragma once

__global__ void brute_kernel(
    const char *charset,
    int charset_len,
    int password_len,
    const char *salt,
    const char *target_hash,
    int *found,
    char *result
);