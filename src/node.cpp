#include "node.hpp"

Node::Node(uint64_t frequency, uint8_t character) {
  this->character = character;
  this->frequency = frequency;
}

Node::Node(Node *left, Node *right) {
  this->frequency = left->frequency + right->frequency;
  this->left = left;
  this->right = right;
}
