#pragma once
#include <cstdint>

struct Node {
  const uint64_t frequency;
  uint8_t character;

  const Node *left;
  const Node *right;

  Node(uint64_t f, uint8_t c) : frequency(f), character(c), left(0), right(0) {}
  Node(Node *l, Node *r)
      : frequency(l->frequency + r->frequency), left(l), right(r) {}
};
