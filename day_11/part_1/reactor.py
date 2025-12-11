def parse_graph(filename):
    graph = {}
    with open(filename, "r") as input:
        for line in input:
            line = line.strip()
            if not line:
                continue
            node, neighbors = line.split(":")
            node = node.strip()
            graph[node] = neighbors.strip().split()
    return graph

def dfs(node, path, all_paths, graph):
    path.append(node)
    if node == "out":
        all_paths.append(path.copy())
    else:
        for neighbor in graph.get(node, []):
            dfs(neighbor, path, all_paths, graph)
    path.pop()

all_paths = []
graph = parse_graph("input.txt")
dfs("you", [], all_paths, graph)

print(f"Total number of paths: {len(all_paths)}")
