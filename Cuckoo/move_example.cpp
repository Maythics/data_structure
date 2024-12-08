#include <iostream>
#include <vector>

struct HashEntry {
    int key;
    int value;
};

int main() {
    std::vector<HashEntry> array = {{1, 10}, {2, 20}, {3, 30}};

    std::cout << "Before move: " << array.size() << std::endl;

    // 移动array到old
    std::vector<HashEntry> old = std::move(array);

    std::cout << "After move: " << array.size() << std::endl;
    std::cout << "Old size: " << old.size() << std::endl;

    return 0;
}
