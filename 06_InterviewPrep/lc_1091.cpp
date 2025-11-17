/*
Shortest Path in Binary Matrix (LC 1091)

Given:
- nxn binary matrix

Task: 
- Return length of the shortest clear path 

Constraints:
- Can only traverse 0's
- Can move in 8 directions

Idea:
- BFS?
- How do I store the parent info? With a pointer?
- Shortest path is implicit in BFS strategy

Pseudocode:

shortest_path (grid, start, target)
    define queue q
    define visited vector

    push start to q with distance 0
    add start to visited

    while q is not empty
        current = q's front
        pop q

        position = x,y position of current
        distance = distance of current

        if current position == target position
            return distance

        neighbors = getNeighbors
        for each of neighbors
            if neighbors are in_bounds
                if neighbors are unvisited & equal to 0-
                    mark neighbor as visited
                    push to q with distance + 1

    return -1
*/
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<pair<int,int>> get_neighbors(vector<vector<int>>& grid, pair<int,int> position) {
    return {
        {position.first+1, position.second+1}, // top right
        {position.first, position.second+1}, // top
        {position.first-1, position.second+1}, // top left
        {position.first-1, position.second}, // left
        {position.first-1, position.second-1}, // bottom left
        {position.first, position.second-1}, // bottom
        {position.first+1, position.second-1}, // bottom right
        {position.first+1, position.second} // right
    };
}

int shortest_path(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> target) {
    queue<pair<pair<int,int>,int>> q;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    int distance = 0;
    // contains a pair<int,int> and a int
    q.push({start, distance});
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        pair<int,int> position = q.front().first;
        int distance = q.front().second;
        q.pop();

        if (position == target) {
            return distance;
        }

        vector<pair<int,int>> neighbors = get_neighbors(grid, position);
        for (pair<int,int> neighbor: neighbors) {
            bool inBounds = neighbor.first < grid.size() && neighbor.first >= 0;
            inBounds = inBounds && (neighbor.second < grid[0].size() && neighbor.second >= 0);

            if (inBounds) {
                //cout << neighbor.first;
                bool isVisited = visited[neighbor.first][neighbor.second] == false;
                bool isZero = grid[neighbor.first][neighbor.second] == 0;

                if(isVisited && isZero) {
                    q.push({neighbor, distance+1});
                    visited[neighbor.first][neighbor.second] = true;
                }
            }
        }
    }
    return -1; 
} 

int main() {
    vector<vector<int>> grid = {
        {0, 1, 1},
        {0, 1, 0},
        {0, 0, 0}
    };
    pair<int,int> start = {0,0};
    pair<int,int> target = {2,2};
    int dist = shortest_path(grid, start, target);
    cout << "Distance: " << dist << endl;
    return 0;
} 