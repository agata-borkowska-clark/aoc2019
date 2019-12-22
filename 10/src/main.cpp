#include <iostream>
#include <fstream>
#include <string>

int count_asteroids(const std::string[]& map, int x, int y) {
  int count = 0;
  for (int i = 0; i < 43; ++i) {
    for (int j = 0; j < map[i].size(); ++j) {
      if (i == 0 && j == 0) {
        continue;
      }
      if (y - i > 0 && x - j > 0) {
        if (map[y - i][x - j] == '#') {
          ++count;
        }
      }
      if (y + i < 43 && x + j < map[i].size()) {
        if (map[])
      } 

    }
  }

}

int main() {
  std::fstream file("input.txt");
  std::string map[43];
  int i = 0;
  while (std::getline(file, map[i])) {
    ++i;
  }
  int max = 0;
  for (int y = 0; y < 43; ++y) {
    for (int x = 0; x < (int) map[1].size(); ++x) {
      if (map[y][x] == '#') {
        int res = count_asteroids(map, x, y);
      }
      if (res > max) {
        max = res;
      }
    }
  }
  std::cout << max << "\n";
}
