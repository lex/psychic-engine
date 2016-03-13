#pragma once
#include <string>
#include <array>
#include <iostream>
#include <vector>
#include <sstream>

#include "node.hpp"

class JuuhCode {
public:
  JuuhCode(const std::string &s);
  void printCodes() const;
  void printEncodedString() const;
  void printStats() const;
  void printBytes() const;
  void decode();

private:
  void calculateFrequencies();
  void createTree();
  void generateHuffmanCode(const Node *node, const std::vector<bool> &code);
  void generateEncodedString();
  void encode(const Node *node, std::vector<bool> &v);
  void bitsToBytes();
  Node* readNode();
  void printTree(const Node* n);
  bool getBit();
  uint8_t getByte();
  void printDecoded();
  char getCharacter(const Node* n);
  void appendEncodedBits();

  size_t decodeIndex = 0;

  std::string stringToEncode;
  std::string encodedString;
  size_t nodeCount = 0;
  size_t leafCount = 0;

  // we need room for 256 values, UINT8_MAX is 255
  std::array<std::vector<bool>, UINT8_MAX + 1> codes;
  // std::array<uint8_t, UINT8_MAX + 1> byteCodes = {{0}};
  std::array<uint64_t, UINT8_MAX + 1> frequencies = {{0}};

  std::vector<bool> bits;
  std::vector<uint8_t> bytes;

  Node *root = 0;
};
