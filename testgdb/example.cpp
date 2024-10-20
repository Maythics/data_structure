#include <iostream>
#include <string>

class Animal { // 基类
public:
    void speak() {
        std::cout << "Animal speaks!" << std::endl;
    }
};

class Dog : public Animal { // 派生类
public:
    void bark() {
	
        std::cout << "Dog barks!" << std::endl;
    }
};

int main() {
    Dog myDog;
    myDog.speak(); // 通过继承访问基类的成员
    myDog.bark();  // 访问派生类自己的成员
    return 0;
}

