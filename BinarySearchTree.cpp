#include <iostream>
#include <iomanip>

class BinarySearchTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* copyTree(const Node* otherNode);
    void destroyRecursive(Node* node);

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
    ~BinarySearchTree();
    BinarySearchTree& operator=(const BinarySearchTree& other);

    void print() const;
    bool insert(int key);
    bool contains(int key) const;
    bool erase(int key);
};

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