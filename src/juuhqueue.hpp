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
  Node *top() const;
  size_t size() const;

private:
  // at maximum there will be 256 nodes in the queue
  std::array<Node *, UINT8_MAX> queue = {{0}};
  size_t queueSize = 0;
};
