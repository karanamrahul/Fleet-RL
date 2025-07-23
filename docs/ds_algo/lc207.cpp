#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <functional>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Step 1: Build the graph representation
        // We'll use an adjacency list: graph[i] = list of courses that depend on course i
        vector<vector<int>> graph(numCourses);
        
        for (auto& prereq : prerequisites) {
            int course = prereq[0];          // course that has prerequisite
            int prerequisite = prereq[1];    // prerequisite course
            
            // Add edge: prerequisite -> course
            graph[prerequisite].push_back(course);
        }
        
        // Step 2: Cycle Detection using DFS with colors
        // 0 = White (unvisited), 1 = Gray (in progress), 2 = Black (done)
        vector<int> color(numCourses, 0);
        
        // Define DFS function to detect cycles
        function<bool(int)> hasCycle = [&](int course) -> bool {
            if (color[course] == 1) {
                // Found a gray node - cycle detected!
                return true;
            }
            
            if (color[course] == 2) {
                // Already processed, no cycle from this path
                return false;
            }
            
            // Mark as gray (in progress)
            color[course] = 1;
            
            // Visit all neighbors
            for (int neighbor : graph[course]) {
                if (hasCycle(neighbor)) {
                    return true;
                }
            }
            
            // Mark as black (completely processed)
            color[course] = 2;
            return false;
        };
        
        // Check each course for cycles
        for (int i = 0; i < numCourses; i++) {
            if (color[i] == 0) {  // Only check unvisited courses
                if (hasCycle(i)) {
                    return false; // Cycle found - cannot finish all courses
                }
            }
        }
        
        return true; // No cycle - can finish all courses
    }
};

// Helper function to print test results
void runTest(int testNum, int numCourses, vector<vector<int>>& prerequisites, bool expected) {
    Solution sol;
    bool result = sol.canFinish(numCourses, prerequisites);
    
    cout << "Test " << testNum << ":" << endl;
    cout << "  Number of courses: " << numCourses << endl;
    cout << "  Prerequisites: [";
    for (int i = 0; i < prerequisites.size(); i++) {
        cout << "[" << prerequisites[i][0] << "," << prerequisites[i][1] << "]";
        if (i < prerequisites.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "  Expected: " << (expected ? "true" : "false") << endl;
    cout << "  Got: " << (result ? "true" : "false") << endl;
    cout << "  " << (result == expected ? "✓ PASS" : "✗ FAIL") << endl;
    cout << endl;
}

int main() {
    cout << "=== LeetCode 207: Course Schedule ===" << endl;
    cout << "Problem: Given numCourses and prerequisites, determine if you can finish all courses" << endl;
    cout << "Prerequisites format: [course, prerequisite] means you must take 'prerequisite' before 'course'" << endl;
    cout << endl;
    
    // Test Case 1: Simple case - can finish
    vector<vector<int>> prereq1 = {{1,0}};
    runTest(1, 2, prereq1, true);
    
    // Test Case 2: Cycle exists - impossible to finish
    vector<vector<int>> prereq2 = {{1,0},{0,1}};
    runTest(2, 2, prereq2, false);
    
    // Test Case 3: Complex case - can finish
    vector<vector<int>> prereq3 = {{1,0},{2,0},{3,1},{3,2}};
    runTest(3, 4, prereq3, true);
    
    // Test Case 4: No prerequisites
    vector<vector<int>> prereq4 = {};
    runTest(4, 1, prereq4, true);
    
    // Test Case 5: 3-node cycle - impossible to finish
    vector<vector<int>> prereq5 = {{1,0},{2,1},{0,2}};
    runTest(5, 3, prereq5, false);
    
    cout << "=== Summary ===" << endl;
    cout << "Key Learning: This problem is about detecting cycles in a directed graph." << endl;
    cout << "- If there's a cycle in prerequisites, it's impossible to finish all courses." << endl;
    cout << "- We use DFS with color coding: White(0), Gray(1), Black(2)" << endl;
    cout << "- Finding a Gray node during DFS means we found a cycle!" << endl;
    
    return 0;
}