#include <iostream>

int main() {
    std::cout << "Hello World!" << std::endl;
    
    int a=10;
    int* ptr =&a;
    std::cout << ptr << std::endl ;
    return 0;
}
