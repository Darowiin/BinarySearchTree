#include <iostream>

#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() : root(nullptr) {}
BinarySearchTree::Node* BinarySearchTree::copyTree(const Node* otherNode) {
    if (!otherNode) {
        return nullptr;
    }
    Node* newNode = new Node(otherNode->data);
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

        std::cout << root->data << std::endl;

        printRecursive(root->left, prefix + (isLeft ? "|   " : "    "), true);
        printRecursive(root->right, prefix + (isLeft ? "|   " : "    "), false);
    }
}
void BinarySearchTree::print() const {
    std::cout << "Tree: " << std::endl;
    printRecursive(root);
}
bool BinarySearchTree::insert(int key) {
    if (!root) {
        root = new Node(key);
        return true;
    }
    
    Node* tmp = root;
    while (tmp && tmp->data != key) {
        if (tmp->data > key) {
            if (tmp->left)
                tmp = tmp->left;
            else {
                tmp->left = new Node(key);
                return true;
            }
        }
        else if (tmp->data < key) {
            if (tmp->right)
                tmp = tmp->right;
            else {
                tmp->right = new Node(key);
                return true;
            }
        }
        else
            return false;
    }
}
bool BinarySearchTree::containsRecursive(Node* node, const int key) const {
    if (node) {
        if (node->data == key) return true;
        else if (node->data < key) return containsRecursive(node->right, key);
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
    if (key < node->data) {
        eraseRecursive(node->left, key);
    }
    else if (key > node->data) {
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
            node->data = findMin(node->right)->data;
            eraseRecursive(node->right, node->data);
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
    if (node == nullptr || node->data == key)
        return root;

    if (node->data < key)
        return searchRecursive(node->right, key);

    return searchRecursive(node->left, key);
}
bool BinarySearchTree::search(int key) {
    if (searchRecursive(root, key)) return true;
    return false;
}