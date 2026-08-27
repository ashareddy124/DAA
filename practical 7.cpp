from collections import deque

class Graph:
    def __init__(self):
        self.graph = {}

    # Add a vertex
    def add_vertex(self, vertex):
        if vertex not in self.graph:
            self.graph[vertex] = []

    # Add an edge
    def add_edge(self, u, v):
        self.add_vertex(u)
        self.add_vertex(v)

        # Undirected graph
        self.graph[u].append(v)
        self.graph[v].append(u)

    # DFS
    def dfs(self, start):
        visited = set()

        def dfs_recursive(vertex):
            visited.add(vertex)
            print(vertex, end=" ")

            for neighbor in self.graph[vertex]:
                if neighbor not in visited:
                    dfs_recursive(neighbor)

        dfs_recursive(start)
        print()

    # BFS
    def bfs(self, start):
        visited = set()
        queue = deque()

        visited.add(start)
        queue.append(start)

        while queue:
            vertex = queue.popleft()
            print(vertex, end=" ")

            for neighbor in self.graph[vertex]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)

        print()


# Create graph
g = Graph()

g.add_edge(0, 1)
g.add_edge(0, 2)
g.add_edge(1, 3)
g.add_edge(1, 4)
g.add_edge(2, 5)

print("DFS traversal:")
g.dfs(0)

print("BFS traversal:")
g.bfs(0)
