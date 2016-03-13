#include <string>
#include <iostream>
#include "juuhcode.hpp"

enum option { UNDEFINED, ENCODE, DECODE };

void printUsage() {
  std::cout << "Examples of use:"
            << "\n"
            << "\t"
            << "juuhman --encode test.txt -o encoded.txt"
            << "\n"
            << "\t"
            << "juuhman --decode encoded.txt -o decoded.txt"
            << "\n"
            << "\n"
            << "Options:"
            << "\n"
            << "\t"
            << "--encode"
            << "\n"
            << "\t"
            << "--decode"
            << std::endl;
}

option getOptionForArgument(const std::string &argument) {
  if (argument == "--encode") {
    return ENCODE;
  }

  if (argument == "--decode") {
    return DECODE;
  }

  return UNDEFINED;
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    // if there are not enough arguments
    printUsage();
    return 1;
  }

  const std::string option = argv[1];
  const std::string inputFile = argv[2];
  const std::string outputArgument = argv[3];
  const std::string outputFile = argv[4];

  // argv[3] has to be -o
  if (outputArgument != "-o") {
    printUsage();
    return 1;
  }

  JuuhCode j = JuuhCode();

  switch (getOptionForArgument(option)) {
  case ENCODE:
    j.encodeFile(inputFile, outputFile);
    break;
  case DECODE:
    j.decodeFile(inputFile, outputFile);
    break;
  case UNDEFINED:
    printUsage();
    return 1;
  }

  return 0;
}
