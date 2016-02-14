#include <string>
#include <iostream>
#include "juuhcode.hpp"
#include "mainfunctions.cpp"

int main(int argc, char *argv[]) {
  if (argc < 2 || isatty(0)) {
    // if there's no argument(s) or we're not getting piped anything
    printUsage();
    return 2;
  }

  // gather everything from stdin
  std::string s{std::istreambuf_iterator<char>(std::cin),
                std::istreambuf_iterator<char>()};

  std::string option = argv[1];

  auto j = JuuhCode(s);

  switch (getOptionForArgument(option)) {
  case PRINT_CODES:
    j.printCodes();
    break;
  case PRINT_ENCODED:
    j.printEncodedString();
    break;
  case PRINT_STATS:
    j.printStats();
    break;
  case UNDEFINED:
    printUsage();
    return 2;
  }

  return 0;
}
