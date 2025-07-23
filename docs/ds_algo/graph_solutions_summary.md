# Graph Problems Solutions Summary

## 🎯 Problems Solved

### 1. LC 133: Clone Graph ✅
**Problem**: Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph.

**Solution Approach**: DFS with HashMap
- Use `unordered_map<Node*, Node*>` to track original → clone mapping
- DFS traversal to visit all nodes
- Create new nodes while avoiding infinite loops in cycles

**Key Learning**: Graph cloning requires tracking visited nodes to handle cycles properly.

**Time Complexity**: O(V + E)  
**Space Complexity**: O(V)

---

### 2. LC 200: Number of Islands ✅
**Problem**: Given an m x n 2D binary grid which represents a map of '1's (land) and '0's (water), return the number of islands.

**Solution Approach**: DFS on 2D Grid
- Iterate through each cell in the grid
- When we find '1' (land), increment island counter and DFS to "sink" the entire island
- Mark visited cells as '0' to avoid double counting

**Key Learning**: Connected components in a 2D grid using 4-directional DFS.

**Time Complexity**: O(m × n)  
**Space Complexity**: O(m × n) for recursion stack

---

### 3. LC 207: Course Schedule ✅
**Problem**: Given `numCourses` and a list of prerequisite pairs, determine if you can finish all courses.

**Solution Approach**: Cycle Detection in Directed Graph (3-Color DFS)
- Build adjacency list from prerequisites
- Use 3-color DFS: White (0), Gray (1), Black (2)
- If we encounter a Gray node during DFS → cycle detected → impossible to finish

**Key Learning**: Course scheduling is essentially detecting cycles in a dependency graph.

**Time Complexity**: O(V + E)  
**Space Complexity**: O(V)

---

## 🔧 Common Patterns Learned

### 1. Graph Representation
```cpp
// Most common: Adjacency List
vector<vector<int>> graph(n);
```

### 2. DFS Template
```cpp
function<void(int)> dfs = [&](int node) {
    visited[node] = true;
    // Process node
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
};
```

### 3. BFS Template
```cpp
queue<int> q;
vector<bool> visited(n, false);
q.push(start);
visited[start] = true;

while (!q.empty()) {
    int node = q.front();
    q.pop();
    // Process node
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            q.push(neighbor);
        }
    }
}
```

### 4. Cycle Detection (Directed Graph)
```cpp
// 3-Color DFS
vector<int> color(n, 0); // 0=White, 1=Gray, 2=Black
function<bool(int)> hasCycle = [&](int node) -> bool {
    if (color[node] == 1) return true;  // Back edge
    if (color[node] == 2) return false; // Already done
    
    color[node] = 1; // Mark as processing
    for (int neighbor : graph[node]) {
        if (hasCycle(neighbor)) return true;
    }
    color[node] = 2; // Mark as done
    return false;
};
```

## 📊 Complexity Summary

| Problem | Algorithm | Time | Space | Key Data Structure |
|---------|-----------|------|-------|-------------------|
| LC 133 | DFS + HashMap | O(V+E) | O(V) | `unordered_map<Node*, Node*>` |
| LC 200 | DFS on Grid | O(m×n) | O(m×n) | 2D vector, recursion stack |
| LC 207 | 3-Color DFS | O(V+E) | O(V) | `vector<int>` for colors |

## 🚀 Next Steps

### Related Problems to Practice:
- **LC 210**: Course Schedule II (return actual order)
- **LC 547**: Number of Provinces (connected components)
- **LC 994**: Rotting Oranges (multi-source BFS)
- **LC 1162**: As Far from Land as Possible (BFS shortest path)
- **LC 684**: Redundant Connection (cycle detection in undirected graph)

### Advanced Topics:
- Topological Sort (Kahn's Algorithm)
- Shortest Path (Dijkstra, Bellman-Ford)
- Minimum Spanning Tree (Kruskal, Prim)
- Strongly Connected Components (Tarjan's, Kosaraju's)

---

**Status**: ✅ All 3 problems completed and tested  
**Date**: July 22, 2025  
**Next Goal**: Push solutions to repository and update STL knowledge base
