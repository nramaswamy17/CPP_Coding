#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// Simple 2D Point
struct Point {
    int x, y;
    bool operator == (const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Node in our search
struct Node {
    Point pos;
    double g; 
    double h;
    double f;

    Point parent; // For reconstruction

    // For min heap
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

class AStar {
private:
    vector<vector<int>> grid; 
    int rows, cols;

    // Calculate straight-line distance (heuristic)
    double heuristic(const Point& a, const Point& b) {
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        return sqrt(dx*dx + dy*dy);
    }

    // Is the point within the grid bounds and NOT obstructed
    bool is_valid(const Point& p) {
        return p.x >= 0 && p.x < cols &&
                p.y >= 0 && p.y < rows &&
                grid[p.y][p.x] == 0;
    }

    // Get neighbors (up, down, left, right)
    vector<Point> get_neighbors(const Point& p) {
        vector<Point> neighbors;

        // Right, Left, Down, Up
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            Point neighbor = {p.x + dx[i], p.y + dy[i]};
            if (is_valid(neighbor)) {
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }
public:
    AStar(const vector<vector<int>>& map) : grid(map) {
        rows = grid.size();
        cols = grid[0].size();
    }

    vector<Point> find_path(Point start, Point goal) {
        // Min heap: get the node with smallest f value
        priority_queue<Node, vector<Node>, greater<Node>> open_set;

        // Track visited nodes
        vector<vector<bool>> visited(rows, vector<bool>(cols,false));

        // Track how we got to each node (path reconstruction)
        vector<vector<Point>> came_from(rows, vector<Point>(cols, {-1, -1}));

        // Start node
        Node start_node;
        start_node.pos = start;
        start_node.g = 0;
        start_node.h = heuristic(start, goal);
        start_node.f = start_node.h;
        start_node.parent = {-1, -1};

        open_set.push(start_node);

        cout << "Searching from (" << start.x << "," << start.y << ") "
        << "to (" << goal.x << "," << goal.y << ")\n\n";

        int iterations = 0;

        // Main search loop
        while (!open_set.empty()) {
            // Get node with lowest f
            Node current = open_set.top();
            open_set.pop();

            iterations++;

            // Already visited? Skip
            if (visited[current.pos.y][current.pos.x]) {
                continue;
            }

            visited[current.pos.y][current.pos.x] = true;
            came_from[current.pos.y][current.pos.x] = current.parent;
        
            cout << "Exploring (" << current.pos.x << "," << current.pos.y << ") "
            << "f=" << current.f << " g=" << current.g << " h=" << current.h << "\n";
    
            if (current.pos == goal) {
                cout << "\nGoal reached in " << iterations << " iterations!\n";
                return reconstruct_path(came_from, start, goal);
            }

            // Check all neighbors
            for (const Point& neighbor : get_neighbors(current.pos)) {
                if (visited[neighbor.y][neighbor.x]) {
                    continue;
                }

                // Create neighbor node
                Node next;
                next.pos = neighbor;
                next.g = current.g + 1; // each step costs 1
                next.h = heuristic(neighbor, goal);
                next.f = next.g + next.h;
                next.parent = current.pos;

                open_set.push(next);
            }
        }
    
        cout << "\nNo path found\n";
        return {};
    }

    // Reconstruct path from the came_from mapping
    vector<Point> reconstruct_path(const vector<vector<Point>>& came_from, Point start, Point goal) {
        vector<Point> path;
        Point current = goal;

        // Walk backwards from goal to start
        while(!(current == start)) {
            path.push_back(current);
            current = came_from[current.y][current.x];
        }
        path.push_back(start);

        // Reverse to get start -> goal
        reverse(path.begin(), path.end());
        return path;
    }

    // Visualize grid & path
    void print_path(const vector<Point> & path) {
        // Create copy of grid for visualization
        vector<vector<char>> display(rows, vector<char>(cols, '.'));

        // Mark obstacles
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (grid[y][x] == 1) {
                    display[y][x] = '#';
                }
            }
        }

        // Mark path
        for (const Point& p : path) {
            display[p.y][p.x] = '*';
        }

        // Mark start & goal
        if (!path.empty()) {
            display[path.front().y][path.front().x] = 'S';
            display[path.back().y][path.back().x] = 'G';
        }

        // Print
        cout << "\nPath Visualization:\n";
        for (const auto& row : display) {
            for (char c : row) {
                cout << c << " ";
            }
            cout << "\n";
        }
        cout << "\nPath length: " << path.size() << " steps\n";
    }
};


int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    AStar astar(grid);

    Point start = {0, 3};
    Point goal = {6, 1};

    vector<Point> path = astar.find_path(start, goal);

    if (!path.empty()) {
        astar.print_path(path);

        cout << "\n{ath Coordinates\n";
        for (const Point& p : path) {
            cout << "(" << p.x << "," << p.y << ") ";
        }
        cout << "\n";
    }
    return 0;
}