#include <iostream>

/// @brief 好多c++的书都建议 operator >> 或 << 使用friend函数， 但在这里建议使用public memeber与全局operator
class Data
{
public:
    inline std::istream &in(std::istream &cin) const
    {
        return cin;
    }

    inline std::ostream &out(std::ostream &cout) const
    {
        return cout;
    }
};

std::istream &operator>>(std::istream &cin, const Data &data)
{
    return data.in(cin);
}

std::ostream &operator<<(std::ostream &cout, const Data &data)
{
    return data.out(cout);
}

int main()
{
}