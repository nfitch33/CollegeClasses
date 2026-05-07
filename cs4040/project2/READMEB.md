This project generates random 2D points, builds a k-nearest-neighbor (k-NN) graph, and compares the performance of Dijkstra’s algorithm and A* for shortest-path computation. It also plots runtime results for different graph sizes and values of k.

Requirements
    Install matplotlib:
    pip install matplotlib

---- How It Works ----

Generate random points:
    points = generate_points(n)
    Creates n random points in the range [0,100] × [0,100].

Build a k-NN graph:
    graph = build_knn_graph(points, k)
    Connects each point to its k nearest neighbors (undirected).

Pick source and target:
    s, t = find_source_target(points)
    s = lexicographically smallest point
    t = lexicographically largest point

Shortest-path algorithms:
    dijkstra(graph, s, t)
    a_star(graph, points, s, t)
        Dijkstra uses a min-heap.
        A* uses Euclidean distance as a heuristic.

Run experiments:
    results = run_experiments(ns, ks)
    Benchmarks Dijkstra and A* for multiple dataset sizes (ns) and values of k.

Plot results:
    plot_results(ns, ks, results)
    Creates runtime-vs-n plots for Dijkstra and A*.

Run the script:
    python3 main.py

This will:
    Generate random point sets
    Build k-NN graphs
    Benchmark Dijkstra and A*
    Plot results
    Print example shortest-path outputs

Function Overview
    generate_points – Create random 2D points
    euclidean_distance – Compute distance between points
    build_knn_graph – Construct k-NN adjacency list
    find_source_target – Select smallest and largest points
    dijkstra – Shortest path using Dijkstra
    a_star – Shortest path using A*
    run_experiments – Benchmark algorithms
    plot_results – Plot runtime results