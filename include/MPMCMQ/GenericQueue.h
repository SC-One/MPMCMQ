#ifndef GENERICQUEUE_H
#define GENERICQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>

namespace TrendPlus {

// code copied from:
// https://gist.github.com/ictlyh/f8473ad0cb1008c6b32c41f3dea98ef5
// and made some changes

///
/// \brief A generic queue that can be used in any multi threading
/// scenarios(mutex implementation)
///
///
/// T is type of structure that is using by consumers and producers
///
/// BUFFER_SIZE_VALUE is size of items that save in queuee
///
/// Container is type of container that can be changed by custom types(i.e:
/// wrapp other container and re-write using methods in GenerticQueue)
///
template <typename T, std::size_t BUFFER_SIZE_VALUE = 100,
          typename Container = std::queue<T>>
class GenericQueue {
 public:
  T pop() {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty()) {
      cond_.wait(mlock);
    }
    auto val = queue_.front();
    queue_.pop();
    mlock.unlock();
    cond_.notify_one();
    return val;
  }

  void pop(T& item) {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty()) {
      cond_.wait(mlock);
    }
    item = queue_.front();
    queue_.pop();
    mlock.unlock();
    cond_.notify_one();
  }

  void push(const T& item) {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.size() >= BUFFER_SIZE) {
      cond_.wait(mlock);
    }
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }
  GenericQueue() = default;
  GenericQueue(const GenericQueue&) = delete;             // disable copying
  GenericQueue& operator=(const GenericQueue&) = delete;  // disable assignment

 private:
  Container queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
  const static unsigned int BUFFER_SIZE =
      std::integral_constant<decltype(BUFFER_SIZE_VALUE), BUFFER_SIZE_VALUE>();
};
}  // namespace TrendPlus
#endif  // GENERICQUEUE_H
