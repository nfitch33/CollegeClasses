#ifndef HASH_CRACKER_H
#define HASH_CRACKER_H

#include "sha256.h"

void ix_to_password(char *alphabet, int len, unsigned long long ix, char *out);

static inline void calculate_hash(char* dest, const char* salt, const char* guess)
{
    sha_hashonly(dest, salt, guess);
}

#endif