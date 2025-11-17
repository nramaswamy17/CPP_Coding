#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void dfs(int node, vector<vector<int>>& graph, unordered_set<int>& visited) {
    visited.insert(node);
    cout << node << " ";

    for (int neighbor: graph[node]) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(neighbor, graph, visited);
        }
    }
}

int main () {

    vector<vector<int>> graph(5);

    graph[0] = {1, 2};
    graph[1] = {0, 3};
    graph[2] = {0, 4};
    graph[3] = {1};
    graph[4] = {2};

    unordered_set<int> visited;
    cout << "DFS traversal starting from node 0: ";
    dfs(0, graph, visited);
    cout << endl;
    return 0;
}