#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

int main() {
  std::fstream file("input.txt");
  std::vector<std::pair<int, int>> wire1;
  std::pair<int, int> start(0, 0);
  wire1.push_back(start);
  std::vector<std::pair<int, int>> wire2;
  std::pair<int, int> start2(0, 0);
  wire2.push_back(start2);
  char direction;
  int distance;
  char delim;
  do {
    file >> direction >> distance >> delim;
    for (int i = 0; i < distance; ++i) {
      std::pair<int, int> coords;
      switch (direction) {
        case 'R':
	  coords.first = wire1.at(wire1.size() - 1).first;
	  coords.second = wire1.at(wire1.size() - 1).second + 1;
	  break;
	case 'L':
	  coords.first = wire1.at(wire1.size() - 1).first;
	  coords.second = wire1.at(wire1.size() - 1).second - 1;
	  break;
	case 'U':
	  coords.first = wire1.at(wire1.size() - 1).first + 1;
	  coords.second = wire1.at(wire1.size() - 1).second;
	  break;
	case 'D':
	  coords.first = wire1.at(wire1.size() - 1).first - 1;
	  coords.second = wire1.at(wire1.size() - 1).second;
	  break;
      }
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
      std::pair<int, int> coords;
      switch (direction) {
        case 'R':
	  coords.first = wire2.at(wire2.size() - 1).first;
	  coords.second = wire2.at(wire2.size() - 1).second + 1;
	  break;
	case 'L':
	  coords.first = wire2.at(wire2.size() - 1).first;
	  coords.second = wire2.at(wire2.size() - 1).second - 1;
	  break;
	case 'U':
	  coords.first = wire2.at(wire2.size() - 1).first + 1;
	  coords.second = wire2.at(wire2.size() - 1).second;
	  break;
	case 'D':
	  coords.first = wire2.at(wire2.size() - 1).first - 1;
	  coords.second = wire2.at(wire2.size() - 1).second;
	  break;
      }
      //printf("%d %d\n", coords.first, coords.second);
      wire2.push_back(coords);
    }
  } while (delim == ',' && !file.eof());
  printf("done second wire\n");
  std::sort(wire1.begin(), wire1.end());
  std::sort(wire2.begin(), wire2.end());
  printf("done sorting\n");
  std::vector<std::pair<int, int>> intersection(wire1.size() + wire2.size());
  std::vector<std::pair<int, int>>::iterator it;
  it = std::set_intersection(wire1.begin(), wire1.end(), wire2.begin(), wire2.end(), intersection.begin());
  intersection.resize(it - intersection.begin());
  for (it = intersection.begin(); it != intersection.end(); ++it) {
    //printf("%d %d\n", it->first, it->second);
  }
  std::vector<int> candidates;
  for (it = intersection.begin(); it <= intersection.end(); ++it) {
    candidates.push_back(std::abs(it->first) + std::abs(it->second));
    //printf(" candidate: %d\n", candidates[candidates.size() - 1]);
  }
  std::sort(candidates.begin(), candidates.end());
  printf("%d\n", candidates[2]);
}
