import heapq
import math
import time
import matplotlib.pyplot as plt
from scipy.spatial import KDTree

INF = float('inf')

# ---------------------------
# Utility Functions
# ---------------------------

def euclidean_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def lexicographic_min_max(points):
    s = min(points, key=lambda p: (p[0], p[1]))
    t = max(points, key=lambda p: (p[0], p[1]))
    return points.index(s), points.index(t)

def build_knn_graph(points, k):
    """Optimized k-NN graph using KDTree for fast neighbor search."""
    n = len(points)
    adj = [[] for _ in range(n)]
    tree = KDTree(points)
    for i, point in enumerate(points):
        dists, idxs = tree.query(point, k=k+1)  # +1 to exclude self
        for dist, j in zip(dists[1:], idxs[1:]):  # skip self
            adj[i].append((j, dist))
            adj[j].append((i, dist))  # undirected
    # Remove duplicate edges efficiently
    for i in range(n):
        seen = set()
        new_adj = []
        for v, w in adj[i]:
            if (v, w) not in seen:
                new_adj.append((v, w))
                seen.add((v, w))
        adj[i] = new_adj
    return adj

# ---------------------------
# Dijkstra
# ---------------------------

def dijkstra(adj, s, t):
    n = len(adj)
    dist = [INF] * n
    dist[s] = 0
    pq = [(0, s)]
    while pq:
        d, u = heapq.heappop(pq)
        if u == t:
            return dist[t]
        if d > dist[u]:
            continue
        for v, w in adj[u]:
            if dist[v] > dist[u] + w:
                dist[v] = dist[u] + w
                heapq.heappush(pq, (dist[v], v))
    return INF

# ---------------------------
# A* Algorithm
# ---------------------------

def a_star(adj, points, s, t):
    n = len(adj)
    dist = [INF] * n
    dist[s] = 0

    def heuristic(u):
        return euclidean_distance(points[u], points[t])

    pq = [(heuristic(s), s)]
    while pq:
        f, u = heapq.heappop(pq)
        if u == t:
            return dist[t]
        for v, w in adj[u]:
            if dist[v] > dist[u] + w:
                dist[v] = dist[u] + w
                heapq.heappush(pq, (dist[v] + heuristic(v), v))
    return INF

# ---------------------------
# Test-Me Functions (50 points)
# ---------------------------

def Test_Me_Dijkstra(points, k=10):
    """
    Run Dijkstra's algorithm on a k-NN graph built from exactly 50 2D points.
    Returns shortest-path distance between lexicographic min and max points.
    """
    if len(points) != 50:
        raise ValueError("Test_Me_Dijkstra requires exactly 50 points.")
    adj = build_knn_graph(points, k)
    s, t = lexicographic_min_max(points)
    return dijkstra(adj, s, t)

def Test_Me_Astar(points, k=10):
    """
    Run A* algorithm on a k-NN graph built from exactly 50 2D points.
    Returns shortest-path distance between lexicographic min and max points.
    """
    if len(points) != 50:
        raise ValueError("Test_Me_Astar requires exactly 50 points.")
    adj = build_knn_graph(points, k)
    s, t = lexicographic_min_max(points)
    return a_star(adj, points, s, t)

# ---------------------------
# Experiments & Plots
# ---------------------------

def run_experiments():
    import random
    ns = [100, 500, 1000, 5000, 10000, 20000]
    ks = [5, 10, 20, 50]

    # Warm up with exactly 50 points (required by Test-Me functions)
    warmup_points = [(random.uniform(0,100), random.uniform(0,100)) for _ in range(50)]
    Test_Me_Dijkstra(warmup_points)
    Test_Me_Astar(warmup_points)

    for k in ks:
        dijkstra_times = []
        a_star_times = []
        shortest_paths = []

        for n in ns:
            print(f"Running experiment for n={n}, k={k} ...")
            points = [(random.uniform(0,100), random.uniform(0,100)) for _ in range(n)]
            adj = build_knn_graph(points, k)
            s, t = lexicographic_min_max(points)

            # Dijkstra timing
            start = time.perf_counter()
            dijkstra_distance = dijkstra(adj, s, t)
            dt = (time.perf_counter() - start) * 1000

            # A* timing
            start = time.perf_counter()
            a_star_distance = a_star(adj, points, s, t)
            at = (time.perf_counter() - start) * 1000

            if abs(dijkstra_distance - a_star_distance) > 1e-6:
                print(f"Warning: distances do not match for n={n}, k={k}")

            dijkstra_times.append(dt)
            a_star_times.append(at)
            shortest_paths.append(dijkstra_distance)

            print(f"n={n}, k={k}, Dijkstra={dt:.2f}ms, A*={at:.2f}ms, distance={dijkstra_distance:.2f}")

        # Plot results
        import matplotlib.pyplot as plt
        plt.figure()
        plt.plot(ns, dijkstra_times, marker='o', label='Dijkstra')
        plt.plot(ns, a_star_times, marker='s', label='A*')
        plt.xlabel("Number of nodes (n)")
        plt.ylabel("Runtime (ms)")
        plt.title(f"Runtime vs n for k={k}")
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.savefig(f"runtime_k{k}.png")

# ---------------------------
# Main
# ---------------------------

_has_run = False

def main():
    global _has_run
    if _has_run:
        print("Experiments already ran. Skipping.")
        return
    _has_run = True
    run_experiments()

if __name__ == "__main__":
    main()
