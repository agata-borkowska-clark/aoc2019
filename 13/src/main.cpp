#include <iostream>
#include <fstream>
#include <vector>

#include "../../intcomputer/src/intcomputer.h"

int main() {
  std::fstream file("input.txt");
  std::vector<long> original;
  long a;
  char comma;
  while (file >> a >> comma) {
    original.push_back(a);
  }
  file >> a;
  original.push_back(a);
  intcomputer game(original);
  std::vector<long> output = game.run();
  int block_count = 0;
  for (int i = 2; i < (int) output.size(); i +=3) {
    if (output[i] == 2L) {
      ++block_count;
    }
  }
  std::cout << "Part 1: " << block_count << "\n";
}