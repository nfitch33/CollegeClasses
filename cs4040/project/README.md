# CS 4040 – Project Phase 1  
## Empirical Analysis of Sorting Algorithms

**Name:** Nathaniel Fitch
**Course:** CS 4040 
**Due Date:** October 22, 2025  
**Language Used:** Python 3.10+

## Overview

This project implements and empirically analyzes the performance of two comparison-based sorting algorithms:

- **Insertion Sort** (in-place)
- **Randomized Quicksort** (recursive with uniform random pivot)
- **Counting Sort** (stable)

Both algorithms are benchmarked using randomly generated integer arrays of various input sizes. Runtime is measured using high-resolution timing (`time.perf_counter()`), and results are plotted and analyzed against theoretical expectations.

Measured empirical runtimes for input sizes n ∈ {10, 100, 1000, 2000, 5000, 10000, 20000}
and three different ranges of k ∈ {10, n, n² (capped for memory)}.

# Milestone 2:
Implemented **stable Counting Sort** that supports integers in [0, k].

# Sorting Algorithm Analysis (CS 4040 Project - Phase 1)

## Files
- `sort_algorithms.py`: Implements Insertion Sort and Randomized Quicksort and Counting Sort
- `main_analysis.py`: Generates input arrays, runs benchmarks, and plots results
- `test_functions.py`: Functions to test and verify sorting output
- `runtime_plot.png`: Runtime plot (generated)
- `report.pdf`: Contains table, plots, and commentary

## Run Instructions (Python 3.7+)
```bash
pip install matplotlib
python main_analysis.py


