#pragma once
#include <string>
#include <map>
#include <array>
#include <queue>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iostream>

#include "node.hpp"

class JuuhCode {
public:
  JuuhCode(std::string s);
  void printCodes() const;
  void printEncodedString() const;
  void printStats() const;

private:
  void calculateFrequencies();
  void createTree();
  void generateHuffmanCode(Node *node, std::string code);
  void generateEncodedString();

  std::string stringToEncode;
  std::string encodedString;
  std::map<char, std::string> codes;
  std::array<uint64_t, UINT8_MAX> frequencies = {{0}};

  Node *root = 0;
};
