#include "juuhcode.hpp"
#include "juuhqueue.hpp"

// initialize with the given string
JuuhCode::JuuhCode(const std::string &s) : stringToEncode(s) {
  std::cout << "Calculating frequencies..." << std::endl;
  calculateFrequencies();
  std::cout << "Creating a tree..." << std::endl;
  createTree();
  std::cout << "Generating Huffman code..." << std::endl;
  generateHuffmanCode(root, "");
  std::cout << "Generating the encoded string..." << std::endl;
  generateEncodedString();
  std::cout << std::endl;
}

// calculate character (byte) frequencies
void JuuhCode::calculateFrequencies() {
  for (const char &c : stringToEncode) {
    ++(frequencies[static_cast<uint8_t>(c)]);
  }
}

// create the initial leaves and internal leaves
void JuuhCode::createTree() {
  JuuhQueue tree;

  // loop through bytes ("characters") and push them into the queue
  uint8_t i = 0;

  do {
    const auto frequency = frequencies[i];

    if (frequency == 0) {
      continue;
    }

    Node *node = new Node(frequency, i);
    tree.push(node);
  } while (i++ != UINT8_MAX);

  // create internal nodes
  while (tree.size() > 1) {
    Node *rightChild = tree.pop();
    Node *leftChild = tree.pop();

    Node *parent = new Node(leftChild, rightChild);
    tree.push(parent);
  }

  root = tree.top();
}

// recursively generate huffman coding
void JuuhCode::generateHuffmanCode(const Node *node, const std::string &code) {
  // assign a code
  if (!node->left && !node->right) {
    size_t index = static_cast<size_t>(node->character);
    codes[index] = code;
    return;
  }

  generateHuffmanCode(node->left, code + "0");
  generateHuffmanCode(node->right, code + "1");
}

// print the codes
void JuuhCode::printCodes() const {
  for (size_t i = 0; i < codes.max_size(); ++i) {
    char character = static_cast<char>(i);
    std::string code = codes[i];

    if (code == "") {
      continue;
    }

    std::cout << "'" << character << "': " << code << std::endl;
  }
}

void JuuhCode::generateEncodedString() {
  std::string encoded = "";

  for (const char &c : stringToEncode) {
    uint8_t i = static_cast<uint8_t>(c);
    encoded.append(codes[i]);
  }

  encodedString = encoded;
}

// print the encoded string
void JuuhCode::printEncodedString() const {
  std::cout << encodedString << std::endl;
}

void JuuhCode::printStats() const {
  const size_t originalBytes = stringToEncode.length();
  const size_t encodedBytes = encodedString.length() / 8;

  const double percentage =
      (static_cast<double>(encodedBytes) / static_cast<double>(originalBytes)) *
      100;

  std::cout << "Original size:\t" << originalBytes << " bytes"
            << "\n"
            << "Encoded size:\t" << encodedBytes << " bytes (" << percentage
            << "% of original)" << std::endl;
}
