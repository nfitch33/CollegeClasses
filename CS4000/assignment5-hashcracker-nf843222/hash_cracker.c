#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

#include "hash_cracker.h"

const int bufsize = 256;
int debug = 0;

/* ================= MAIN ================= */
int main(int argc, char *argv[]) {

   int rank, comm_sz;

   char salt[bufsize];
   char target_hash[bufsize];
   char alphabet[bufsize];
   int pwd_len;

   MPI_Init(NULL, NULL);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   /* input */
   if (rank == 0) {
      FILE *fp = stdin;

      if (argc >= 2) {
         fp = fopen(argv[1], "r");
         if (!fp) {
            fprintf(stderr, "Cannot open input file\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
         }
      }

      fscanf(fp, "%s %s %s %d",
             salt, target_hash, alphabet, &pwd_len);

      if (fp != stdin)
         fclose(fp);
   }

   MPI_Bcast(salt, bufsize, MPI_CHAR, 0, MPI_COMM_WORLD);
   MPI_Bcast(target_hash, bufsize, MPI_CHAR, 0, MPI_COMM_WORLD);
   MPI_Bcast(alphabet, bufsize, MPI_CHAR, 0, MPI_COMM_WORLD);
   MPI_Bcast(&pwd_len, 1, MPI_INT, 0, MPI_COMM_WORLD);

   /* compute search space */
   int base = strlen(alphabet);

   int total = 1;
   for (int i = 0; i < pwd_len; i++)
      total *= base;

   int chunk = total / comm_sz;
   int rem = total % comm_sz;

   int start = rank * chunk + (rank < rem ? rank : rem);
   int end   = start + chunk - 1;
   if (rank < rem) end++;

   int found = FindHash(rank, salt, target_hash,
                        alphabet, pwd_len,
                        start, end);

   int result;

   MPI_Allreduce(&found, &result, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

   if (rank == 0) {
      if (result >= 0) {
         char guess[bufsize];
         ix_to_password(alphabet, pwd_len, result, guess);
         printf("%d: '%s'\n", result, guess);
      } else {
         printf("not found\n");
      }
   }

   MPI_Finalize();
   return 0;
}