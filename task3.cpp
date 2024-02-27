#include <vector>
#include <iostream>

#include "BinarySearchTree.h"

std::vector<int> findDuplicates(const std::vector<int>& inputVector) {
    std::vector<int> result;
    BinarySearchTree bst;

    for (int element : inputVector) {
        bool flag = bst.insert(element);
        if (!flag) {
            result.push_back(element);
        }
    }

    return result;
}

//int main() {
//    std::vector<int> vector{ 1,5,5,2,7,9,11,11 };
//    std::vector<int> duplicates = findDuplicates(vector);
//    std::cout << "default vector: ";
//    for (int i = 0; i < vector.size(); ++i)
//        std::cout << vector[i] << " ";
//    std::cout << std::endl;
//    std::cout << "duplicates vector: ";
//    for (int i = 0; i < duplicates.size(); ++i)
//        std::cout << duplicates[i] << " ";
//}