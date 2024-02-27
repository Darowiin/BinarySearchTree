#pragma once
#include <iomanip>

class BinarySearchTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(const int k) : data(k), left(nullptr), right(nullptr) {}
    };

    Node* root;
    Node* copyTree(const Node* otherNode);
    Node* findMin(Node* node) const;
    Node* searchRecursive(Node* node, int key);
    void eraseRecursive(Node*& node, const int key);
    void destroyRecursive(Node* node);
    void printRecursive(Node* node, const std::string& prefix = "", bool isLeft = true) const;
    bool containsRecursive(Node* node, const int key) const;
    int countRecursive(Node* node);

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
    ~BinarySearchTree();
    BinarySearchTree& operator=(const BinarySearchTree& other);
    
    void print() const;
    bool insert(int key);
    bool contains(int key) const;
    bool erase(int key);
    int count();
    bool search(int key);
};