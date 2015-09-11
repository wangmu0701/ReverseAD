#include<iostream>
#include "src/tape/TestTape.hpp"

int main() {
  ReverseAD::TestTape<int> t(2);
  if (2 != t.getVal()) {
    std::cout << "TEST FAIL!" << std::endl;
    return 1;
  }
  std::cout << "TEST PASS!" << std::endl;
}

