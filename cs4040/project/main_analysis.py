import time
import random
import statistics
import matplotlib.pyplot as plt
import csv

from sort_algorithms import insertion_sort, quicksort, counting_sort

# Input sizes
input_sizes = [10, 100, 1000, 2000, 5000, 10000, 20000]

# Algorithms (Counting Sort handled separately)
algorithms = {
    "Insertion Sort": insertion_sort,
    "Quicksort": quicksort,
}

# Results container
results = {name: [] for name in algorithms}
results["Counting Sort"] = []

def warm_up():
    """Run dummy sorts to trigger interpreter optimizations (JIT warm-up)."""
    dummy = [random.randint(0, 1000) for _ in range(1000)]
    insertion_sort(dummy.copy())
    quicksort(dummy.copy())
    counting_sort(dummy.copy(), 1000)

def time_algorithm(algorithm, arr, k=None):
    """Time a sorting algorithm using a high-resolution monotonic timer."""
    arr_copy = arr.copy()
    start = time.perf_counter()
    if k is not None:
        algorithm(arr_copy, k)
    else:
        algorithm(arr_copy)
    end = time.perf_counter()
    return (end - start) * 1000  # milliseconds

def run_trials():
    """Run timing trials for all algorithms."""
    warm_up()

    print("n     Algorithm         k-value      Median Time (ms)")
    print("-" * 55)

    # --- Insertion Sort and Quicksort ---
    for name, func in algorithms.items():
        for n in input_sizes:
            times = []
            for _ in range(5):
                arr = [random.randint(0, 10**6) for _ in range(n)]
                try:
                    t = time_algorithm(func, arr)
                    times.append(t)
                except Exception as e:
                    print(f"Error during {name} at n={n}: {e}")
            if times:
                median_time = statistics.median(times)
                results[name].append((n, None, median_time))
                print(f"{n:<5} {name:<17} {'-':<10} {median_time:>10.3f}")

    # --- Counting Sort (run ONCE per n, using k = n) ---
    for n in input_sizes:
        k = n  # single representative k value
        times = []
        for _ in range(5):
            arr = [random.randint(0, k) for _ in range(n)]
            try:
                t = time_algorithm(counting_sort, arr, k)
                times.append(t)
            except Exception as e:
                print(f"Error during Counting Sort at n={n}, k={k}: {e}")
        if times:
            median_time = statistics.median(times)
            results["Counting Sort"].append((n, k, median_time))
            print(f"{n:<5} {'Counting Sort':<17} {str(k):<10} {median_time:>10.3f}")

def plot_results():
    """Generate runtime comparison plot."""
    plt.figure(figsize=(10, 7))

    # Plot Insertion Sort & Quicksort
    for name in algorithms:
        x = [n for n, _, _ in results[name]]
        y = [t for _, _, t in results[name]]
        plt.plot(x, y, marker='o', label=name)

    # Plot Counting Sort (single curve)
    x = [n for n, _, _ in results["Counting Sort"]]
    y = [t for _, _, t in results["Counting Sort"]]
    plt.plot(x, y, marker='s', linestyle='--', label="Counting Sort (k=n)")

    plt.xlabel("Input size (n)")
    plt.ylabel("Median runtime (ms)")
    plt.title("Sorting Algorithm Runtime Comparison (Phase 2)")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("runtime_plot_phase2.png")
    print("\nSaved runtime plot as 'runtime_plot_phase2.png'.")

def save_results_to_csv(filename="results_phase2.csv"):
    """Save all results to CSV."""
    with open(filename, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["n", "Algorithm", "k", "Median Time (ms)"])
        for name in results:
            for n, k, time_ms in results[name]:
                writer.writerow([n, name, k if k is not None else "-", round(time_ms, 3)])
    print(f"Saved results to '{filename}'.")

if __name__ == "__main__":
    run_trials()
    save_results_to_csv()
    plot_results()
