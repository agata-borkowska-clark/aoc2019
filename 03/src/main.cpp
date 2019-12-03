#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <tuple>
#include <climits>

int main() {
  std::fstream file("input.txt");
  std::vector<std::tuple<int, int, int>> wire1;
  std::tuple<int, int, int> start(0, 0, 0);
  wire1.push_back(start);
  std::vector<std::tuple<int, int, int>> wire2;
  std::tuple<int, int, int> start2(0, 0, 0);
  wire2.push_back(start2);
  char direction;
  int distance;
  char delim;
  do {
    file >> direction >> distance >> delim;
    for (int i = 0; i < distance; ++i) {
      std::tuple<int, int, int> coords;
      switch (direction) {
        case 'R':
	  std::get<0>(coords) = std::get<0>(wire1.at(wire1.size() - 1));
	  std::get<1>(coords) = std::get<1>(wire1.at(wire1.size() - 1)) + 1;
	  break;
	case 'L':
	  std::get<0>(coords) = std::get<0>(wire1.at(wire1.size() - 1));
	  std::get<1>(coords) = std::get<1>(wire1.at(wire1.size() - 1)) - 1;
	  break;
	case 'U':
	  std::get<0>(coords) = std::get<0>(wire1.at(wire1.size() - 1)) + 1;
	  std::get<1>(coords) = std::get<1>(wire1.at(wire1.size() - 1));
	  break;
	case 'D':
	  std::get<0>(coords) = std::get<0>(wire1.at(wire1.size() - 1)) - 1;
	  std::get<1>(coords) = std::get<1>(wire1.at(wire1.size() - 1));
	  break;
      }
      std::get<2>(coords) = std::get<2>(wire1.at(wire1.size() - 1)) + 1;
      //printf("%d %d\n", coords.first, coords.second);
      wire1.push_back(coords);
    }
  } while (delim == ',');
  printf("done first wire\n");
  delim = ',';
  do {
    file >> direction >> distance >> delim;
    //printf("Instr: %c %d %c\n", direction, distance, delim);
    for (int i = 0; i < distance; ++i) {
      std::tuple<int, int, int> coords;
      switch (direction) {
        case 'R':
	  std::get<0>(coords) = std::get<0>(wire2.at(wire2.size() - 1));
	  std::get<1>(coords) = std::get<1>(wire2.at(wire2.size() - 1)) + 1;
	  break;
	case 'L':
	  std::get<0>(coords) = std::get<0>(wire2.at(wire2.size() - 1));
	  std::get<1>(coords) = std::get<1>(wire2.at(wire2.size() - 1)) - 1;
	  break;
	case 'U':
	  std::get<0>(coords) = std::get<0>(wire2.at(wire2.size() - 1)) + 1;
	  std::get<1>(coords) = std::get<1>(wire2.at(wire2.size() - 1));
	  break;
	case 'D':
	  std::get<0>(coords) = std::get<0>(wire2.at(wire2.size() - 1)) - 1;
	  std::get<1>(coords) = std::get<1>(wire2.at(wire2.size() - 1));
	  break;
      }
      std::get<2>(coords) = std::get<2>(wire2.at(wire2.size() - 1)) + 1;
      //printf("%d %d\n", std::get<0>(coords), std::get<1>(coords));
      wire2.push_back(coords);
    }
  } while (delim == ',' && !file.eof());
  printf("done second wire\n");
  std::sort(wire1.begin(), wire1.end());
  std::sort(wire2.begin(), wire2.end());
  printf("done sorting\n");
  std::vector<std::tuple<int, int, int>> intersection;
  std::vector<std::tuple<int, int, int>>::iterator it1 = wire1.begin();
  std::vector<std::tuple<int, int, int>>::iterator it2 = wire2.begin();
  while (it1 != wire1.end() && it2 != wire2.end()) {
    std::pair<int, int> pair1(std::get<0>(*it1), std::get<1>(*it1));
    std::pair<int, int> pair2(std::get<0>(*it2), std::get<1>(*it2));
    if (pair1 < pair2) {
      ++it1;
    } else if (pair2 < pair1) {
      ++it2;
    } else {
      std::tuple<int, int, int> coords;
      std::get<0>(coords) = std::get<0>(*it1);
      std::get<1>(coords) = std::get<1>(*it1);
      std::get<2>(coords) = std::get<2>(*it1) + std::get<2>(*it2);
      intersection.push_back(coords);
      //printf("%d %d %d\n", std::get<0>(coords), std::get<1>(coords), std::get<2>(coords));
      ++it1;
      ++it2;
    }
  }

  std::vector<int> candidates;
  int min_distance = INT_MAX;
  for (it1 = intersection.begin(); it1 != intersection.end(); ++it1) {
    candidates.push_back(std::abs(std::get<0>(*it1)) + std::abs(std::get<1>(*it1)));
    if (std::get<2>(*it1) < min_distance && std::get<2>(*it1) > 0) {
      min_distance = std::get<2>(*it1);
    }
    //printf(" candidate: %d %d\n", std::get<0>(*it1), std::get<1>(*it1));
  }
  std::sort(candidates.begin(), candidates.end());
  printf("Part 1: %d\n", candidates[1]);
  printf("Part 2: %d\n", min_distance);
}
