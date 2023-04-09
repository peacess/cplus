#include <stdio.h>
#include <cstring>
#include <utility>

class derived_class;

class class_8
{
private:
    char *str;

public:
    class_8(/* args */);
    virtual ~class_8();
    class_8(const class_8 &other);
    class_8(class_8 &&other);
    /// @brief  为什使用virtual? 当有derived class时，解决 class_8 v (derived class) = class_8 v;
    /// 也就是derived class在使用base class 赋值时，可以正确调用derived class的 operator=方法
    /// 可以做如下优化， 
    /// 1. 检查是不是自己=自己
    /// 2. 如果方便可以检查是否完全相等
    /// 3. 如果有分配内存时，处理内存分配失败的情况
    virtual class_8 &operator=(const class_8 &other);
    /// @brief  使用virtual原因同上
    virtual class_8 &operator=(class_8 &&other);
    // 下面这两个函数，一般不用手动实现
    // class_8 *operator&();
    // class_8 const *operator&() const;

public:
    void  set_str(const char * data);
};

class derived_class : public class_8
{

public:
    int data = 0;
    derived_class(/* args */);
    virtual ~derived_class();
    derived_class(const derived_class &other);
    derived_class(derived_class &&other);
    virtual derived_class &operator=(const class_8 &other) override;
    virtual derived_class &operator=(class_8 &&other) override;
    // /// @brief 解决 derived_class的子类时，少一次dynamic_static转换，会使用代码变得更复杂，所以不建议这样使用
    // virtual derived_class &operator=(const derived_class &other);
    // virtual derived_class &operator=(derived_class &&other);
};

class_8::class_8(/* args */) : str{nullptr}
{
    printf("class_8 constructor\n");
}
class_8::~class_8()
{
    printf("~class_8\n");
    if (nullptr != str)
    {
        delete str;
        str = nullptr;
    }
}

class_8::class_8(const class_8 &other)
{
    printf("class_8 copy constructor\n");
    if (nullptr != other.str)
    {
        auto l = std::strlen(other.str) + 1;
        str = new char[l];
        str[l - 1] = '\0';
        std::strncpy(str, other.str, l - 1);
    }
    else
    {
        str = nullptr;
    }
}
class_8::class_8(class_8 &&other)
{
    printf("class_8 move constructor\n");
    if (nullptr != other.str)
    {
        auto l = std::strlen(other.str) + 1;
        str = new char[l];
        str[l - 1] = '\0';
        std::strncpy(str, other.str, l - 1);
        other.str = nullptr;
    }
    else
    {
        str = nullptr;
    }
}

// 这个返回值也可以给 const
class_8 &class_8::operator=(const class_8 &other)
{
    printf("class_8 operator=\n");
    if (this != &other)
    {
        // auto tt = const_cast<class_8&>( other);
        // auto tp = dynamic_cast<derived_class*>( &tt);
        // printf("st: %d", tp.data);
        if (nullptr != str)
        {
            delete[] str;
            str = nullptr;
        }
        if (nullptr != other.str)
        {
            auto l = std::strlen(other.str) + 1;
            str = new char[l];
            str[l - 1] = '\0';
            std::strncpy(str, other.str, l - 1);
        }
    }
    return *this;
}

class_8 &class_8::operator=(class_8 &&other)
{
    printf("class_8 move operator=\n");
    if (this != &other)
    {
        if (nullptr != str)
        {
            delete[] str;
            str = nullptr;
        }
        if (nullptr != other.str)
        {
            str = other.str;
            other.str = nullptr;
        }
    }

    return *this;
}

void class_8::set_str(const char *data)
{
    if(str != nullptr){
        delete []str;
        str = nullptr;
    }
    if (nullptr != data)
    {
        auto l = std::strlen(data) + 1;
        str = new char[l];
        str[l - 1] = '\0';
        std::strncpy(str, data, l - 1);
    }
}

// class_8 *class_8::operator&()
// {
//     return this;
// }

// class_8 const *class_8::operator&() const
// {
//     return this;
// }



derived_class::derived_class()
{
    printf("derived_class constructor\n");
}

derived_class::~derived_class()
{
    printf("~derived_class\n");
}

derived_class::derived_class(const derived_class &other) : class_8{other}
{
    printf("derived_class copy destructor\n");
}

/// @brief 一定记得std::move, 不然就调用到 copy constructor了
/// @param other
derived_class::derived_class(derived_class &&other) : class_8{std::move(other)}
{
    printf("derived_class move destructor\n");
}

derived_class &derived_class::operator=(const class_8 &other)
{
    printf("derived_class operator=\n");
    if(this != &other){
        // 调用基类的函数，注意一定转换为引用
        // static_cast<class_8 &>(*this) = other;
        //也可以使用这个方式
        class_8::operator= (other); 
        auto t = dynamic_cast<const derived_class *>(&other);
        if(nullptr != t){
            data = t->data;
        }else{
            //当使用 = class_8真实类型时，只处理基类
        }
    }
    return *this;
}

derived_class &derived_class::operator=(class_8 &&other)
{
    printf("derived_class move operator=\n");
    if(this != &other){
        // 调用基类的函数，注意一定转换为引用
        // static_cast<class_8 &>(*this) = std::move(other);
        //也可以使用这个方式
        class_8::operator= (std::move(other)); //注意基类一定不能把derived_class中的数据move
        auto t = dynamic_cast<const derived_class *>(&other);
        if(nullptr != t){
            data = t->data;
        }
    }
    return *this;

}

// derived_class &derived_class::operator=(const derived_class &other)
// {
//     printf("derived_class move operator=\n");
//     if(this != &other){
//         // 调用基类的函数
//         // static_cast<class_8 &>(*this) = std::move(other);//不可以使用，因为是virtual函数，会形成递归调用
//         class_8::operator= (other);
//         data = other.data;
//     }
//     return *this;
// }

// derived_class &derived_class::operator=(derived_class &&other)
// {
//     printf("derived_class move operator=\n");
//     if(this != &other){
//         // 调用基类的函数
//         // static_cast<class_8 &>(*this) = std::move(other); //不可以使用，因为是virtual函数，会形成递归调用
//         class_8::operator= (std::move(other)); //注意 move，不然会调用到非move的函数上面； 基类一定不能把derived_class中的数据move
//         data = other.data;
//     }
//     return *this;
// }

int main()
{
    class_8 *p8_1 = new derived_class();
    p8_1->set_str("1");
    class_8 *p8_2 = new derived_class();
    p8_2->set_str("2");

    // 这个会调用到derived_class
    // static_cast<class_8 &>(*p8_1) = static_cast<class_8 &>(*p8_2);
    *p8_1 = *p8_2;

    *p8_1 = std::move(*p8_2);
    // static_cast<class_8 &>(*p8_1) = std::move(*p8_2);

    derived_class *pd = new derived_class();
    pd->set_str("3");

    *p8_1 = *pd;


    delete p8_1;
    delete p8_2;
    delete pd;
}
