/*
LC 102: Binary Tree Level Order Traversal (BFS)

Given:
- Root Node
- Binary Tree

Task:
- Return the level order traversal (L->R by level)

Constraints:
- None

Idea:
- BFS

Pseudocode:

void level_order_traversal(root)
    define queue 
    define visited set 

    Push root to queue
    add root to visited set

    while queue is not empty
        current = queue top element
        print current

        neighbors = children of current node
        for each neighbor
            add to queue
            add to visited set
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <list>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* build_tree(vector<int>& tree, int index) {
    if (index >= tree.size() || tree[index] == -1) {
        return nullptr;
    }

    Node* node = new Node();
    node->data = tree[index];

    node->left = build_tree(tree, 2*index+1);
    node->right = build_tree(tree, 2*index + 2);

    return node;
}


vector<vector<int>> level_order_traversal(Node* root) {
    if (root == nullptr) {
        return {{}};
    }
    queue<Node*> q;
    vector<vector<int>> result;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); // how many nodes are at the current level
        vector<int> currentLevel;

        for (int i = 0; i < levelSize; i++) {
            Node* node = q.front(); q.pop();
            cout << node->data << " ";
            currentLevel.push_back(node->data);

            if (node->left) {
                q.push(node->left);
            } 
            if (node->right) {
                q.push(node->right);
            }
        }
        result.push_back(currentLevel);
    }
    return result;

}

int main() {
    vector<int> tree = {3,9,20,-1,-1,15,7};
    Node* root = build_tree(tree, 0);
    level_order_traversal(root);
    return 0;
}