#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../intcomputer/src/intcomputer.h"

int main() {
  int input = 1;
  std::fstream file("input.txt");
  std::vector<long> original;
  long a;
  char comma;
  while (file >> a >> comma) {
    original.push_back(a);
  }
  file >> a;
  original.push_back(a);
  intcomputer intcomp(original);
  std::vector<long> v = intcomp.run((long) input);
  std::cout << "Part 1: " << v[v.size() - 1] << "\n";
  input = 5;
  intcomputer p2(original);
  v = p2.run((long) input);
  std::cout << "Part 2 " << v[0] << "\n";
  return 0;  
}

