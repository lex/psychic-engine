#include <string>
#include <iostream>
#include "juuhcode.hpp"

enum option { UNDEFINED, PRINT_CODES, PRINT_ENCODED, PRINT_STATS, PRINT_RAW };

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
  if (argument == "--print-codes") {
    return PRINT_CODES;
  }

  if (argument == "--print-encoded") {
    return PRINT_ENCODED;
  }

  if (argument == "--print-stats") {
    return PRINT_STATS;
  }

  if (argument == "--print-raw") {
    return PRINT_RAW;
  }

  return UNDEFINED;
}

int main(int argc, char *argv[]) {
  if (argc < 2 || isatty(0)) {
    // if there's no argument(s) or we're not getting piped anything
    printUsage();
    return 1;
  }

  // gather everything from stdin
  const std::string s{std::istreambuf_iterator<char>(std::cin),
                      std::istreambuf_iterator<char>()};

  const std::string argument = argv[1];

  const JuuhCode j = JuuhCode(s);

  switch (getOptionForArgument(argument)) {
  case PRINT_CODES:
    j.printCodes();
    break;
  case PRINT_ENCODED:
    j.printEncodedString();
    break;
  case PRINT_STATS:
    j.printStats();
    break;
  case PRINT_RAW:
    j.printBytes();
    break;
  case UNDEFINED:
    printUsage();
    return 1;
  }

  return 0;
}
