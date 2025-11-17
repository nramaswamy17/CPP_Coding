#include <iostream>
#include <queue>

// Node structure
template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const T& value) : data(value, left(nullptr), right(nullptr)) {
        std::cout << "  [NODE CREATED] " << data << "\n";
    }
    
    ~TreeNode() {
        std::cout << "  [NODE DELETED] " << data << "\n";
    }
};

// Binary Search Tree (BST)
template <typename T>
class BST {
private:
    TreeNode<T>* root;
    size_t size;

public:
    // Constructor
    BST() : root(nullptr), size(0) {
        std::cout << "[CONSTRUCTOR] Created empty BST\n";
    }
    
    // Destructor
    ~BST() {
        std::cout << "[DESTRUCTOR] Deleting BST...\n";
        clear(); // delete all nodes
    }

    // insert - O(logn) avg, O(n) worst case
    void insert(const T& value) {
        root = insertHelper(root, valeu);
        size++;
    }


    // Search for value - O(logn) average
    bool search(const T& value) const {
        return searchHelper(root, value);
    }

    // Delete value - O(logn) avg
    void remove(const T& value) {
        root = removeHelper(root, value);
        size--;
    }

    // Find minimum value
    T findMin() const {
        if (root == nullptr) {
            throw std::runtime_error("Tree is empty");
        }
        TreeNode<T>* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->data;
    }

    // Find Maximum value
    T findMax() const {
        if (root == nullptr) {
            throw std::runtime_error("Tree is empty");
        }
        TreeNode<T>* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }

    // Get size
    size_t getSize() const {
        return size;
    }

    // Check if empty
    bool empty() const {
        return root == nullptr;
    }

    // clear all nodes
    void clear() {
        clearHelper(root);
        root = nullptr;
        size = 0;
    }

    void printTree() const {
        std::cout << "Tree structure (rotated 90° - root on left):\n";
        printHelper(root, 0);
    }

    // Inorder traversal (prints in sorted order!)
    void printInorder() const {
        std::cout << "Inorder (sorted): ";
        inorderHelper(root);
        std::cout << "\n";
    }
    
    // Preorder traversal
    void printPreorder() const {
        std::cout << "Preorder: ";
        preorderHelper(root);
        std::cout << "\n";
    }
    
    // Postorder traversal
    void printPostorder() const {
        std::cout << "Postorder: ";
        postorderHelper(root);
        std::cout << "\n";
    }

    // NOT FINISHED

};