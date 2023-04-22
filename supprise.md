
```c++
{
    int x = 0;
    typeid(decltype(x)) != typeid(decltype((x))); //只是多一个括号，但确定不是相同的类型
}
{
    auto p = NULL; //请问p是指针，还是整数？
}
{
    auto p = nullptr;//请问p是什么类型？
    anyp = p; //可以把p赋值给任意指针类型吗？
}
{
    f(){}
    auto f2 = f; //f2是指针类型？还是函数类型
    auto & f3 = f; // f3是什么类型？
    // 同一个类型 f 为什么可以直接给它们赋值

    f2();(*f2)();// 那一个正确？ 为什么可以不使用 *
    f3();(*f3)(); //那一个正确？ 
    // 引用与指针是一样的吗？
}
{
    ClassA s(); //声明一个函数，不是定义变量a
    
    ClassA s2{}; //使用默认构造函数，定义变量a
    ClassA s3 ; //同s2
    
    ClassA s4({}); // 使用空的std::initializer_list调用构造函数
    ClassA s5{{}}; //同s4
}
{
    //const 关键字有两层含义，一层是常量，一层是只读
    const int c1= 10;// 常量，且编译时常量
    int x = 10;
    const int &c2 = x;// 只读，因为可以通过x来修改实际的值
    const int f(const int p) const; // const使用在函数参数返回值，函数后面，含义都是 只读
    //const使用在成员函数后面时，c++开了一个后门，有mutable修辞的成员是可以修改的
    //const的含义并不唯一，它可以被分为两个关键字 const 与 readonly(c#就是这么做的，感觉不错)
    //所以c++11增加了关键字constexpr来着重表示编译时的常量，为了兼容之前的，它不能像c#那样明确彻底解决----增加readonly关键字
    //(单从constexpr这个名字上看，怎么也看不出它与const有什么区别)
    //关键字 constexpr还有一个功能，就是对于同一个函数来说，它的返回值可能是编译时常量，也可能不是。这种情况也是由关键字constexpr来处理
    //增加关键字来处理编译时常量，但又不完全。
    //c++就在这样不停止的修补中成长变大，这也使得c++变成很有研究味道的编程语言
    //给予足够的操控能力，同时也是性能高效的编译语言
    consteval int f2(){return 0;} //consteval 要求必须是编译时计算的常量，差不多是更为严格的constexpr
    constinit int d = 10;//指名d是静态初始化的，它不能是局变量，要么是static变量，要么是thread-local变量。变量本身不要求const

}
{
    auto a1 = new int[10];
    auto a2 = new int[10](); //a1与a2的结果相同吗？
    std::unique_ptr<int[]> a3(new int[10]);
    std::unique_ptr<int[]> a4(new int[10]());// a3 与 a4?
}
{
    int data = 10;
    auto&& d1 = data;// d1为 int&类型，不是int&&类型
    auto&& d2 = 10;// d1为 int&&类型
}


```
