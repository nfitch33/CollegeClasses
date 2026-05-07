import heapq
import math
import random
import time
import matplotlib.pyplot as plt

# generate random points in [0,100] x [0,100]
def generate_points(n):
    points = [(random.uniform(0, 100), random.uniform(0, 100)) for _ in range(n)]
    return points

# compute Euclidean distance between two points
def euclidean_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

# build k-nearest neighbor graph (undirected)
def build_knn_graph(points, k):
    n = len(points)
    graph = {i: [] for i in range(n)}
    edges_added = set()  # keep track of added undirected edges

    for i in range(n):
        distances = []
        for j in range(n):
            if i != j:
                dist = euclidean_distance(points[i], points[j])
                distances.append((dist, j))
        distances.sort(key=lambda x: (x[0], x[1]))  # break ties by index

        for d, j in distances[:k]:
            if (i, j) not in edges_added and (j, i) not in edges_added:
                graph[i].append((j, d))
                graph[j].append((i, d))
                edges_added.add((i, j))
    return graph


# find source and target nodes (lexicographically smallest/largest)
def find_source_target(points):
    s = min(range(len(points)), key=lambda i: (points[i][0], points[i][1]))
    t = max(range(len(points)), key=lambda i: (points[i][0], points[i][1]))
    return s, t

# Dijkstra's algorithm using min-heap
def dijkstra(graph, s, t):
    n = len(graph)
    INF = float('inf')
    d = [INF] * n
    d[s] = 0
    heap = [(0, s)]

    while heap:
        dist_u, u = heapq.heappop(heap)
        if u == t:
            return d[t]  # reached target
        if dist_u > d[u]:
            continue  # skip stale entry
        for v, w in graph[u]:
            if d[v] > d[u] + w:  # relax edge
                d[v] = d[u] + w
                heapq.heappush(heap, (d[v], v))
    return INF  # target unreachable

# A* algorithm with Euclidean heuristic
def a_star(graph, points, s, t):
    n = len(graph)
    INF = float('inf')
    d = [INF] * n
    d[s] = 0

    h = [euclidean_distance(points[u], points[t]) for u in range(n)]  # heuristic

    heap = [(d[s] + h[s], s)]  # (f[u] = d + h, node)

    while heap:
        f_u, u = heapq.heappop(heap)
        if u == t:
            return d[t]  # reached target
        if f_u - h[u] > d[u]:
            continue  # skip stale entry
        for v, w in graph[u]:
            if d[v] > d[u] + w:  # relax edge
                d[v] = d[u] + w
                heapq.heappush(heap, (d[v] + h[v], v))
    return INF  # target unreachable

# Test-Me function for Dijkstra
def TestMe_Dijkstra(points, k=10):
    graph = build_knn_graph(points, k)
    s, t = find_source_target(points)
    return dijkstra(graph, s, t)

# Test-Me function for A*
def TestMe_Astar(points, k=10):
    graph = build_knn_graph(points, k)
    s, t = find_source_target(points)
    return a_star(graph, points, s, t)

# function to run experiments and collect runtimes
def run_experiments(ns, ks):
    results = {k: {'dijkstra': [], 'astar': []} for k in ks}

    for k in ks:
        print(f"Running experiments for k = {k}")
        for n in ns:
            print(f"  n = {n}")
            points = generate_points(n)
            graph = build_knn_graph(points, k)
            s, t = find_source_target(points)

            # warm up once
            dijkstra(graph, s, t)
            a_star(graph, points, s, t)

            # measure Dijkstra runtime
            start = time.perf_counter()
            dist_dijkstra = dijkstra(graph, s, t)
            end = time.perf_counter()
            time_dijkstra = (end - start) * 1000  # ms

            # measure A* runtime
            start = time.perf_counter()
            dist_astar = a_star(graph, points, s, t)
            end = time.perf_counter()
            time_astar = (end - start) * 1000  # ms

            # sanity check: both distances should be equal
            if abs(dist_dijkstra - dist_astar) > 1e-6:
                print("Warning: Dijkstra and A* results do not match!")

            results[k]['dijkstra'].append(time_dijkstra)
            results[k]['astar'].append(time_astar)
    
    return results

# plot results
def plot_results(ns, ks, results):
    for k in ks:
        plt.figure()
        plt.plot(ns, results[k]['dijkstra'], marker='o', label='Dijkstra')
        plt.plot(ns, results[k]['astar'], marker='s', label='A*')
        plt.xlabel("Number of points n")
        plt.ylabel("Runtime (ms)")
        plt.title(f"Runtime vs n for k = {k}")
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.show()

# main function to run everything
def main():
    ns = [100, 500, 1000, 5000, 10000, 20000]
    ks = [5, 10, 20, 50]

    results = run_experiments(ns, ks)  # collect runtime data
    plot_results(ns, ks, results)      # make plots

    # optional: test the Test-Me functions
    points50 = [(random.uniform(0, 100), random.uniform(0, 100)) for _ in range(50)]
    print("TestMe Dijkstra:", TestMe_Dijkstra(points50, k=10))
    print("TestMe A*:", TestMe_Astar(points50, k=10))

if __name__ == "__main__":
    main()
