#pragma once
#include <string>
#include <map>
#include <queue>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iostream>

#include "node.hpp"

class JuuhCode {
public:
  JuuhCode(std::string s);
  void Print();

private:
  void CalculateFrequencies();
  void CreateTree();
  void GenerateHuffmanCode(Node *node, std::string code);

  std::string s;
  std::map<char, std::string> codes;
  std::map<uint8_t, uint64_t> frequencies;

  Node *root = 0;
};
