
#include "class_.h"
#include <iostream>

template <typename T>
MyClass<T>::MyClass(){}

template <typename T>
void MyClass<T>::print() {
    std::cout << _arg << std::endl;
}

template class MyClass<int>;