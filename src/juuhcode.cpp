#include "juuhcode.hpp"

// initialize with the given string
JuuhCode::JuuhCode(std::string s) : stringToEncode(s) {
  calculateFrequencies();
  createTree();
  generateHuffmanCode(root, "");
}

// calculate character (byte) frequencies
void JuuhCode::calculateFrequencies() {
  for (auto it = stringToEncode.begin(); it != stringToEncode.end(); ++it) {
    ++(frequencies[(uint8_t)*it]);
  }
}

// create the initial leaves and internal leaves
void JuuhCode::createTree() {
  const auto comparison = [](const Node *first, const Node *second) {
    return first->frequency > second->frequency;
  };

  std::priority_queue<Node *, std::vector<Node *>, decltype(comparison)> tree(
      comparison);

  // loop through "characters" and push them into the queue
  for (uint8_t i = 0; i < UINT8_MAX; ++i) {
    const auto frequency = frequencies[i];

    if (frequency == 0) {
      continue;
    }

    auto node = new Node(frequency, i);
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

  root = tree.top();
}

// recursively generate huffman coding
void JuuhCode::generateHuffmanCode(Node *node, std::string code) {
  // assign a code
  if (!node->left && !node->right) {
    codes[node->character] = code;
    return;
  }

  generateHuffmanCode(node->left, code + "0");
  generateHuffmanCode(node->right, code + "1");
}

// print the coding
void JuuhCode::print() const {
  for (const auto &pair : codes) {
    auto character = pair.first;
    auto code = pair.second;
    std::cout << "'" << character << "': " << code << std::endl;
  }
}
