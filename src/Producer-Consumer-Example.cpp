#include <MPMCMQ/Producer-Consumer-Example.h>

#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

namespace TrendPlus {
class ConcurrentLogger {
 public:
  static auto& instance() {
    static ConcurrentLogger instance;
    return instance;
  }
  template <typename T>
  ConcurrentLogger& operator<<(T const& type) {
    {
      std::lock_guard<std::mutex> lock(_mutex);
      std::cout << type;
    }
    return *this;
  }

 private:
  ConcurrentLogger() = default;
  std::mutex _mutex;
};

namespace Example {
void produce(TrendPlus::GenericQueue<int>& q) {
  for (int i = 0; i < 10000; ++i) {
    std::stringstream s;
    s << "Pushing " << i << "\n";
    ConcurrentLogger::instance() << s.str();
    q.push(i);
  }
}

void consume(TrendPlus::GenericQueue<int>& q, unsigned int id) {
  for (int i = 0; i < 2500; ++i) {
    auto item = q.pop();
    std::stringstream s;
    s << "Consumer " << id << " popped " << item << "\n";
    ConcurrentLogger::instance() << s.str();
  }
}

}  // namespace Example
}  // namespace TrendPlus
