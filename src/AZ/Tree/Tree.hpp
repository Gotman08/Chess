#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"

class Tree{
public:
    Node* root;

    Tree(const State& initialState) {
        root = new Node(initialState);
    }

    ~Tree() {
        delete root;
    }

    Node* getRoot() const {
        return root;
    }

    void setRoot(Node* newRoot) {
        if (root) {
            delete root;
        }
        root = newRoot;
    }
};

#endif