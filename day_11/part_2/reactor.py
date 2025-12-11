from functools import lru_cache

def parse_graph(filename):
    graph = {}
    with open(filename, "r") as input:
        for line in input:
            line = line.strip()
            if not line:
                continue
            node, neighbors = line.split(":")
            graph[node.strip()] = neighbors.strip().split()
    return graph

SPECIAL = ["dac", "fft"]
BIT = {name: i for i, name in enumerate(SPECIAL)}

def add_memoized_counting(graph):
    @lru_cache(None)
    def dfs(node, mask):
        if node == "out":
            return 1 if mask == (1 << len(SPECIAL)) - 1 else 0

        if node in BIT:
            mask |= (1 << BIT[node])

        total = 0
        for neigh in graph.get(node, []):
            total += dfs(neigh, mask)
        return total

    return dfs

graph = parse_graph("input.txt")
dfs = add_memoized_counting(graph)

print("Total valid paths:", dfs("svr", 0))
