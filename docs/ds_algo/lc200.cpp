#include <vector>
#include <iostream>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        const int rows = static_cast<int>(grid.size());      // Number of rows in the grid
        const int cols = static_cast<int>(grid[0].size());   // Number of columns in the grid
        int islands = 0;                                     // Counter for islands

        // This is a helper function (DFS) to "sink" an island.
        // It visits all connected '1's (land) and marks them as '0' (water).
        auto dfs = [&](auto&& self, int r, int c) -> void {
            // If out of bounds or at water, stop
            if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == '0')
                return;

            grid[r][c] = '0';               // Mark this cell as visited (turn land into water)
            self(self, r - 1, c);           // Visit cell above
            self(self, r + 1, c);           // Visit cell below
            self(self, r, c - 1);           // Visit cell to the left
            self(self, r, c + 1);           // Visit cell to the right
        };

        // Go through every cell in the grid
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (grid[r][c] == '1') {    // If we find land
                    ++islands;              // We found a new island
                    dfs(dfs, r, c);         // Sink the whole island so we don't count it again
                }

        return islands;                     // Return the total number of islands found
    }
};

// Helper function to run test cases
void runTest(int testNum, std::vector<std::vector<char>> grid, int expected) {
    std::cout << "Test " << testNum << ":" << std::endl;
    std::cout << "  Grid:" << std::endl;
    for (const auto& row : grid) {
        std::cout << "    ";
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    
    Solution sol;
    int result = sol.numIslands(grid);
    
    std::cout << "  Expected: " << expected << std::endl;
    std::cout << "  Got: " << result << std::endl;
    std::cout << "  " << (result == expected ? "✓ PASS" : "✗ FAIL") << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "=== LeetCode 200: Number of Islands ===" << std::endl;
    std::cout << "Problem: Count the number of islands in a 2D grid" << std::endl;
    std::cout << "'1' represents land, '0' represents water" << std::endl;
    std::cout << std::endl;
    
    // Test Case 1: Multiple islands
    std::vector<std::vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    runTest(1, grid1, 1);
    
    // Test Case 2: Multiple separate islands
    std::vector<std::vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    runTest(2, grid2, 3);
    
    // Test Case 3: No islands
    std::vector<std::vector<char>> grid3 = {
        {'0','0','0','0'},
        {'0','0','0','0'}
    };
    runTest(3, grid3, 0);
    
    // Test Case 4: Single cell island
    std::vector<std::vector<char>> grid4 = {
        {'1'}
    };
    runTest(4, grid4, 1);
    
    std::cout << "=== Summary ===" << std::endl;
    std::cout << "Key Learning: Island counting uses DFS to:" << std::endl;
    std::cout << "- Find connected components in a 2D grid" << std::endl;
    std::cout << "- Mark visited cells to avoid double counting" << std::endl;
    std::cout << "- Use 4-directional movement (up, down, left, right)" << std::endl;
    
    return 0;
}
