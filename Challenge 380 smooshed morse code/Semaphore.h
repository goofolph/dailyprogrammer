#pragma once

#include <condition_variable>
#include <mutex>

class Semaphore {
 public:
  Semaphore(int count = 0);
  void notify(int tid);
  void wait(int tid);

 private:
  std::mutex mtx;
  std::condition_variable cv;
  int count;
};
