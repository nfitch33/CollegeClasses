# k-NN Graph Shortest Path Algorithms

This repository contains Python implementations of **Dijkstra** and **A\*** algorithms applied to **k-Nearest Neighbor (k-NN) graphs**. The code is designed for 2D point sets and provides utilities to measure and compare the runtime performance of these algorithms for different graph sizes and connectivity.

---

## Features

- Build optimized **k-NN graphs** using **KDTree** for fast neighbor queries.
- Compute shortest paths using:
  - **Dijkstra's algorithm**
  - **A\* algorithm** with Euclidean distance heuristic
- Predefined **Test-Me functions** for experiments on exactly 50 points.
- Automatic performance experiments for various `n` (number of nodes) and `k` (k-NN parameter) values.
- Generates **runtime plots** for Dijkstra vs A\* for different `k` values.

---

## Requirements

- Python 3.8+
- Libraries:
  - `numpy`
  - `scipy`
  - `matplotlib`

Install dependencies via pip:

```bash
pip install numpy scipy matplotlib

File Structure
  main.py – Main script containing all functions:
  Utility functions (euclidean_distance, lexicographic_min_max, etc.)
  Graph construction (build_knn_graph)
  Shortest-path algorithms (dijkstra, a_star)
  Testing functions (Test_Me_Dijkstra, Test_Me_Astar)
  Experiment and plotting routines (run_experiments, main)

Output:
  PNG plots of runtime vs number of nodes for different k values.

Run Experiments:
  python3 Project2.py
  -This will:
    Warm up the algorithms with exactly 50 random points.
    Run experiments for different graph sizes (n) and k-NN parameters (k).
    Measure runtime for Dijkstra and A* algorithms.
    Generate and save runtime plots as runtime_k{K}.png.

Algorithm Details:
  Graph Construction
    KDTree is used to efficiently find k nearest neighbors for each point.
    The adjacency list is built as an undirected graph.
    Duplicate edges are removed for efficiency.

  Dijkstra Algorithm
    Standard priority queue implementation.
    Returns the shortest distance between the lexicographic min and max points.
  
  A* Algorithm
    Uses Euclidean distance to the target as a heuristic.
    Often faster than Dijkstra for large graphs with a meaningful heuristic.

Experiments:
  Experiments are run for varying:
    n = [100, 500, 1000, 5000, 10000, 20000]
    k = [5, 10, 20, 50]
  Runtime for both algorithms is measured in milliseconds.
  Plots saved in the current directory.