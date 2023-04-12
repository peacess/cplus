#include "class_.h"
// #include "class_.cpp"

//template代码，把定义与实现分开时，有两种方式
// 在使用的地方包含实现文件
// 或者在 实现文件中把以“template class MyClass<int>;”template实例化
int main(){
    MyClass<int> t;
    t.print();
}
