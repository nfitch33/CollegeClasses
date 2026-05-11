#ifndef HASH_CRACKER_H
#define HASH_CRACKER_H

#include "sha256.h"

// MPI helper routines
void Get_input(int my_rank, int comm_sz,
                char *salt, char *hash,
                char *alphabet, int *ppwd_len);

void ix_to_password(char *alphabet, int pwd_length,
                    int ix, char *guess);

int FindHash(int my_rank,
             char *salt,
             char *hash,
             char *alphabet,
             int pwd_length,
             int first_pwd_ix,
             int last_pwd_ix);

// math helper
unsigned power(unsigned base, unsigned degree);

// hashing wrapper
void calculate_hash(char* dest,
                    const char* salt,
                    const char* guess);

#endif