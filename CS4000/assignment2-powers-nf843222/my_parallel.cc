//
// File: my_parallel.cc
// Author: Nathaniel Fitch
// Purpose: Computes the last six digits of the
// sum from 1 to n (given as input) of i^i
// Uses modular arithemtic and OpenMP parallelization
// This version does NOT use Boost and is optimizzed for speed.
// Extra Credit given using Eulers Method.
//

#include <iostream>
#include <iomanip>
#include <omp.h>

using namespace std;

// greatest common divisor
long long gcd(long long a, long long b){
  while (b != 0){
    long long t = a % b;
    a = b;
    b = t;
  }
  return a;
}

// fast modular exponentiation
long long modPow(long long base, long long exp, long long mod){
  const long long PHI = 400000;  // phi(1,000,000)
  if (gcd(base, mod) == 1)
    exp = exp % PHI;

  long long result = 1;
  base %= mod;

  while (exp > 0){
    if (exp & 1)
      result = (result * base) % mod;

    base = (base * base) % mod;
    exp >>= 1;
  }

  return result;
}

int main(){
  int n;
  cin >> n;

  const long long MOD = 1000000;
  long long sum = 0;

  // Proper OpenMP parallel loop
  #pragma omp parallel for schedule(runtime) reduction(+:sum)
  for (int i = 1; i <= n; i++) {
    sum += modPow(i, i, MOD);
    sum %= MOD;   // keep bounded
  }

  cout << "Answer = "
       << setw(6) << setfill('0')
       << sum % MOD << endl;

  return 0;
}