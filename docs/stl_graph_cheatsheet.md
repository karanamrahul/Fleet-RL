# STL Graph Algorithms Cheat Sheet

## 📊 Graph Representation

### 1. Adjacency List (Most Common)
```cpp
// Unweighted graph
vector<vector<int>> graph(n);
graph[u].push_back(v); // Add edge u -> v

// Weighted graph
vector<vector<pair<int, int>>> graph(n); // {neighbor, weight}
graph[u].push_back({v, weight});

// Using unordered_map for dynamic nodes
unordered_map<int, vector<int>> graph;
```

### 2. Adjacency Matrix
```cpp
vector<vector<int>> matrix(n, vector<int>(n, 0));
matrix[u][v] = 1; // or weight for weighted graphs
```

### 3. Edge List
```cpp
vector<pair<int, int>> edges; // For unweighted
vector<tuple<int, int, int>> edges; // {u, v, weight}
```

## 🔍 Graph Traversal Algorithms

### DFS (Depth-First Search)
```cpp
// Recursive DFS
vector<bool> visited(n, false);
function<void(int)> dfs = [&](int node) {
    visited[node] = true;
    // Process node
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
};

// Iterative DFS with stack
stack<int> st;
vector<bool> visited(n, false);
st.push(start);
while (!st.empty()) {
    int node = st.top();
    st.pop();
    if (!visited[node]) {
        visited[node] = true;
        // Process node
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                st.push(neighbor);
            }
        }
    }
}
```

### BFS (Breadth-First Search)
```cpp
queue<int> q;
vector<bool> visited(n, false);
vector<int> distance(n, -1);

q.push(start);
visited[start] = true;
distance[start] = 0;

while (!q.empty()) {
    int node = q.front();
    q.pop();
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            distance[neighbor] = distance[node] + 1;
            q.push(neighbor);
        }
    }
}
```

## 🔄 Cycle Detection

### Undirected Graph (DFS)
```cpp
function<bool(int, int)> hasCycleDFS = [&](int node, int parent) -> bool {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (hasCycleDFS(neighbor, node)) return true;
        } else if (neighbor != parent) {
            return true; // Back edge found
        }
    }
    return false;
};
```

### Directed Graph (3-Color DFS)
```cpp
// 0 = White (unvisited), 1 = Gray (processing), 2 = Black (done)
vector<int> color(n, 0);
function<bool(int)> hasCycle = [&](int node) -> bool {
    if (color[node] == 1) return true;  // Back edge (cycle)
    if (color[node] == 2) return false; // Already processed
    
    color[node] = 1; // Mark as processing
    for (int neighbor : graph[node]) {
        if (hasCycle(neighbor)) return true;
    }
    color[node] = 2; // Mark as done
    return false;
};
```

## 📋 Topological Sort

### Kahn's Algorithm (BFS-based)
```cpp
vector<int> indegree(n, 0);
for (int u = 0; u < n; u++) {
    for (int v : graph[u]) {
        indegree[v]++;
    }
}

queue<int> q;
for (int i = 0; i < n; i++) {
    if (indegree[i] == 0) q.push(i);
}

vector<int> topoOrder;
while (!q.empty()) {
    int node = q.front();
    q.pop();
    topoOrder.push_back(node);
    
    for (int neighbor : graph[node]) {
        indegree[neighbor]--;
        if (indegree[neighbor] == 0) {
            q.push(neighbor);
        }
    }
}

// Check if topological sort is possible
if (topoOrder.size() != n) {
    // Graph has cycle
}
```

### DFS-based Topological Sort
```cpp
vector<bool> visited(n, false);
stack<int> st;

function<void(int)> dfs = [&](int node) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
    st.push(node); // Push after processing all neighbors
};

for (int i = 0; i < n; i++) {
    if (!visited[i]) dfs(i);
}

vector<int> topoOrder;
while (!st.empty()) {
    topoOrder.push_back(st.top());
    st.pop();
}
```

## 🛣️ Shortest Path Algorithms

### Dijkstra's Algorithm
```cpp
vector<int> dijkstra(int start, vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[start] = 0;
    pq.push({0, start}); // {distance, node}
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

### Floyd-Warshall (All Pairs)
```cpp
vector<vector<int>> floyd(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist = graph;
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    return dist;
}
```

## 🔗 Connected Components

### Union-Find (Disjoint Set Union)
```cpp
class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
        return true;
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
```

### DFS for Connected Components
```cpp
int countComponents(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    int components = 0;
    
    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    };
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            components++;
        }
    }
    return components;
}
```

## 🌲 Minimum Spanning Tree

### Kruskal's Algorithm
```cpp
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    int mstWeight = 0;
    
    for (const Edge& e : edges) {
        if (uf.unite(e.u, e.v)) {
            mstWeight += e.weight;
        }
    }
    return mstWeight;
}
```

### Prim's Algorithm
```cpp
int prim(vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<bool> inMST(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    pq.push({0, 0}); // {weight, node}
    int mstWeight = 0;
    
    while (!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();
        
        if (inMST[u]) continue;
        inMST[u] = true;
        mstWeight += weight;
        
        for (auto [v, w] : graph[u]) {
            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }
    return mstWeight;
}
```

## 🔧 Useful STL Containers for Graphs

### Priority Queue (for Dijkstra, Prim's)
```cpp
// Min-heap
priority_queue<int, vector<int>, greater<int>> minHeap;

// Custom comparator for pairs
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
```

### Unordered Map/Set for Dynamic Graphs
```cpp
unordered_map<int, vector<int>> graph;
unordered_set<int> visited;
```

### Stack for DFS
```cpp
stack<int> dfs_stack;
```

### Queue for BFS
```cpp
queue<int> bfs_queue;
```

## 🎯 Common Graph Problem Patterns

| Problem Type | Algorithm | Time Complexity | Space Complexity |
|--------------|-----------|-----------------|------------------|
| Shortest Path (unweighted) | BFS | O(V + E) | O(V) |
| Shortest Path (weighted) | Dijkstra | O((V + E) log V) | O(V) |
| All Pairs Shortest Path | Floyd-Warshall | O(V³) | O(V²) |
| Cycle Detection (Undirected) | DFS | O(V + E) | O(V) |
| Cycle Detection (Directed) | 3-Color DFS | O(V + E) | O(V) |
| Topological Sort | Kahn's / DFS | O(V + E) | O(V) |
| Connected Components | DFS/BFS/Union-Find | O(V + E) | O(V) |
| Minimum Spanning Tree | Kruskal/Prim | O(E log E) | O(V) |

## 📚 LeetCode Problems Solved

### LC 133: Clone Graph
- **Algorithm**: DFS with HashMap
- **Key Insight**: Use visited map to handle cycles
- **Pattern**: Graph cloning/deep copy

### LC 200: Number of Islands  
- **Algorithm**: DFS/BFS on 2D grid
- **Key Insight**: Mark visited cells to avoid double counting
- **Pattern**: Connected components in grid

### LC 207: Course Schedule
- **Algorithm**: Cycle detection in directed graph
- **Key Insight**: 3-color DFS (White, Gray, Black)
- **Pattern**: Dependency resolution, topological ordering

---

*Last updated: July 22, 2025*
*Repository: /home/rahul/DREAM/Fleet-RL*
