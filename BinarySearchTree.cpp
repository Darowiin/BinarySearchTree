#include <iostream>
#include <iomanip>
#include <queue>

class BinarySearchTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(const int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* copyTree(const Node* otherNode);
    Node* insertRecursive(Node*& node, const int key);
    Node* findMin(Node* node) const;
    void eraseRecursive(Node*& node, const int key);
    void destroyRecursive(Node* node);
    void printRecursive(Node* root, const std::string& prefix = "", bool isLeft = true) const;
    bool containsRecursive(Node* node, const int key) const;

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

int main() {
    BinarySearchTree bst;
    bst.insert(7);
    bst.insert(8);
    bst.insert(3);
    bst.insert(15);
    bst.insert(15);
    bst.insert(6);
    bst.insert(5);
    bst.insert(13);
    bst.print();
    bst.erase(5);
    BinarySearchTree bst2(bst);
    BinarySearchTree bst3 = bst;
    bst2.print();
    bst3.print();
}