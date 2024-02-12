#include "BinarySearchTree.h"
#include <iostream>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}
BinarySearchTree::Node* BinarySearchTree::copyTree(const Node* otherNode) {
    if (!otherNode) {
        return nullptr;
    }
    Node* newNode = new Node(otherNode->key);
    newNode->left = copyTree(otherNode->left);
    newNode->right = copyTree(otherNode->right);
    return newNode;
}
BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) : root(copyTree(other.root)) {}
void BinarySearchTree::destroyRecursive(Node* node) {
    if (node) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}
BinarySearchTree::~BinarySearchTree() {
    destroyRecursive(root);
}
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    BinarySearchTree copy(other);
    if (this != &copy) {
        std::swap(*this, copy);
    }
    return *this;
}
void BinarySearchTree::printRecursive(Node* root, const std::string& prefix, bool isLeft) const {
    if (root) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "\\--");

        std::cout << root->key << std::endl;

        printRecursive(root->left, prefix + (isLeft ? "|   " : "    "), true);
        printRecursive(root->right, prefix + (isLeft ? "|   " : "    "), false);
    }
}
void BinarySearchTree::print() const {
    std::cout << "Tree: " << std::endl;
    printRecursive(root);
}
BinarySearchTree::Node* BinarySearchTree::insertRecursive(Node*& node, const int key) {
    if (!node) {
        return new Node(key);
    }
    if (!contains(key)) {
        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        }
        else if (key > node->key) {
            node->right = insertRecursive(node->right, key);
        }
    }
    return node;
}
bool BinarySearchTree::insert(int key) {
    root = insertRecursive(root, key);
    if (root) return true;
    else return false;
}
bool BinarySearchTree::containsRecursive(Node* node, const int key) const {
    if (node) {
        if (node->key == key) return true;
        else if (node->key < key) return containsRecursive(node->right, key);
        else return containsRecursive(node->left, key);
    }
    else
        return false;
}
bool BinarySearchTree::contains(int key) const {
    return containsRecursive(root, key);
}
void BinarySearchTree::eraseRecursive(Node*& node, const int key) {
    if (!node) {
        return;
    }
    if (key < node->key) {
        eraseRecursive(node->left, key);
    }
    else if (key > node->key) {
        eraseRecursive(node->right, key);
    }
    else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            node = temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            node = temp;
        }
        else {
            node->key = findMin(node->right)->key;
            eraseRecursive(node->right, node->key);
        }
    }
}
BinarySearchTree::Node* BinarySearchTree::findMin(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
bool BinarySearchTree::erase(int key) {
    if (contains(key)) {
        eraseRecursive(root, key);
        return true;
    }
    return false;
}
int BinarySearchTree::countRecursive(Node* node) {
    if (!node)
        return 0;
    return countRecursive(node->right) + countRecursive(node->left) + 1;
}
int BinarySearchTree::count() {
    return countRecursive(root);
}
BinarySearchTree::Node* BinarySearchTree::searchRecursive(Node* node, int key) {
    if (node == nullptr || node->key == key)
        return root;

    if (node->key < key)
        return searchRecursive(node->right, key);

    return searchRecursive(node->left, key);
}
bool BinarySearchTree::search(int key) {
    if (searchRecursive(root, key)) return true;
    return false;
}