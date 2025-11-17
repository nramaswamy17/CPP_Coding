/*
Pseudocode

canReach(grid, start, target)
    define queue
    define visited 2d array and set default to false
    
    set start position as visited 
    push start to queue
    
    while queue is not empty
        current = pop from queue

        if current == target
            return true
        
        for each neighbor (up down left right)
            valid = neighbor is within bounds AND not an obstacle AND not visited yet
            if neighbor is valid
                mark neighbor as visited
                push to queue
    return false

*/


#include <vector>
#include <queue>
#include <iostream>
using namespace std;

vector<pair<int,int>> getNeighbors(pair<int,int>& current) {
    return {
        {current.first-1, current.second},
        {current.first+1, current.second},
        {current.first, current.second-1},
        {current.first, current.second+1}
    };
}


bool canReach(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> target) {
    queue<pair<int,int>> q;
    vector<vector<bool>> visited(grid.size(), (vector<bool>(grid.size(), false)));

    visited[start.first][start.second] = true;
    q.push(start);

    while (!q.empty()) {
        pair<int,int> current = q.front();
        q.pop();

        if (current == target) {
            return true;
        }

        for (pair<int,int> neighbor: getNeighbors(current)) {
            bool isN1InBounds = neighbor.first >= 0 && neighbor.first < grid.size();
            bool isN2InBounds = neighbor.second >= 0 && neighbor.second < grid.size();  

            if (isN1InBounds && isN2InBounds) {
                bool isNotObstacle = grid[neighbor.first][neighbor.second] == 0;
                bool isNotVisited = visited[neighbor.first][neighbor.second] == false;

                if (isNotObstacle && isNotVisited){
                    visited[neighbor.first][neighbor.second] = true;
                    q.push(neighbor);
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
    pair<int, int> target = {3, 3};
    bool val = canReach(grid, start, target);
    cout << val << endl;
    return 0;
}