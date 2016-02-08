#include <cstdint>

class Node {
public:
  uint64_t frequency;
  uint8_t character;

  Node *left = 0;
  Node *right = 0;

  Node(uint64_t frequency, uint8_t character);
  Node(Node *left, Node *right);
};
