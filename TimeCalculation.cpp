#include "BinarySearchTree.cpp"
#include <chrono>
#include <vector>
#include <algorithm>
#define SIZE 1000

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}
template<typename Function>
double measureTime(Function func) {
    auto start = std::chrono::steady_clock::now();
    func();
    auto end = std::chrono::steady_clock::now();
    auto duration = end - start;
    return std::chrono::duration <double, std::milli>(duration).count();
}
int main() {
    //bst
    double averageFillTime = 0;
    for (int attempt = 0; attempt < 100; ++attempt) {
		BinarySearchTree bst;
        auto fillOperation = [&]() {
            for (int i = 0; i < SIZE; ++i) {
                bst.insert(lcg());
            }
            };
        averageFillTime += measureTime(fillOperation);
	}
    averageFillTime /= 100;
	std::cout << "Average fill time (bst): " << std::fixed << std::setprecision(3) << averageFillTime << " ms" << std::endl;
    double averageSearchTime = 0;
    for (int attempt = 0; attempt < 1000; ++attempt) {
        BinarySearchTree bst;
        for (int i = 0; i < SIZE; ++i) {
            bst.insert(lcg());
        }
        auto searchOperation = [&]() {
            int target = lcg();
            bst.search(target);
            };
        averageSearchTime += measureTime(searchOperation);
    }
    averageSearchTime /= 1000;
    std::cout << "Average search time (bst): " << std::fixed << std::setprecision(3) << averageSearchTime << " ms" << std::endl;
    double averageAddRemoveTime = 0;
    for (int attempt = 0; attempt < 1000; ++attempt) {
        BinarySearchTree bst;
        for (int i = 0; i < SIZE; ++i) {
            bst.insert(lcg());
        }
        auto addRemoveOperation = [&]() {
            int target = lcg();
            bst.insert(target);
            bst.erase(target);
            };
        averageAddRemoveTime += measureTime(addRemoveOperation);
    }
    averageAddRemoveTime /= 1000;
    std::cout << "Average insert&remove time (bst): " << std::fixed << std::setprecision(3) << averageAddRemoveTime << " ms" << std::endl;
    //vector
    std::vector<int> stdVector(SIZE);
    std::generate(stdVector.begin(), stdVector.end(), [&]() { return lcg(); });

    double vectorFillTime = measureTime([&]() {
        std::vector<int> stdVectorCopy(stdVector);
        });
    std::cout << "Vector fill time: " << std::fixed << std::setprecision(3) << vectorFillTime << " ms" << std::endl;
    double vectorSearchTime = measureTime([&]() {
        int target = lcg();
        std::find(stdVector.begin(), stdVector.end(), target);
        });
    std::cout << "Vector search time: " << std::fixed << std::setprecision(3) << vectorSearchTime << " ms" << std::endl;
    double vectorAddRemoveTime = measureTime([&]() {
        int target = lcg();
        stdVector.push_back(target);
        std::vector<int>::iterator it = std::find(stdVector.begin(), stdVector.end(), target);
        if (it != stdVector.end()) stdVector.erase(it);
        });
    std::cout << "Vector add/remove time: " << std::fixed << std::setprecision(3) << vectorAddRemoveTime << " ms" << std::endl;
}