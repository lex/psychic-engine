#pragma once
#include <string>
#include <array>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "node.hpp"
#include "juuhvector.hpp"

class JuuhCode {
public:
  JuuhCode();
  void encodeFile(const std::string &input, const std::string &output);
  void decodeFile(const std::string &input, const std::string &output);

private:
  // encoding stuff
  void calculateFrequencies();
  void createTree();
  void generateHuffmanCode(const Node *node, const JuuhVector<bool> &code);

  void encode(const Node *node, JuuhVector<bool> &v);
  void bitsToBytes();

  void appendEncodedBits();

  // decoding stuff
  Node *rebuildTree();
  bool getBit();
  uint8_t getByte();

  char getCharacter(const Node *n);

  size_t decodingIndex = 0;

  std::string stringToEncode;

  // we need room for 256 values, UINT8_MAX is 255
  std::array<JuuhVector<bool>, UINT8_MAX + 1> codes;
  std::array<uint64_t, UINT8_MAX + 1> frequencies = {{0}};

  JuuhVector<bool> bits;
  JuuhVector<uint8_t> bytes;

  Node *root = 0;
};
