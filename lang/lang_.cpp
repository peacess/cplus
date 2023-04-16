#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

int main(){

    auto x = {1,2,3};
    int xx = 1;
    auto data2{1};
    cout << typeid(data2).name();
}