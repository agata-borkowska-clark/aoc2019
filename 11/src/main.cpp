#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "../../intcomputer/src/intcomputer.h"

enum Direction {
  UP = 0,
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3
};

std::pair<int, int> move_robot(std::pair<int, int> loc, int facing) {
  //std::cout << "at " << loc.first << " " << loc.second << " facing " << facing << "\n";
  switch (facing) {
    case UP: {
      std::pair<int, int> new_loc(loc.first - 1, loc.second);
      return new_loc;
    }
    case RIGHT: {
      std::pair<int, int> new_loc(loc.first, loc.second + 1);
      return new_loc;
    }
    case DOWN: {
      std::pair<int, int> new_loc(loc.first + 1, loc.second);
      return new_loc;
    }
    case LEFT: {
      std::pair<int, int> new_loc(loc.first, loc.second - 1);
      return new_loc;
    }
  }
  return loc;
}

int main() {
  //long input = 1l;
  std::fstream file("input.txt");
  std::vector<long> original;
  long a;
  char comma;
  while (file >> a >> comma) {
    original.push_back(a);
  }
  file >> a;
  original.push_back(a);
  intcomputer robot(original);
  std::map<std::pair<int, int>, char> hull;
  int facing = UP;
  bool finished = false;
  std::pair<int, int> location(0, 0);
  std::vector<long> output;
  while (!finished) {
    long input = 0L;
    if (hull[{location.first, location.second}] == '#') {
      input = 1L;
      std::cout<< "white square\n";
    } else {
      std::cout << "black square\n";
    }
    robot.queue_input(input);
    output = robot.run();
    finished = robot.is_done();
    if (finished) {
      break;
    }
    hull.emplace(location, output[0] == 0 ? '-' : '#');
    std::cout << "loc " << location.first << " " << location.second << " painted " << hull[{location.first, location.second}] << "\n";
    robot.consume_output();
    facing = (facing + 4 + (output[1] == 0 ? -1 : 1)) % 4;
    robot.consume_output();
    location = move_robot(location, facing);
  }
  std::cout << "Part 1 " << hull.size() << "\n";
}