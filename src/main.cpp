#include <string>
#include <iostream>
#include "juuhcode.hpp"

enum option { UNDEFINED, PRINT_CODES, ENCODE, DECODE };

void printUsage() {
  std::cout << "Examples of use:"
            << "\n"
            << "\t"
            << "juuhman [option] < input_file"
            << "\n"
            << "\t"
            << "head -n 50 /dev/urandom | juuhman [option]"
            << "\n"
            << "\n"
            << "Options:"
            << "\n"
            << "\t"
            << "--print-codes"
            << "\n"
            << "\t"
            << "--print-encoded"
            << "\n"
            << "\t"
            << "--print-stats" << std::endl;
}

option getOptionForArgument(const std::string &argument) {
  if (argument == "--show-codes") {
    return PRINT_CODES;
  }

  if (argument == "--encode") {
    return ENCODE;
  }

  if (argument == "--decode") {
    return DECODE;
  }

  return UNDEFINED;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    // if there's no argument(s) or we're not getting piped anything
    printUsage();
    return 1;
  }

  // gather everything from stdin
  // const std::string ss{std::istreambuf_iterator<char>(std::cin),
  //                     std::istreambuf_iterator<char>()};
  // const std::string s = ss.substr(0, ss.size() - 1);

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
  case PRINT_CODES:
    j.printCodes(inputFile);
    break;
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
