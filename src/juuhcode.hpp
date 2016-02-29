#pragma once
#include <string>
#include <array>
#include <iostream>

#include "node.hpp"

class JuuhCode {
public:
  JuuhCode(const std::string &s);
  void printCodes() const;
  void printEncodedString() const;
  void printStats() const;

private:
  void calculateFrequencies();
  void createTree();
  void generateHuffmanCode(const Node *node, const std::string &code);
  void generateEncodedString();

  std::string stringToEncode;
  std::string encodedString;

  // we need room for 256 values, UINT8_MAX is 255
  std::array<std::string, UINT8_MAX + 1> codes = {{""}};
  std::array<uint64_t, UINT8_MAX + 1> frequencies = {{0}};

  Node *root = 0;
};
