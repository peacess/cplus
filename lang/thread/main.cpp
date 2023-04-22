#include <cstdio>
#include <thread>
#include <future>
// #include <literals

using namespace std::literals;

void f(){
    std::this_thread::sleep_for(1s);
}

int main(){
    auto fu = std::async(std::launch::deferred, f);
    while (fu.wait_for(100ms) != std::future_status::ready)
    {
        printf("done");
    }
    
}