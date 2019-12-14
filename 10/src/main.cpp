#include <iostream>
#include <fstream>

int main() {
  std::fstream file("input.txt");
  std::string map[43];
  for (int i = 0; i < 43; ++i) {
    map[i] = file.next_line();
  }
}
