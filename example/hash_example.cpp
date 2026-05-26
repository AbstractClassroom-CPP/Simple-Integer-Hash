#include "simple_integer_hash/IntegerHash.hpp"

#include <cstdint>
#include <iomanip>
#include <iostream>

int main(int argc, char** argv) {
  using simple_integer_hash::IntegerHash;

  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      IntegerHash h(argv[i]);
      std::cout << '"' << h.str() << "\" -> 0x" << std::hex
                << static_cast<std::uint64_t>(h.hash()) << std::dec << '\n';
    }
    return 0;
  }

  IntegerHash a("hello");
  IntegerHash b("world");
  IntegerHash c("hello");

  std::cout << "a == c? "
            << (a.equals(c.str()) ? "true" : "false") << '\n';

  std::cout << "a != c? "
            << (!a.equals(c.str()) ? "true" : "false") << '\n';
  std::cout << "a.hash(): 0x" << std::hex << a.hash() << std::dec << '\n';
  std::cout << "b.hash(): 0x" << std::hex << b.hash() << std::dec << '\n';
  std::cout << "c.hash(): 0x" << std::hex << c.hash() << std::dec << '\n';

  return 0;
}


