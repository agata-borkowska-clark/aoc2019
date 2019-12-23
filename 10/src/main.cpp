#include <iostream>
#include <fstream>
#include <string>

bool coprime(int i, int j) {
  //std::cout << "coprime: " << i << " " << j << "\n";
  while (i != 0 && j != 0) {
    if (i > j) {
      i %= j;
    } else {
      j %= i;
    }
  }
  int result = i > j ? i : j;
  //std::cout << "GCD " << result << "\n";
  return result == 1;
};

int count_asteroids(const std::string map[], int y, int x) {
  int count = 0;
  for (int yj = y - 1; yj >= 0; --yj) {
    if (map[yj][x] == '#') {
      ++count;
      break;
    }
  }
  for (int yj = y + 1; yj < 43; ++yj) {
    if (map[yj][x] == '#') {
      ++count;
      break;
    }
  }
  for (int xi = x - 1; xi >= 0; --xi) {
    if (map[y][xi] == '#') {
      ++count;
      break;
    }
  }
  for (size_t xi = x + 1; xi < map[y].size(); ++xi) {
    if (map[y][xi] == '#') {
      ++count;
      break;
    }
  }
  for (int i = 1; y + i < 43; ++i) {
    for (size_t j = 1; x + j < map[i].size(); ++j) {
      if (!coprime(i, j)) {
        continue;
      }
      int up = i;
      int left = j;
      int down = i;
      int right = j;
      while (y - up > 0 && x - left > 0) {
        if (map[y - up][x - left] == '#') {
          ++count;
          break;
        }
        up += i;
        left += j;
      }
      up = i;
      right = j;
      while (y - up > 0 && x + right < (int) map[i].size()) {
        if (map[y - up][x + right] == '#') {
          ++count;
          break;
        }
        up += i;
        right += j;
      }
      down = i;
      left = j;
      while (y + down < 43 && x - left > 0) {
        if (map[y + down][x - left] == '#') {
          ++count;
          break;
        }
        up += i;
        left += j;
      }
      down = i;
      right = j;
      while (y + down < 43 && x + right < (int) map[i].size()) {
        if (map[y + down][x + right] == '#') {
          ++count;
          break;
        }
        down += i;
        right += j;
      }
    }
  }
  return count;
};

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
        int res = count_asteroids(map, y, x);
        if (res > max) {
          max = res;
        }
      }
    }
  }
  std::cout << max << "\n";
}
