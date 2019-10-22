#include <iostream>

#include "Semaphore.h"

Semaphore::Semaphore(int count) { this->count = count; }

void Semaphore::notify(int tid) {
  std::unique_lock<std::mutex> lock(mtx);
  count++;
  std::cout << "thread " << tid << " notify" << std::endl;
  // notify the waiting thread
  cv.notify_one();
}

void Semaphore::wait(int tid) {
  std::unique_lock<std::mutex> lock(mtx);
  while (count == 0) {
    std::cout << "thread " << tid << " wait" << std::endl;
    // wait on the mutex until notify is called
    cv.wait(lock);
    std::cout << "thread " << tid << " run" << std::endl;
  }
  count--;
}