[中文](./codestyle_cplus-cn.md)

# Code Style -- cplus 0.1

## 名词
左值Lvalue, 可以取地址的值，可以出现在=号的左边（当然它也可以出现在右边）
右值Rvalue， 不可取地址的值或一个临时值，不可以出现在=号的左边。如一整数常量 5,它是右值； 又如函数返回值等



## 规则
[参见](https://github.com/peacess/code_styles/blob/master/development_roles-cn.md)

```c++
int32_t fun_name(){
   //定义数据
   int32_t data = 0;
   //生成数据
   {}
   //使用数据
   return data;
}
```

## Name

[遵守C++的命名](https://en.cppreference.com/w/cpp/named_req)  
常用单词[Words](https://github.com/peacess/code_styles/blob/master/words_cn_en.md)   

1. 所有源代码文件名，使用小写，加下划线
2. 命名使用有明确函义的英文单词
3. 使用一至的单词顺命名。  
    一般是动词-名词-错误。这里有一种特殊的情况是，是某一分类下内容，可以在动词前面增加一个分类的前缀如 Eth---，或Btc---等

## 目录文件

1. 单元测试？
2. 所有的demo放入“ 仓库名/demo ” 目录中
3. 如果是框架或基础库，需要“仓库名/sample”

## 代码

1. 使用确定大小的类型，如int32_t而不少使用int类型，int只使用在局部，如循环变量等，像成员变量、或交互，或持久等都使用确定大小类型
2. 函数入参优先使用const &， 如果想要修改值才使用&，如果有移动含义时才使用&&
3. 不要重载引用与右值引用，如果要这样做要给出特别的理由。因为当这样重载时，不容易确认是调用的那个函数

```c++
void f(int32_t& data);
void f(int32_t&& data);

int32_t&& value = 5;
foo(value); //这里调用那个函数？

```

### 重载/继承
1. 在重载bool与int时，在同一参数位置上，不要只bool与int的重载。  
原因，bool类型比较特别，在c99之前是没有bool类型，VC中BOOL实际是int类型，所以在使用不同版本的编译器会产生不同的结果。  
下面是错误代码：
```c++
void f(int);
void f(bool);
f(bool) //这个代码希望调用f(int)，而如果是不支持bool类型与支持的编译器，最后编译的结果会不一样。

```
2. 不要让自动类型转换发生，自动类型转换容易发生不遇见的结果  
    *. explicit 单构造函数(注意，当有默认值时，如果可以传单参，也是单构造函数)，加了explicit后显示转换是可以的（包含，static_cast, (T)v -- 旧的强制类型转换）
    *. operator T() 函数
3. 不要重载 &&，||，“,”这些运算符，因为它们都是有先后顺序的，一但变成函数调用，就无法确定先后顺序。  
4. C& C::operator=(const C&);这是operator=的规范用法（返回const，也是可以）   
5. 在base class中的static member，在不同的derived class中只有一份  
    如果想在不同derived class中有不同的 static member，需要使用template，因为范型会做代码展开，所以只每一个derived class都有一份展开，就可以。代码如下。
```c++
#include <cstdio>
#include <cstdlib>

template <typename T>
class Base
{
public: 
    static int staticVar;
    virtual ~Base(){} // base class must be virtual destructor
};

template <typename T> int Base<T>::staticVar(1);

class DerivedA : public Base<DerivedA> {};
class DerivedB : public Base<DerivedB> {};

int main() {
    
    DerivedA::staticVar  =2;
    DerivedB::staticVar = 3;
    Base<DerivedA>::staticVar = 4;

    printf("a : %d, b: %d , base: %d \n", DerivedA::staticVar, DerivedB::staticVar, Base<DerivedA>::staticVar);
    return 0;
}
// a : 4, b: 3 , base: 4 
// Base<DerivedA>::staticVar 与 DerivedA::staticVar 代码展开，只有一次，所以它的是同一个变量
```    
6. 通过base class来释放内存，而base class的destructor不是virtual时，只会调用base class的destructor函数  
    所以如果base 类型的destructor必须定义为 virtual。
    反过来就是，在derived class中需确保 base class中的destructor中virtual的。
7. 建议不要在 static与inline 函数中使用 "static"的变量，因为这时函数中的static变量的含义可能会冲突。  
如： inline函数在所有调用的地方会展开，那么这时static a 变量是每一个调用都是一个独立的a，这个与习惯理解冲突。  但是如果编译器认为这个inline 函数不被内联，那么它又是共享的，与习惯理解一样。有这种不确定性，所以不要在inline中直接使用static变量。可以使用static成员变量等方式来代替。
如： static只在当前文件可见，那么可以在不同文件中定义同名的static 函数，这时在不同static函数中的static a变量，不是共享的，但很容易让人识误以为是共享的。
终上，为了减少理解的偏差或奇义。
8. 建议减少使用非类的static 函数。 对于看代码，容易误解

### 指针
1. 各种new与delete的配置对
    1. new delete -- 分配内存后调用构造， 调用析构函数后释放内存
    2. new [] delete [] -- 与1一样，只是数组
    3. operator new/delete, 只分配内存（相当于 malloc与free）
    4. operator new[]/delete[], 分配数组
    5. placement new， 在使用它时，一定要注意，内存是否需要调用析构函
    

### 多线程

### 代码提交前准备

### tepmlate
1. 类型参数据使用typename,不要使用class，除非只能使用class才能编译的情况。  


### 测试


## 文档


## 库使用说明

### 

## 参考
[cppreference](https://en.cppreference.com/w/)

