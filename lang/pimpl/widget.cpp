#include "widget.h"
#include <string>
#include <vector>
#include <memory>

struct Widget::Impl
{
    std::string name;
    std::vector<double> data;

};


Widget::Widget(/* args */): p(std::make_unique<Impl>())
{
}

Widget::~Widget()
{
}
