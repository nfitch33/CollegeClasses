/* MPI Hash Cracker */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#include "hash_cracker.h"

#define bufsize 256

int debug = 0;

/* ---------------- MAIN ---------------- */

int main(int argc, char *argv[]) {

   int my_rank, comm_sz;

   char salt[bufsize];
   char hash[bufsize];
   char alphabet[bufsize];

   int password_length;

   int ix1, ix2;
   int total_passwords;

   int my_answer_ix;
   int answer = -1;

   MPI_Init(NULL, NULL);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   if ((argc == 2) && (strcmp(argv[1], "-d") == 0))
      debug = 1;

   Get_input(my_rank, comm_sz,
             salt, hash, alphabet,
             &password_length);

   total_passwords =
      power(strlen(alphabet), password_length);

   int chunk = total_passwords / comm_sz;

   ix1 = my_rank * chunk;
   ix2 = (my_rank == comm_sz - 1)
            ? total_passwords - 1
            : ix1 + chunk - 1;

   my_answer_ix =
      FindHash(my_rank, salt, hash,
               alphabet, password_length,
               ix1, ix2);

   int local = my_answer_ix;

   MPI_Reduce(&local, &answer, 1,
              MPI_INT, MPI_MAX,
              0, MPI_COMM_WORLD);

   if (my_rank == 0) {

      if (answer >= 0) {
         char guess[bufsize];
         ix_to_password(alphabet,
                        password_length,
                        answer,
                        guess);

         printf("%d '%s'\n", answer, guess);
      } else {
         printf("not found\n");
      }
   }

   MPI_Finalize();
   return 0;
}

/* ---------------- INPUT ---------------- */

void Get_input(int my_rank, int comm_sz,
               char *salt, char *hash,
               char *alphabet, int *ppwd_len) {

   if (my_rank == 0) {
      scanf("%s %s %s %d",
            salt, hash, alphabet, ppwd_len);
   }

   MPI_Bcast(salt, bufsize, MPI_CHAR, 0, MPI_COMM_WORLD);
   MPI_Bcast(hash, bufsize, MPI_CHAR, 0, MPI_COMM_WORLD);
   MPI_Bcast(alphabet, bufsize, MPI_CHAR, 0, MPI_COMM_WORLD);
   MPI_Bcast(ppwd_len, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

/* ---------------- INDEX -> PASSWORD ---------------- */

void ix_to_password(char *alphabet,
                    int pwd_length,
                    int ix,
                    char *guess) {

   int base = strlen(alphabet);

   for (int i = pwd_length - 1; i >= 0; i--) {

      char c = alphabet[ix % base];
      ix /= base;

      if (i % 2 == 0) {
         if (c >= 'a' && c <= 'z')
            guess[i] = c - 32;
         else
            guess[i] = c;
      } else {
         if (c >= 'A' && c <= 'Z')
            guess[i] = c + 32;
         else
            guess[i] = c;
      }
   }

   guess[pwd_length] = '\0';
}

/* ---------------- SEARCH ---------------- */

int FindHash(int my_rank,
             char *salt,
             char *target_hash,
             char *alphabet,
             int pwd_length,
             int first,
             int last) {

   char guess[pwd_length + 1];
   char hashbuffer[bufsize];

   for (int ix = first; ix <= last; ix++) {

      ix_to_password(alphabet,
                     pwd_length,
                     ix,
                     guess);

      calculate_hash(hashbuffer,
                     salt,
                     guess);

      if (strcmp(hashbuffer,
                 target_hash) == 0) {
         return ix;
      }
   }

   return -1;
}

/* ---------------- POWER ---------------- */

unsigned power(unsigned base, unsigned exp) {
   unsigned result = 1;
   while (exp) {
      if (exp & 1)
         result *= base;
      base *= base;
      exp >>= 1;
   }
   return result;
}

/* ---------------- HASH WRAPPER ---------------- */

void calculate_hash(char* dest,
                    const char* salt,
                    const char* guess) {
   sha_hashonly(dest, salt, guess);
}