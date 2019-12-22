#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "../../intcomputer/src/intcomputer.h"

int main() {
  //long input = 1l;
  std::fstream file("input.txt");
  std::map<unsigned long, long> original;
  unsigned long a;
  char comma;
  int counter = 0;
  while (file >> a >> comma) {
    original.emplace(counter, a);
    ++counter;
  }
  file >> a;
  original.emplace(counter, a);
  intcomputer intcomp(original);
  std::vector<long> v = intcomp.run(2L);
  for (long i : v) {
    std::cout << i << ", ";
  }
  std::cout <<"\n";

  return 0;  
}

