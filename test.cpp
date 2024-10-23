#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr(new int(5)); 
    int *ptr1 = ptr.get();
    std::cout << "Value: " << *ptr << ", Address: " << ptr.get() << std::endl;
    std::cout << "Value: " << *ptr1 << ", Address: " << ptr1 << std::endl;
}