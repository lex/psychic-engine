#include "juuhcode.hpp"

// initialize with the given string
JuuhCode::JuuhCode(std::string s) {
  this->s = s;
  CalculateFrequencies();
  CreateTree();
  GenerateHuffmanCode(this->root, "");
}

// calculate character (byte) frequencies
void JuuhCode::CalculateFrequencies() {
  for (auto it = this->s.begin(); it < this->s.end(); ++it) {
    ++(this->frequencies[(uint8_t)*it]);
  }
}

// create the initial leaves and internal leaves
void JuuhCode::CreateTree() {
  const auto comparison = [](const Node *first, const Node *second) {
    return first->frequency > second->frequency;
  };

  std::priority_queue<Node *, std::vector<Node *>, decltype(comparison)> tree(
      comparison);

  for (auto it = this->frequencies.begin(); it != this->frequencies.end();
       ++it) {
    auto character = it->first;
    auto frequency = it->second;

    if (frequency == 0) {
      continue;
    }

    auto node = new Node(frequency, character);
    tree.push(node);
  }

  // create internal nodes
  while (tree.size() > 1) {
    auto rightChild = tree.top();
    tree.pop();

    auto leftChild = tree.top();
    tree.pop();

    auto parent = new Node(leftChild, rightChild);
    tree.push(parent);
  }

  this->root = tree.top();
}

// recursively generate huffman coding
void JuuhCode::GenerateHuffmanCode(Node *node, std::string code) {
  if (!node->left && !node->right) {
    this->codes[node->character] = code;
    return;
  }

  GenerateHuffmanCode(node->left, code + "0");
  GenerateHuffmanCode(node->right, code + "1");
}

// print the coding
void JuuhCode::Print() {
  for (auto it = this->codes.begin(); it != this->codes.end(); ++it) {
    auto character = it->first;
    auto code = it->second;
    std::cout << "'" << character << "': " << code << std::endl;
  }
}
