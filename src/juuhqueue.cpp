#include "juuhqueue.hpp"

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

// return the last node (the node with the smallest frequency) from the queue
Node *JuuhQueue::pop() {
  size_t lastIndex = queueSize;
  Node *last = queue[lastIndex];
  queue[lastIndex] = 0;
  queueSize--;
  return last;
}

size_t JuuhQueue::size() const { return queueSize; }

Node *JuuhQueue::top() const { return queue[firstIndex]; }

