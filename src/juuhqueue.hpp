#pragma once

#include "node.hpp"
#include <cstdint>
#include <algorithm>
#include <array>

class JuuhQueue {
public:
  JuuhQueue();
  void push(Node *node);
  Node *pop();
  Node *top();
  size_t size();

private:
  void heapify(size_t index);
  void swap(size_t first, size_t second);
  size_t getLowestFrequency(size_t index);
  // 1024(???) for now, gotta figure out the real size in runtime
  std::array<Node *, 1024> queue = {{0}};
  size_t queueSize = 0;
};
