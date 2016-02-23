#include "juuhqueue.hpp"

static size_t leftChild(size_t i) { return 2 * i; }

static size_t rightChild(size_t i) { return 2 * i + 1; }

static size_t parent(size_t i) { return i / 2; }

JuuhQueue::JuuhQueue() {}

// push an item to the queue
void JuuhQueue::push(Node *node) {
  size_t i = ++queueSize;

  // keep the shape
  while (i > 1 && queue[parent(i)]->frequency < node->frequency) {
    queue[i] = queue[parent(i)];
    i = parent(i);
  }

  queue[i] = node;
}

// retrieve the top item from the queue
Node *JuuhQueue::pop() {
  Node *last = queue[queueSize];
  queue[queueSize] = 0;
  queueSize--;
  return last;
}

size_t JuuhQueue::size() const { return queueSize; }

Node *JuuhQueue::top() const { return queue[1]; }

