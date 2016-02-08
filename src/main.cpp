#include <string>
#include <iostream>
#include "juuhcode.hpp"

int main(int argc, char *argv[]) {
  const auto s = u8"fresh beer enjoyment 🍺🍺🍺";

  std::cout << s << std::endl;

  auto j = JuuhCode(s);
  j.print();

  return 0;
}

