#ifndef concretesyntaxtree_H
#define concretesyntaxtree_H

#include <iostream>
#include <vector>
#include <string>

// Class to represent a node in the syntax tree
class SyntaxTreeNode {
public:
    // Data stored in the node (e.g., a symbol, value, or token)
    std::string value;

    // List of children nodes
    std::vector<SyntaxTreeNode*> children;

    // Constructor to initialize the node with a value
    SyntaxTreeNode(const std::string& value) : value(value) {}

    // Method to add a child node
    void addChild(SyntaxTreeNode* child) {
        children.push_back(child);
    }

    // Destructor to delete all child nodes recursively
    ~SyntaxTreeNode() {
        for (SyntaxTreeNode* child : children) {
            delete child;
        }
    }
};

// Class to represent the entire syntax tree
class SyntaxTree {
private:
    SyntaxTreeNode* root;

public:
    // Constructor to initialize the tree with a root node
    SyntaxTree(const std::string& rootValue) {
        root = new SyntaxTreeNode(rootValue);
    }

    // Get the root of the tree
    SyntaxTreeNode* getRoot() {
        return root;
    }

    // Destructor to clean up memory
    ~SyntaxTree() {
        delete root;
    }

    // Method to print the tree (pre-order traversal)
    void printTree(SyntaxTreeNode* node, int depth = 0) const {
        if (node == nullptr) return;

        // Print the current node with indentation
        std::cout << std::string(depth * 2, ' ') << node->value << "\n";

        // Recursively print each child
        for (SyntaxTreeNode* child : node->children) {
            printTree(child, depth + 1);
        }
    }

    // Convenience method to print the entire tree starting from the root
    void print() const {
        printTree(root);
    }
};

#endif //concretesyntaxtree_H