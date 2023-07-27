#include <atomic>
#include <iostream>
#include <thread>



int main() {
  std::atomic<int> x(0);
  x.store(1, std::memory_order_acquire);//store本来应该与 release对应的
  x.load(std::memory_order_release);// load 本来应该与acquire对应的
  return 0;
}