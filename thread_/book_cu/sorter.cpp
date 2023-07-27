
#include <algorithm>
#include <atomic>
#include <future>
#include <list>
#include <memory>
#include <thread>
#include <vector>

#include "kits/concurrent_stack.hpp"

template <typename T>
class Sorter {
 public:
  Sorter() : max_thread_count(std::thread::hardware_concurrency() - 1) {}

  ~Sorter() {
    end_of_data = true;
    for (auto& x : threads) {
      if (x.joinable()) {
        x.join();
      }
    }
  }

  std::list<T> do_sort(std::list<T>& v) {
    if (v.empty()) {
      return {};
    }
    std::list<T> res;
    res.splice(res.begin(), v, v.begin());
    auto it = std::partition(v.begin(), v.end(),
                             [&](const T& x) { return x < res.front(); });
    ChunkToSort low;
    low.data.splice(low.data.end(), v, v.begin(), it);
    std::future<std::list<T>> l = low.promise.get_future();
    chunks.push(std::move(low));
    if (threads.size() < max_thread_count) {
      threads.emplace_back(&Sorter<T>::sort_thread, this);
    }
    auto r{do_sort(v)};
    res.splice(res.end(), r);
    while (l.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
      try_sort_chunk();
    }
    res.splice(res.begin(), l.get());
    return res;
  }

 private:
  struct ChunkToSort {
    std::list<T> data;
    std::promise<std::list<T>> promise;
  };

 private:
  void sort_chunk(const std::shared_ptr<ChunkToSort>& chunk) {
    if(nullptr == chunk) {

    }else{
      chunk->promise.set_value(do_sort(chunk->data));
    }
  }

  void try_sort_chunk() {
    std::shared_ptr<ChunkToSort> chunk = chunks.pop();
    if (chunk) {
      sort_chunk(chunk);
    }
  }

  void sort_thread() {
    while (!end_of_data) {
      try_sort_chunk();
      std::this_thread::yield();
    }
  }

 private:
  ConcurrentStack<ChunkToSort> chunks;
  std::vector<std::thread> threads;
  const std::size_t max_thread_count;
  std::atomic<bool> end_of_data = false;
};

template <typename T>
std::list<T> parallel_quick_sort(std::list<T> v) {
  if (v.empty()) {
    return {};
  }
  return Sorter<T>{}.do_sort(v);
}

int main(){

  std::list<int> data = {5,1,2,9,100,8};

  auto sorted_data = parallel_quick_sort(data);

  for(auto it: sorted_data ){
    printf("%d\n", it);
  }
}