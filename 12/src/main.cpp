#include <iostream>
#include <array>
#include <cmath>

void pairwise_gravity(int i, int j, std::pair<std::array<long, 3>, std::array<long, 3>> moons[4]) {
  auto mooni = moons[i].first;
  auto moonj = moons[j].first;
  for (int k = 0; k < 3; ++k) {
    if (mooni[k] != moonj[k]) {
      if (mooni[k] > moonj[k]) {
        --moons[i].second[k];
        ++moons[j].second[k];
      } else {
        ++moons[i].second[k];
        --moons[j].second[k];
      }
    }
  }
}

void gravity(std::pair<std::array<long, 3>, std::array<long, 3>> moons[4]) {
  for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      pairwise_gravity(i, j, moons);
    }
  }
}

void velocity(std::pair<std::array<long, 3>, std::array<long, 3>> moons[4]) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 3; ++j) {
      moons[i].first[j] += moons[i].second[j];
    }
  }
}

long energy(std::pair<std::array<long, 3>, std::array<long, 3>> moon) {
  long grav = std::abs(moon.first[0]) + std::abs(moon.first[1]) + std::abs(moon.first[2]);
  long vel = std::abs(moon.second[0]) + std::abs(moon.second[1]) + std::abs(moon.second[2]);
  std::cout << "grav " << grav << " vel " << vel << "\n";
  return grav * vel;
}

long total_energy(std::pair<std::array<long, 3>, std::array<long, 3>> moons[4]) {
  long total = 0L;
  for (int i = 0; i < 4; ++i) {
    total += energy(moons[i]);
    std::cout << total << "\n";
  }
  return total;
}

int main() {
  std::pair<std::array<long, 3>, std::array<long, 3>> moons[4];
  //moons[0].first = {-1L, 0L, 2L};
  moons[0].first = {14L, 9L, 14L};
  moons[0].second = {0L, 0L, 0L};
  //moons[1].first = {2L, -10L, -7L};
  moons[1].first = {9L, 11L, 6L};
  moons[1].second = {0L, 0L, 0L};
  //moons[2].first = {4L, -8L, 8L};
  moons[2].first = {-6L, 14L, -4L};
  moons[2].second = {0L, 0L, 0L};
  //moons[3].first = {3L, 5L, -1L};
  moons[3].first = {4L, -4L, -3L};
  moons[3].second = {0L, 0L, 0L};

  for (int i = 0; i < 1000; ++i) {
    gravity(moons);
    velocity(moons);
    //std::cout << "after " << i << " steps\n";
    //std::cout << "x=" << moons[0].first[0] << " y=" << moons[0].first[1] << " z=" << moons[0].first[2] 
    //  << " v1=" << moons[0].second[0] << " v2=" << moons[0].second[1] << " v3=" << moons[0].second[2] << "\n";
  }

  std::cout << "Part 1: " << total_energy(moons) << "\n";

  return 0;
}
