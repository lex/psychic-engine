#include "juuhcode.hpp"
#include "juuhqueue.hpp"

// initialize with the given string
JuuhCode::JuuhCode(const std::string &s) : stringToEncode(s) {
  // std::cout << "Calculating frequencies..." << std::endl;
  calculateFrequencies();
  // std::cout << "Creating a tree..." << std::endl;
  createTree();
  // std::cout << "Generating Huffman code..." << std::endl;
  std::vector<bool> v;
  generateHuffmanCode(root, v);
  // std::cout << "Generating the encoded string..." << std::endl;
  generateEncodedString();
  // std::cout << std::endl;

  std::vector<bool> b;
  encode(root, b);
  bits = b;

  // for (const auto &bb : b) {
  //   std::cout << bb;
  // }
  // std::cout << std::endl;

  bitsToBytes();
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
void JuuhCode::generateHuffmanCode(const Node *node,
                                   const std::vector<bool> &code) {
  // assign a code
  if (!node->left && !node->right) {
    size_t index = static_cast<size_t>(node->character);
    codes[index] = code;
    return;
  }

  auto left = code;
  left.push_back(false);

  auto right = code;
  right.push_back(true);

  generateHuffmanCode(node->left, left);
  generateHuffmanCode(node->right, right);
}

// print the codes
void JuuhCode::printCodes() const {
  for (size_t i = 0; i < codes.max_size(); ++i) {
    char character = static_cast<char>(i);
    std::vector<bool> code = codes[i];

    if (code.empty()) {
      continue;
    }

    std::cout << "'" << character << "': ";

    for (const bool &b : code) {
      std::cout << b;
    }

    std::cout << std::endl;
  }
}

void JuuhCode::generateEncodedString() {
  std::string encoded = "";

  for (const char &c : stringToEncode) {
    uint8_t i = static_cast<uint8_t>(c);
    auto code = codes[i];

    for (const bool &b : code) {
      encoded += b ? "1" : "0";
    }
  }

  encodedString = encoded;
}

// print the encoded string
void JuuhCode::printEncodedString() const {
  std::cout << encodedString << std::endl;
}

// encode the codes and the string into bits for packaging into bytes
void JuuhCode::encode(const Node *node, std::vector<bool> &v) {
  if (!node->left) {
    // this is the code for this byte
    v.push_back(true);
    uint8_t b = static_cast<uint8_t>(node->character);

    // this is the byte in bits
    // only works in little endian machines
    v.push_back(((b >> 7) & 1));
    v.push_back(((b >> 6) & 1));
    v.push_back(((b >> 5) & 1));
    v.push_back(((b >> 4) & 1));
    v.push_back(((b >> 3) & 1));
    v.push_back(((b >> 2) & 1));
    v.push_back(((b >> 1) & 1));
    v.push_back((b & 1));

  } else {
    v.push_back(false);

    encode(node->left, v);
    encode(node->right, v);
  }
}

// convert bits to bytes for output purposes
void JuuhCode::bitsToBytes() {
  for (auto it = bits.begin(); it != bits.end();) {
    uint8_t byte = 0;

    for (size_t i = 0; i < 8; ++i) {
      // shift the bit to the right position and or it in place
      byte |= (*it & 1) << (7 - i);
      ++it;

      if (it == bits.end()) {
        break;
      }
    }

    bytes.push_back(byte);
  }
}

void JuuhCode::printBytes() const {
  for (const uint8_t &u : bytes) {
    std::cout << u;
  }

  std::cout << std::endl;
}

void JuuhCode::decode() {}

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
