#ifndef MUTEXQUEUE_H
#define MUTEXQUEUE_H

#include "QueueNode.h"
#include <mutex>
#include <condition_variable>

class MutexQueue {
  public:
    MutexQueue();
    bool enqueue(int val);
    int  dequeue();
    ~MutexQueue();
    QueueNode* search(int val);
    int show();

  private:
    int        max_size = 100000;
    int        queue_size;
    QueueNode* tail;
    QueueNode* head;
    std::mutex wrt;
    std::mutex mtx;
    int readcount;

    std::condition_variable not_full;
    std::condition_variable not_empty;
};

#endif  // MUTEXQUEUE_H
