#include "juuhcode.hpp"
#include "juuhqueue.hpp"

JuuhCode::JuuhCode() {}

void JuuhCode::encodeFile(const std::string &input, const std::string &output) {
  std::streampos size;
  char *data;
  std::ifstream inputFile(input,
                          std::ios::binary | std::ios::in | std::ios::ate);

  if (!inputFile.is_open()) {
    std::cout << "failed to open" << std::endl;
    return;
  }

  size = inputFile.tellg();
  data = new char[size];
  inputFile.seekg(0, std::ios::beg);
  inputFile.read(data, size);

  inputFile.close();

  stringToEncode = data;
  delete[] data;

  std::cout << "Calculating frequencies..." << std::endl;
  calculateFrequencies();

  std::cout << "Creating a tree..." << std::endl;
  createTree();

  std::cout << "Generating Huffman code..." << std::endl;
  std::vector<bool> v;
  generateHuffmanCode(root, v);

  std::vector<bool> b;
  encode(root, b);
  bits = b;

  appendEncodedBits();

  bitsToBytes();

  std::ofstream outputFile;
  outputFile.open(output, std::ofstream::out);

  for (const uint8_t &byte : bytes) {
    outputFile << byte;
  }

  outputFile.close();
}

void JuuhCode::decodeFile(const std::string &input, const std::string &output) {
  std::streampos size;
  char *data;
  std::ifstream file(input, std::ios::binary | std::ios::in | std::ios::ate);

  if (!file.is_open()) {
    std::cout << "failed to open" << std::endl;
    return;
  }

  size = file.tellg();
  data = new char[size];
  file.seekg(0, std::ios::beg);
  file.read(data, size);
  file.close();

  size_t fileSize = static_cast<size_t>(size);

  // convert bytes to bits
  for (size_t k = 0; k < fileSize; ++k) {

    char c = data[k];

    uint8_t byte = static_cast<uint8_t>(c);

    size_t shiftCount = 7;

    do {
      bool bit = ((byte >> shiftCount) & 1);
      bits.push_back(bit);
    } while (shiftCount-- != 0);
  }

  delete[] data;

  Node *decodedRoot = readNode();

  std::string s = "";

  while (true) {
    // in case we hit the end
    if (decodingIndex >= bits.size()) {
      break;
    }

    char c = getCharacter(decodedRoot);
    s += c;
  }

  std::ofstream outputFile;
  outputFile.open(output, std::ofstream::out);

  outputFile << s;

  outputFile.close();
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

      // do we need to shift more?
      if (it == bits.end()) {
        break;
      }
    }

    bytes.push_back(byte);
  }
}

void JuuhCode::appendEncodedBits() {
  for (const char &c : stringToEncode) {
    uint8_t i = static_cast<uint8_t>(c);
    auto code = codes[i];

    for (const bool &b : code) {
      bits.push_back(b);
    }
  }
}

bool JuuhCode::getBit() { return bits[decodingIndex++]; }

uint8_t JuuhCode::getByte() {
  uint8_t byte = 0;

  for (size_t i = 0; i < 8; ++i) {
    bool bit = getBit();
    byte |= bit;

    if (i != 7) {
      byte <<= 1;
    }
  }

  return byte;
}

Node *JuuhCode::readNode() {
  if (getBit()) {
    return new Node(0, getByte());
  }

  Node *left = readNode();
  Node *right = readNode();

  return new Node(left, right);
}

char JuuhCode::getCharacter(const Node *n) {
  if (!n->left && !n->right) {
    // it's a leaf, get the character
    return n->character;
  } else if (getBit()) {
    // bit is 1, go right
    return getCharacter(n->right);
  } else {
    // bit is 0, go left
    return getCharacter(n->left);
  }
}
