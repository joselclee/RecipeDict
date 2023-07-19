#include <iostream>

struct Recipe {
    std::string Name;
    std::string Ingredients;
    std::string Instructions;
};

template <typename T>
class BSTNode {
public:
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;

    // Constructor
    BSTNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
private:
    BSTNode<T>* root;

    // Helper function for inserting a value into the tree
    BSTNode<T>* insertHelper(BSTNode<T>* node, T value) {
        if (node == nullptr) {
            // Create a new node if the current node is null
            return new BSTNode<T>(value);
        }

        if (value.Name < node->data.Name) {
            // Recursively insert into the left subtree
            node->left = insertHelper(node->left, value);
        }
        else if (value.Name > node->data.Name) {
            // Recursively insert into the right subtree
            node->right = insertHelper(node->right, value);
        }

        return node;
    }

    // Helper function for searching a value in the tree
    bool searchHelper(BSTNode<T>* node, const std::string& searchInput) const {
        if (node == nullptr) {
            // The value is not found
            return false;
        }

        std::string recipeName = node->data.Name;

        if (recipeName.find(searchInput) != std::string::npos) {
            // The value is found
            return true;
        }
        else if (searchInput < recipeName) {
            // Recursively search in the left subtree
            return searchHelper(node->left, searchInput);
        }
        else {
            // Recursively search in the right subtree
            return searchHelper(node->right, searchInput);
        }
    }

public:
    // Constructor
    BST() : root(nullptr) {}

    // Insert a value into the tree
    void insert(T value) {
        root = insertHelper(root, value);
    }

    // Search for a value in the tree
    bool search(const std::string& name) const {
        return searchHelper(root, name);
    }

    BSTNode<T>* getRoot() const {
        return root;
    }
};
