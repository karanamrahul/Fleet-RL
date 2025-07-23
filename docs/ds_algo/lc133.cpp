#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <queue>

// Definition for a Node (as provided in the problem).
class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() : val(0), neighbors(std::vector<Node*>()) {}
    Node(int _val) : val(_val), neighbors(std::vector<Node*>()) {}
    Node(int _val, std::vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {}
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        // If the input graph is empty, return null.
        if (!node) {
            return nullptr;
        }

        // Map to store original nodes and their corresponding clones.
        std::unordered_map<Node*, Node*> visited;

        // Define the recursive DFS function.
        std::function<Node*(Node*)> dfs = [&](Node* original_node) -> Node*{
            // If this node has already been cloned, return its clone from the map.
            if (visited.find(original_node) != visited.end()) {
                return visited[original_node];
            }

            // If not cloned yet, create a new node with the same value.
            Node* clone_node = new Node(original_node->val);
            
            // Add the new clone to the map before exploring its neighbors to handle cycles.
            visited[original_node] = clone_node;

            // Iterate through all neighbors of the original node.
            for (Node* neighbor : original_node->neighbors) {
                // Recursively call dfs for each neighbor and add the returned clone
                // to the new node's neighbors list.
                clone_node->neighbors.push_back(dfs(neighbor));
            }

            // Return the fully cloned node.
            return clone_node;
        };

        // Start the cloning process from the initial node.
        return dfs(node);
    }
};

// Helper function to create a simple graph for testing
Node* createTestGraph() {
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    
    node1->neighbors = {node2, node4};
    node2->neighbors = {node1, node3};
    node3->neighbors = {node2, node4};
    node4->neighbors = {node1, node3};
    
    return node1;
}

// Helper function to print graph using BFS
void printGraph(Node* node, const std::string& title) {
    if (!node) {
        std::cout << title << ": Empty graph" << std::endl;
        return;
    }
    
    std::cout << title << ":" << std::endl;
    std::unordered_map<Node*, bool> visited;
    std::queue<Node*> q;
    q.push(node);
    visited[node] = true;
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        std::cout << "  Node " << current->val << " -> [";
        for (int i = 0; i < current->neighbors.size(); i++) {
            std::cout << current->neighbors[i]->val;
            if (i < current->neighbors.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        
        for (Node* neighbor : current->neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== LeetCode 133: Clone Graph ===" << std::endl;
    std::cout << "Problem: Create a deep copy of an undirected graph" << std::endl;
    std::cout << std::endl;
    
    // Test Case 1: Connected graph
    Node* original = createTestGraph();
    std::cout << "Test 1: 4-node connected graph" << std::endl;
    printGraph(original, "Original Graph");
    
    Solution sol;
    Node* cloned = sol.cloneGraph(original);
    printGraph(cloned, "Cloned Graph");
    
    // Verify they are different objects but same structure
    std::cout << "Memory addresses:" << std::endl;
    std::cout << "  Original node 1: " << original << std::endl;
    std::cout << "  Cloned node 1: " << cloned << std::endl;
    std::cout << "  Different objects: " << (original != cloned ? "✓ PASS" : "✗ FAIL") << std::endl;
    std::cout << std::endl;
    
    // Test Case 2: Empty graph
    std::cout << "Test 2: Empty graph" << std::endl;
    Node* emptyClone = sol.cloneGraph(nullptr);
    std::cout << "  Original: nullptr" << std::endl;
    std::cout << "  Cloned: " << (emptyClone == nullptr ? "nullptr ✓ PASS" : "not nullptr ✗ FAIL") << std::endl;
    std::cout << std::endl;
    
    // Test Case 3: Single node
    std::cout << "Test 3: Single node" << std::endl;
    Node* single = new Node(1);
    Node* singleClone = sol.cloneGraph(single);
    printGraph(single, "Original Single Node");
    printGraph(singleClone, "Cloned Single Node");
    
    std::cout << "=== Summary ===" << std::endl;
    std::cout << "Key Learning: Graph cloning requires:" << std::endl;
    std::cout << "- HashMap to track visited nodes and avoid infinite loops" << std::endl;
    std::cout << "- DFS/BFS to traverse all connected nodes" << std::endl;
    std::cout << "- Create new nodes while preserving the graph structure" << std::endl;
    
    return 0;
}
