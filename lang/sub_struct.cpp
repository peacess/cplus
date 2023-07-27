
#include <cstdio>

struct DataSub
{
    int d;
};

struct Data
{
    struct DataSub;
    // int other;
};


int main(){

    auto d = Data{};
    // d.other = 0;
    printf("%d",sizeof(Data));
}