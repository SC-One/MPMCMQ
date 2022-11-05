#ifndef PRODUCERCONSUMEREXAMPLE_H
#define PRODUCERCONSUMEREXAMPLE_H

#include <MPMCMQ/GenericQueue.h>

namespace TrendPlus {
namespace Example {

void produce(TrendPlus::GenericQueue<int>& q);

void consume(TrendPlus::GenericQueue<int>& q, unsigned int id);

}  // namespace Example
}  // namespace TrendPlus

#endif  // PRODUCERCONSUMEREXAMPLE_H
