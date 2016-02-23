#include "juuhqueue.hpp"

static size_t parent(size_t i) { return i / 2; }

static size_t leftChild(size_t i) { return 2 * i; }

static size_t rightChild(size_t i) { return 2 * i + 1; }

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

// return the first node (the node with the smallest frequency) from the queue
// also move the last node to the first position so we can heapify the queue eas
Node *JuuhQueue::pop() {
  Node *top = queue[firstIndex];
  size_t lastIndex = queueSize;
  queue[firstIndex] = queue[lastIndex];
  queue[lastIndex] = 0;
  heapify(firstIndex);
  queueSize--;
  return top;
}

void JuuhQueue::heapify(const size_t i) {
  size_t left = leftChild(i);
  size_t right = rightChild(i);
  size_t smallest =
      (left < queueSize && queue[left]->frequency < queue[i]->frequency) ? left
                                                                         : i;

  smallest = (right < queueSize &&
              queue[right]->frequency < queue[smallest]->frequency)
                 ? right
                 : smallest;

  if (smallest != i) {
    swap(i, smallest);
    heapify(smallest);
  }
}

void JuuhQueue::swap(const size_t first, const size_t second) {
  Node *temp = queue[first];
  queue[first] = queue[second];
  queue[second] = temp;
}

size_t JuuhQueue::size() const { return queueSize; }

Node *JuuhQueue::top() const { return queue[firstIndex]; }
