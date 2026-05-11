#ifndef HASH_CRACKER_H
#define HASH_CRACKER_H

void calculate_hash(char *dest, const char *salt, const char *key);

void Get_input(int my_rank, int comm_sz,
               char *salt,
               char *hash,
               char *alphabet,
               int *pwd_len,
               int argc, char *argv[]);

void ix_to_password(char *alphabet, int pwd_len,
                    int ix, char *guess);

int FindHash(int my_rank,
             char *salt,
             char *target_hash,
             char *alphabet,
             int pwd_len,
             int first_pwd_ix,
             int last_pwd_ix);

#endif