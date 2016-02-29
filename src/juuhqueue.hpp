#pragma once

#include "node.hpp"
#include <cstdint>
#include <array>

class JuuhQueue {
public:
  JuuhQueue();
  void push(Node *node);
  Node *pop();
  Node *top() const;
  size_t size() const;

private:
  const size_t firstIndex = 1;
  void heapify(const size_t i);
  void swap(const size_t first, const size_t second);
  void debugPrint() const;

  // at maximum there will be 256 nodes in the queue
  // we start indexing from 1, so we need one (two) more spot
  // UINT8_MAX is 255
  std::array<Node *, UINT8_MAX + 2> queue = {{0}};
  size_t queueSize = 0;
};
