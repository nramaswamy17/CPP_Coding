/*
Given: 
- mxn 2D binary grid

Task: 
- Return the number of islands

Constraints:
- 1 is land, 0 is water
- An island is a 1 surrounded by 0's

Idea:
- Check each cell with value 1 to see if on all sides it is surrounded by water or border
    - O(m * n) time complexity

Pseudocode:

function numIslands(grid)
    if grid is empty
        return 0
    num_islands = 0
    define rows, cols based on gridsie

    for each row in rows
        for each col in cols
            if grid[row][col] is 1
                // Incremeent islands b/c we found unvisited land
                num_islands += 1

                // Mark all connected land as visited (convert 1 to 0)
                dfs(grid, i, j)
    return num_islands

function dfs(grid, row, col)
    if i < 0 or i >= rows or j < 0 or j >= cols
        // base case, return if bounds are exited
        return
    if grid[row][col] is 0
        return
    
    grid[row][col] = 0 // set current cell to 0  (visited)

    // explore all 4 directions around island recursively
    dfs(grid, i-1, j) //up
    dfs(grid, i+1, j) // down
    dfs(grid, i, j-1) // left
    dfs(grid, i, j+1) // right


*/

#include <vector>
#include <iostream>

using namespace std;

void dfs(vector<vector<string>>& grid, int row, int col) {
    int rows = grid.size();
    int cols = grid[0].size();

    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return;
    }
    if (grid[row][col] == "0") {
        return;
    }
    grid[row][col] = "0"; // set current cell to 0 

    dfs(grid, row-1, col);
    dfs(grid, row+1, col);
    dfs(grid, row, col-1);
    dfs(grid, row, col+1);
}

int numIslands(vector<vector<string>>& grid) {
    
    if (grid.size() == 0) {
        return 0;
    }
    int num_islands = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if (grid[row][col] == "1") {
                num_islands += 1;

                // mark all connected pieces as 0
                dfs(grid, row, col);
            }
        }
    }
    
    return num_islands;
}

int main() {
    vector<vector<string>> grid = {
        {"1","1","0","0","0"},
        {"1","1","0","0","0"},
        {"0","0","1","0","0"},
        {"0","0","0","1","1"}
    };
    
    cout << numIslands(grid) << endl;
    
    return 0;
}
