#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;
using namespace std::chrono;

/**
 * @class Graph
 * @brief Represents an undirected graph using an ADJACENCY MATRIX
 *        (instead of an adjacency list). Includes DFS, level-order BFS,
 *        cycle detection, and vertex degree reporting.
 */
class Graph {
private:
    int V;                          ///< Number of vertices
    vector<vector<int>> matrix;     ///< Adjacency matrix (0/1)

    /// Recursive DFS helper that also detects back-edges (cycles).
    bool DFSUtil(int v, int parent, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";
        bool cycleFound = false;

        for (int u = 0; u < V; u++) {
            if (matrix[v][u]) {
                if (!visited[u]) {
                    if (DFSUtil(u, v, visited)) cycleFound = true;
                } else if (u != parent) {
                    // Visited neighbor that isn't the parent -> cycle
                    cycleFound = true;
                }
            }
        }
        return cycleFound;
    }

public:
    Graph(int vertices) {
        V = vertices;
        matrix.assign(V, vector<int>(V, 0));
    }

    /// Adds an undirected edge by marking both matrix entries.
    void addEdge(int u, int v) {
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    /// Degree of each vertex (number of edges incident to it).
    void printDegrees() {
        cout << "Vertex degrees:\n";
        for (int i = 0; i < V; i++) {
            int degree = 0;
            for (int j = 0; j < V; j++) degree += matrix[i][j];
            cout << "  Vertex " << i << ": " << degree << "\n";
        }
    }

    /**
     * @brief DFS traversal from a start vertex; reports whether a
     *        cycle was detected in the reachable component.
     */
    void DFS(int start) {
        vector<bool> visited(V, false);
        bool hasCycle = DFSUtil(start, -1, visited);
        cout << (hasCycle ? "\n(Cycle detected in this component)"
                           : "\n(No cycle detected in this component)");
    }

    /**
     * @brief BFS traversal that prints vertices grouped by level
     *        (distance from the start vertex).
     */
    void BFSByLevel(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        int level = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            cout << "Level " << level << ": ";
            for (int i = 0; i < levelSize; i++) {
                int node = q.front();
                q.pop();
                cout << node << " ";
                for (int u = 0; u < V; u++) {
                    if (matrix[node][u] && !visited[u]) {
                        visited[u] = true;
                        q.push(u);
                    }
                }
            }
            cout << "\n";
            level++;
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    // ---- DFS with cycle detection + timing ----
    auto startDFS = high_resolution_clock::now();
    cout << "\nDFS Traversal: ";
    g.DFS(start);
    auto endDFS = high_resolution_clock::now();
    auto dfsTime = duration_cast<nanoseconds>(endDFS - startDFS);

    // ---- BFS by level + timing ----
    auto startBFS = high_resolution_clock::now();
    cout << "\n\nBFS Traversal (by level):\n";
    g.BFSByLevel(start);
    auto endBFS = high_resolution_clock::now();
    auto bfsTime = duration_cast<nanoseconds>(endBFS - startBFS);

    // ---- Extra: vertex degrees ----
    cout << "\n";
    g.printDegrees();

    // ---- Results ----
    cout << "\nExecution Time:";
    cout << "\n  DFS: " << dfsTime.count() << " ns";
    cout << "\n  BFS: " << bfsTime.count() << " ns";

    return 0;
}
