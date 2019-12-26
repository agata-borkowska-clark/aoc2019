#include <iostream>
#include <fstream>
#include <climits>
#include <map>
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
  intcomputer scaffold(original);
  std::vector<long> output = scaffold.run();

  std::vector<std::vector<char>> grid;
  grid.push_back(std::vector<char>());
  int i = 0;
  for (long l : output) {
    if (l == 10L) {
      grid.push_back(std::vector<char>());
      ++i;
    } else {
      grid[i].push_back((char) l);
    }
  }
  for (long l : output) {
    std::cout << (char) l;
  }
  //int length = (int) grid.size();
  //int width = (int) grid[0].size();
  std::cout << grid.size() << " " << grid[0].size() << '\n';
  int sum = 0;
  for (int i = 1; i < 64; ++i) {
    for (int j = 1; j < 42; ++j) {
      //std::cout << grid[i - 1][j] << " " << grid[i][j - 1] << " " << grid[i + 1][j] << " " << grid[i][j + 1] << '\n';
      //std::cout << i << " " << j << '\n';
      if (grid[i - 1][j] == '#' &&
        grid[i][j - 1] == '#' &&
        grid[i + 1][j] == '#' &&
        grid[i][j + 1] == '#') {
        sum += i * j;
      }
      //std::cout << "j: " << j << '\n';
    }
    //std::cout << "i: " << i << '\n';
  }
  std::cout << "Part 1: " << sum << '\n';
}