#include <memory>

class Widget
{
private:
    struct Impl;
    std::unique_ptr<Impl> p;    
    
public:
    Widget(/* args */);
    ~Widget();
};


