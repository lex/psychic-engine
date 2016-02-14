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

enum option { UNDEFINED, PRINT_CODES, PRINT_ENCODED, PRINT_STATS };

option getOptionForArgument(std::string const &argument) {
  if (argument == "--print-codes") {
    return PRINT_CODES;
  }

  if (argument == "--print-encoded") {
    return PRINT_ENCODED;
  }

  if (argument == "--print-stats") {
    return PRINT_STATS;
  }

  return UNDEFINED;
}

