#include <iostream>
#include <fstream>
#include <climits>
#include <map>
#include <vector>

#include "../../intcomputer/src/intcomputer.h"

enum Direction {
  NORTH = 1,
  SOUTH = 2,
  WEST = 3,
  EAST = 4
};

enum Output {
  WALL = 0,
  FLOOR = 1,
  TANK = 2
};

std::pair<int, int> make_a_step(std::pair<int, int> pos, Direction facing) {
  auto new_pos = pos;
  switch (facing) {
    case NORTH:
      --new_pos.first;
      break;
    case SOUTH:
      ++new_pos.first;
      break;
    case EAST:
      ++new_pos.second;
      break;
    case WEST:
      --new_pos.second;
      break;
    default:
      break;
  }
  return new_pos;
}

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
  intcomputer robot(original);
  std::vector<long> output = robot.run(NORTH);
  std::map<std::pair<int, int>, Output> plan;
  plan[{0,0}] = FLOOR;
  std::pair<int, int> position(0, 0);
  Direction facing = NORTH;
  int steps = 0;
  while (output[0] != TANK && steps < 100) {
    //std::cout << "position " << position.first << " " << position.second << " facing " << facing << "\n";
    if (output[0] == FLOOR) {
      //move forward until a wall is hit
      plan[position] = FLOOR;
      position = make_a_step(position, facing);
      ++steps;
    } else {
      plan[make_a_step(position, facing)] = WALL;
      int new_dir = (facing + 2) % 5;
      if (new_dir == 0) {
        new_dir += 2;
      }
      facing = (Direction) new_dir;
      std::cout << new_dir << '\n';
    }
    robot.consume_output();
    output = robot.run(facing);
  }
  std::cout << "Map size: " << plan.size() << "\n";
  char map[50][50];
  for (auto cell : plan) {
    //std::cout << "Marked " << cell.first.first << " " << cell.first.second << "\n";
    char m = ' ';
    switch (cell.second) {
      case WALL:
        m = 'W';
        break;
      case FLOOR:
        m = '.';
        break;
      case TANK:
        m = 'O';
        break;
      default:
        break;
    }
    std::cout << "Marked " << cell.first.first << " " << cell.first.second << " " << m << "\n";
    map[cell.first.first + 25][cell.first.second + 25] = m;
  }
  for (int i = 0; i < 0; ++i) {
    for (int j = 0; j < 50; ++j) {
      char c = map[i][j];
      if (c != 'W' && c != '.' && c != 'O' && c != ' ') {
        c = ' ';
      }
      std::cout << c;
    }
    std::cout << '\n';
  }
}