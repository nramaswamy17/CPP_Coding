/*
Given:
    - 2d array grid
    - start pair
    - target pair

Task: 
    - Output a boolean value on whether or not a robot can reach the goal

Idea:
    Use BFS to find the path to the end node

Pseudocode:

bool canReach(vector<vector<int>>& grid, pair<int,int>& start, pair<int,int>& target)
    
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

vector<pair<int,int>> getNeighbors(pair<int,int>& current) {
    return {{current.first + 1, current.second}, 
            {current.first - 1, current.second},
            {current.first, current.second + 1},
            {current.first, current.second - 1}
            };
}

bool canReach(vector<vector<int>>& grid, pair<int,int>& start, pair<int,int>& target) {
    // Set up 
    queue<pair<int,int>> q;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid.size(), false)); // set default value to false

    // Initialize
    q.push(start);
    visited[start.second][start.first] = true;
    pair<int,int> current;
    int col, row;

    while (!q.empty()) {
        current = q.front();
        q.pop();

        if (current == target) {
            cout << "Reached Target: (" << current.first << ", " << current.second << ")" << endl;
            return true;
        }

        // Explore neighbors
        vector<pair<int,int>> neighbors = getNeighbors(current);
        for (pair<int,int> neighbor : neighbors) {
            bool check_firstN = neighbor.first >= 0 && neighbor.first < grid.size();
            bool check_secondN = neighbor.second >= 0 && neighbor.second < grid[0].size();
            if (check_firstN && check_secondN) {
                bool check_obstacle = grid[neighbor.first][neighbor.second] == 0;
                bool check_visited = visited[neighbor.first][neighbor.second] == false;

                if (check_obstacle && check_visited) {
                    visited[neighbor.first][neighbor.second] = true;
                    q.push(neighbor);
                    cout << "Neighbor: (" << neighbor.first << ", " << neighbor.second << ")" << endl;
            
                }
            }
        }
    }
    return false;

}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };
    pair<int,int> start = {0, 0};
    pair<int,int> target = {3, 3};
    bool val = canReach(grid, start, target);
    cout << "Result: " << val << endl;
    return 0;
}