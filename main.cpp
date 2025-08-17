#include <iostream>
#include "vector.hpp"

// ---------------- SEGMENTION FAULT (MEY BE IN DESTRUCTORS) ----------------

int main() {
    // Default constructor
    Vector<int> v1;
    std::cout << "v1.size = " << v1.size() << ", capacity = " << v1.capacity() << "\n";

    // Fill constructor
    Vector<int> v2(5, 42);
    std::cout << "v2: ";
    for (size_t i = 0; i < v2.size(); ++i) std::cout << v2[i] << " ";
    std::cout << "\n";

    // Initializer list constructor
    Vector<int> v3{1, 2, 3, 4, 5};
    std::cout << "v3: ";
    for (size_t i = 0; i < v3.size(); ++i) std::cout << v3[i] << " ";
    std::cout << "\n";

    // Copy constructor
    Vector<int> v4(v3);
    std::cout << "v4 (copy of v3): ";
    for (size_t i = 0; i < v4.size(); ++i) std::cout << v4[i] << " ";
    std::cout << "\n";

    // Move constructor
    Vector<int> v5(std::move(v4));
    std::cout << "v5 (moved from v4): ";
    for (size_t i = 0; i < v5.size(); ++i) std::cout << v5[i] << " ";
    std::cout << "\n";

    // Copy assignment
    v1 = v2;
    std::cout << "v1 (assigned from v2): ";
    for (size_t i = 0; i < v1.size(); ++i) std::cout << v1[i] << " ";
    std::cout << "\n";

    // Move assignment
    v4 = std::move(v1);
    std::cout << "v4 (move assigned from v1): ";
    for (size_t i = 0; i < v4.size(); ++i) std::cout << v4[i] << " ";
    std::cout << "\n";

    // Initializer list assignment
    v1 = {9, 8, 7};
    std::cout << "v1 (list assigned): ";
    for (size_t i = 0; i < v1.size(); ++i) std::cout << v1[i] << " ";
    std::cout << "\n";

    // Element access
    std::cout << "v3.at(2) = " << v3.at(2) << "\n";
    v3[2] = 99;
    std::cout << "v3[2] modified = " << v3[2] << "\n";
    std::cout << "front = " << v3.front() << ", back = " << v3.back() << "\n";

    // Capacity functions
    std::cout << "v3.size = " << v3.size() << ", capacity = " << v3.capacity() << "\n";
    v3.reserve(20);
    std::cout << "v3 capacity after reserve(20) = " << v3.capacity() << "\n";

    // Modifiers
    v3.push_back(123);
    v3.push_back(456);
    std::cout << "v3 after push_back: ";
    for (size_t i = 0; i < v3.size(); ++i) std::cout << v3[i] << " ";
    std::cout << "\n";

    v3.emplace_back(777);
    std::cout << "v3 after emplace_back(777): ";
    for (size_t i = 0; i < v3.size(); ++i) std::cout << v3[i] << " ";
    std::cout << "\n";

    v3.insert(2, 111);
    std::cout << "v3 after insert at pos 2: ";
    for (size_t i = 0; i < v3.size(); ++i) std::cout << v3[i] << " ";
    std::cout << "\n";

    v3.insert(1, 3, 222);
    std::cout << "v3 after insert 3 times 222 at pos 1: ";
    for (size_t i = 0; i < v3.size(); ++i) std::cout << v3[i] << " ";
    std::cout << "\n";

    v3.erase(1);
    std::cout << "v3 after erase pos 1: ";
    for (size_t i = 0; i < v3.size(); ++i) std::cout << v3[i] << " ";
    std::cout << "\n";

    v3.erase(1, 3);
    std::cout << "v3 after erase from pos 1 to 3: ";
    for (size_t i = 0; i < v3.size(); ++i) std::cout << v3[i] << " ";
    std::cout << "\n";

    v3.pop_back();
    std::cout << "v3 after pop_back: ";
    for (size_t i = 0; i < v3.size(); ++i) std::cout << v3[i] << " ";
    std::cout << "\n";

    v3.resize(10, 999);
    std::cout << "v3 after resize(10, 999): ";
    for (size_t i = 0; i < v3.size(); ++i) std::cout << v3[i] << " ";
    std::cout << "\n";

    v3.clear();
    std::cout << "v3 after clear, size = " << v3.size() << ", empty = " << v3.empty() << "\n";

    // Swap
    v1 = {1, 2, 3};
    v2 = {4, 5};
    v1.swap(v2);
    std::cout << "After swap, v1: ";
    for (size_t i = 0; i < v1.size(); ++i) std::cout << v1[i] << " ";
    std::cout << "\n";
    std::cout << "After swap, v2: ";
    for (size_t i = 0; i < v2.size(); ++i) std::cout << v2[i] << " ";
    std::cout << "\n";

    return 0;
}
