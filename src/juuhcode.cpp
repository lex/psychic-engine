#include "juuhcode.hpp"
#include "juuhqueue.hpp"
#include "juuhvector.hpp"

JuuhCode::JuuhCode() {}

void JuuhCode::encodeFile(const std::string &input, const std::string &output) {
  // read the input file's contents
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

  // calculate byte frequencies
  std::cout << "Calculating frequencies..." << std::endl;
  calculateFrequencies();

  // create the huffman tree
  std::cout << "Creating a tree..." << std::endl;
  createTree();

  // create the huffman code from that tree
  std::cout << "Generating Huffman code..." << std::endl;
  // std::vector<bool> v;
  JuuhVector<bool> v;
  generateHuffmanCode(root, v);

  // encode the tree data as in
  // http://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
  JuuhVector<bool> b;
  // std::vector<bool> b;
  encode(root, b);
  bits = JuuhVector<bool>(b);

  // append the encoded string itself
  appendEncodedBits();

  // convert bits to bytes for saving
  bitsToBytes();

  // write the output
  std::ofstream outputFile;
  outputFile.open(output, std::ofstream::out);

  for (size_t i = 0; i < bytes.size(); ++i) {
    const uint8_t byte = bytes[i];
    outputFile << byte;
  }

  outputFile.close();
}

void JuuhCode::decodeFile(const std::string &input, const std::string &output) {
  // read file contents
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

  // rebuild the tree
  Node *decodedRoot = rebuildTree();

  std::string s = "";

  // decode the encoded data with the rebuilt tree
  while (true) {
    // in case we hit the end
    if (decodingIndex >= bits.size()) {
      break;
    }

    char c = getCharacter(decodedRoot);
    s += c;
  }

  // remove the last byte because of some bug in saving or loading the data
  s = s.substr(0, s.size() - 1);

  // write the output
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
                                   const JuuhVector<bool> &code) {
  // assign a code
  if (!node->left && !node->right) {
    size_t index = static_cast<size_t>(node->character);
    codes[index] = code;
    return;
  }

  auto left = JuuhVector<bool>(code);
  left.push_back(false);

  auto right = JuuhVector<bool>(code);
  right.push_back(true);

  generateHuffmanCode(node->left, left);
  generateHuffmanCode(node->right, right);
}

// encode the codes and the string into bits for packaging into bytes
void JuuhCode::encode(const Node *node, JuuhVector<bool> &v) {
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
  size_t bitCount = 0;
  uint8_t byte = 0;

  for (size_t i = 0; i < bits.size(); ++i) {
    // shift the bit to the right position and or it in place
    // byte |= (*it & 1) << (7 - i);
    byte |= (bits[i] & 1) << (7 - bitCount);
    ++bitCount;

    // is our byte ready?
    if (bitCount == 8) {
      bytes.push_back(byte);
      byte = 0;
      bitCount = 0;
    }

    if (i == bits.size() - 1) {
      break;
    }
  }
}

void JuuhCode::appendEncodedBits() {
  for (const char &c : stringToEncode) {
    uint8_t i = static_cast<uint8_t>(c);
    auto code = codes[i];

    // for (const bool &b : code) {
    for (size_t index = 0; index < code.size(); ++index) {
      bits.push_back(code[index]);
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

Node *JuuhCode::rebuildTree() {
  if (getBit()) {
    return new Node(0, getByte());
  }

  Node *left = rebuildTree();
  Node *right = rebuildTree();

  return new Node(left, right);
}

// find a character for the current code
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
