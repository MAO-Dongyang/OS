#include "MutexQueue.h"
#include <iostream>

MutexQueue::MutexQueue()
{
    head = new QueueNode(-1);
    tail = head;
    readcount = 0;
}

MutexQueue::~MutexQueue() {}

bool MutexQueue::enqueue(int val)
{
    QueueNode* add_node = new QueueNode(val);
    std::unique_lock<std::mutex> lck(wrt);

    while (queue_size == max_size) {
        printf("Slot Full!\n");
        not_full.wait(lck);
    }
    tail->next          = add_node;
    tail                = add_node;
    queue_size++;
    not_empty.notify_all();
    lck.unlock();
    return 1;
}

int MutexQueue::dequeue()
{
    int val;
    std::unique_lock<std::mutex> lck(wrt);
    
    while (queue_size == 0) {
        //printf("Slot empty!\n");
        not_empty.wait(lck); 
    }
    queue_size--;
    val = head->next->val;
    head = head->next;
    not_full.notify_all();
    lck.unlock();
    return val;
}

QueueNode* MutexQueue::search(int val)
{
    std::unique_lock<std::mutex> readLock(mtx);
    ++readcount;
    if (readcount == 1) {
        wrt.lock();
    }
    readLock.unlock();

    QueueNode* p;
    p = head;
    for (int i = 0; i < queue_size; i++) {
        if (p->val == val) {
            break;
        } else {
            p = p->next;
        }
    }

    readLock.lock();
    --readcount;
    if (readcount == 0) {
        wrt.unlock();
    }
    readLock.unlock();

    return p;
}

int MutexQueue::show()
{
    std::unique_lock<std::mutex> readLock(mtx);
    ++readcount;
    if (readcount == 1) {
        wrt.lock();
    }
    readLock.unlock();

    QueueNode* p;
    p = head;
    std::cout << "| |-->";
    for (int i = 0; i < queue_size; i++) {
        if (p->val > 0) {
            std::cout << p->val << "-->";
        }
	p = p->next;
    }
    std::cout << "NULL\n";

    readLock.lock();
    --readcount;
    if (readcount == 0) {
        wrt.unlock();
    }
    readLock.unlock();
    return 0;
}
