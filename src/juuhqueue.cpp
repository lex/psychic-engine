#include "juuhqueue.hpp"

static size_t leftChild(size_t i) { return 2 * i; }

static size_t rightChild(size_t i) { return 2 * i + 1; }

static size_t parent(size_t i) { return i / 2; }

JuuhQueue::JuuhQueue() {}

// push an item to the queue
void JuuhQueue::push(Node *node) {
  size_t i = ++queueSize;

  // keep the shape
  while (i > 1 && queue[parent(i)]->frequency > node->frequency) {
    queue[i] = queue[parent(i)];
    i = parent(i);
  }

  queue[i] = node;
}

// retrieve the top item from the queue
Node *JuuhQueue::pop() {
  Node *top = queue[1];
  Node *last = queue[queueSize];
  queue[1] = last;
  queue[queueSize] = 0;
  queueSize--;
  heapify(1);
  return top;
}

// could be useful, not used for now though
size_t JuuhQueue::getLowestFrequency(size_t i) {
  if (leftChild(i) >= queueSize) {
    return i;
  }

  size_t left = getLowestFrequency(leftChild(i));
  size_t right = getLowestFrequency(rightChild(i));

  return left <= right ? left : right;
}

size_t JuuhQueue::size() { return queueSize; }

Node *JuuhQueue::top() { return queue[1]; }

void JuuhQueue::heapify(size_t i) {
  size_t left = leftChild(i);
  size_t right = rightChild(i);
  size_t largest =
      (left < queueSize && queue[left]->frequency < queue[i]->frequency) ? left
                                                                         : i;

  largest =
      (right < queueSize && queue[right]->frequency < queue[largest]->frequency)
          ? right
          : largest;

  if (largest != i) {
    swap(i, largest);
    heapify(largest);
  }
}

// swap two items
void JuuhQueue::swap(size_t first, size_t second) {
  Node *temp = queue[first];
  queue[first] = queue[second];
  queue[second] = temp;
}
