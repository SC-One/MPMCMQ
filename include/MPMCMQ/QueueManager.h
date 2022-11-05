#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H
#include <any>
#include <string>
#include <variant>

// variant better performance than std::any and because
// we know the types on compile time
#include <MPMCMQ/GenericQueue.h>

namespace TrendPlus {
///
/// Q0 has more priority than Q1
///
/// example:
/// QueueManager<std::variant<int, std::string, double>, std::variant<int>> ex;
template <typename Q0T = std::variant<std::monostate>,
          typename Q1T = std::variant<std::monostate>>
class QueueManager final {
 public:
  QueueManager();

  Q0T popQ0() { return _q0.pop(); }
  Q1T popQ1() { return _q1.pop(); }
  //  auto pop() {
  //      // make pop -> std::optinal
  //      // and current size should not be seprated
  //      // because when you ask for size , maybe other threads use
  //    if (_q0.currentSize() > 0)
  //      return _q0.pop();
  //    else
  //      return _q1.pop();
  //  }
  void pushQ0(Q0T const& value) { _q0.push(value); }
  void pushQ1(Q1T const& value) { _q1.push(value); }

 private:
  GenericQueue<Q0T> _q0;
  GenericQueue<Q1T> _q1;
};

using DefaultTypeOfQueue = std::any;
template <>
class QueueManager<DefaultTypeOfQueue, DefaultTypeOfQueue> final {
 public:
  QueueManager();

  DefaultTypeOfQueue pop() {
    auto result = _q0.pop();
    return result;
  }
  void pushQ0(DefaultTypeOfQueue const& value) { _q0.push(value); }
  void pushQ1(DefaultTypeOfQueue const& value) { _q1.push(value); }

 private:
  GenericQueue<DefaultTypeOfQueue> _q0;
  GenericQueue<DefaultTypeOfQueue> _q1;
};
}  // namespace TrendPlus

#endif  // QUEUEMANAGER_H
