#include <MPMCMQ/GenericQueue.h>
#include <MPMCMQ/Producer-Consumer-Example.h>
#include <MPMCMQ/QueueManager.h>

#include <functional>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  TrendPlus::GenericQueue<int> q;

  using namespace std::placeholders;
  using namespace TrendPlus::Example;
  // producer thread
  std::thread prod1(std::bind(produce, std::ref(q)));

  // consumer threads
  std::thread consumer1(std::bind(&consume, std::ref(q), 1));
  std::thread consumer2(std::bind(&consume, std::ref(q), 2));
  std::thread consumer3(std::bind(&consume, std::ref(q), 3));
  std::thread consumer4(std::bind(&consume, std::ref(q), 4));

  prod1.join();
  consumer1.join();
  consumer2.join();
  consumer3.join();
  consumer4.join();
  return 0;
}
