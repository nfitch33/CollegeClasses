'''
Source Code from CS3560/examples/Profiling/sum_of_squares
'''
import time
import math
import wandb  # Import the wandb library
from functools import lru_cache
from itertools import combinations
from tqdm import tqdm


# Dynamic Programming (static) solution
def sum_of_squares_dp_static(n):
    global dp_static
    if n < len(dp_static):
        return dp_static[n]
    for i in range(len(dp_static), n + 1):
        j = 1
        while j * j <= i:
            dp_static[i] = min(dp_static[i], dp_static[i - j * j] + 1)
            j += 1
    return dp_static[n]

# Dynamic Programming solution
def sum_of_squares_dp(n):
    dp = [float('inf')] * (n + 1)
    dp[0] = 0
    for i in range(1, n + 1):
        j = 1
        while j * j <= i:
            dp[i] = min(dp[i], dp[i - j * j] + 1)
            j += 1
    return dp[n]

# Math-based solution
def sum_of_squares_math(n):
    if math.isqrt(n) ** 2 == n:
        return 1
    c1 = 0
    m = n
    while m % 4 == 0:
        m //= 4
        c1 += 1
    if m % 8 == 7:
        return 4
    for i in range(1, math.isqrt(n) + 1):
        if math.isqrt(n - i * i) ** 2 == n - i * i:
            return 2
    return 3

# Naive solution with combinations
def sum_of_squares_naive_comb(n):
    numbers = [i for i in range(1, n + 1)]
    i = 1
    while i <= n:
        candidates = list(combinations(numbers * i, i))
        for c in candidates:
            if sum(x * x for x in c) == n:
                return i
        i += 1

# Naive solution (brute-force)
def sum_of_squares_naive(n):
    numbers = [i for i in range(1, n + 1)]
    i = 1
    while i <= n:
        # Generate all possible combinations of `i` numbers
        from itertools import product
        for c in product(numbers, repeat=i):
            if sum(x * x for x in c) == n:
                return i
        i += 1

# Recursive solution with `sos` inside `sum_of_squares_recursive`
def sum_of_squares_recursive(n):
    def sos(n, k):
        if k == 1:
            return math.isqrt(n) ** 2 == n
        for i in reversed(range(1, math.isqrt(n) + 1)):
            if sos(n - i * i, k - 1):
                return True
        return False

    i = 1
    while not sos(n, i):
        i += 1
    return i

# Recursive solution with `lru_cache` inside `sum_of_squares_recursive_cache`
def sum_of_squares_recursive_cache(n):
    @lru_cache(maxsize=None)
    def sos(n, k):
        if k == 1:
            return math.isqrt(n) ** 2 == n
        for i in reversed(range(1, math.isqrt(n) + 1)):
            if sos(n - i * i, k - 1):
                return True
        return False

    i = 1
    while not sos(n, i):
        i += 1
    return i

if __name__ == "__main__":
    start = time.time()
    max = 5000
    # Initialize wandb
    wandb.init(project="sum-of-squares-dp-static", config={"max": max})
    max_digits = math.floor(math.log10(max)) + 1
    last_duration = 0
    last_elapsed = 0

    for i in tqdm(range(1, max)):
        t1 = time.time()
        s = sum_of_squares_recursive(i)
        t2 = time.time()
        if t2 - t1 > last_duration * 2 or t2 - start > last_elapsed * 2:
            istr = str(i).rjust(max_digits)
            print('i: ', i)
            print(
                f"{istr}: sum of {s} perfect squares: computed in {t2-t1} sec. Elapsed time: {t2-start} sec."
            )
            last_duration = t2 - t1
            last_elapsed = t2 - start

        # Log metrics to wandb
        wandb.log({
            "sum_of_squares": s,
            "computation_time": t2 - t1,
            "elapsed_time": t2 - start
        })

    end = time.time()
    total_elapsed_time = end - start
    print(
        f"Total elapsed time to compute sum of squares up to {max}: {total_elapsed_time} seconds"
    )


    # Finish the wandb run
    wandb.finish()

if __name__ == "__main__":
    start = time.time()
    max = 1000
    max_digits = math.floor(math.log10(max)) + 1
    last_duration = 0
    last_elapsed = 0
    for i in range(1, max):
        t1 = time.time()
        s = sum_of_squares_math(i)
        t2 = time.time()
        if t2 - t1 > last_duration * 2 or t2 - start > last_elapsed * 2:
            istr = str(i).rjust(max_digits)
            print(
                f"{istr}: sum of {s} perfect squares: computed in {t2-t1} sec. Elapsed time: {t2-start} sec."
            )
            last_duration = t2 - t1
            last_elapsed = t2 - start
    end = time.time()
    print(
        f"Total elapsed time to compute sum of squares up to {max}: {end-start} seconds"
    )
