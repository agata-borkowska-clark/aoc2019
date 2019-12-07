#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
  int input = 1;
  std::fstream file("input.txt");
  std::vector<int> original;
  int a;
  char comma;
  while (file >> a >> comma) {
    original.push_back(a);
  }   
  std::vector<int> v = original;
  //v[1] = 12;
  //v[2] = 2;
  unsigned long current = 0;
  while (current < v.size()) {
    int instruction = v[current];
    std::string mode = "000";
    if (instruction > 99) {
      mode = std::to_string(instruction / 100);
      instruction = instruction % 100;
    }
    if (mode.size() == 2) {
      mode = std::string("0").append(mode);
    } else if (mode.size() == 1) {
      mode = std::string("00").append(mode);
    }
    std::cout << mode << " " << instruction << " " << current <<"\n";
    int param1 = 0;
    int param2 = 0;
    switch (instruction) {
      case 1:
        //std::cout << param1 << " " << param2 << "\n";
        param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
        param2 = mode.at(1) == '0' ? v[v[current + 2]] : v[current + 2];
        v[v[current + 3]] = param1 + param2;
        current += 4;
        break;
      case 2:
        param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
        param2 = mode.at(1) == '0' ? v[v[current + 2]] : v[current + 2];
        v[v[current + 3]] = param1 * param2;
        current += 4;
        break;
      case 3:
        v[v[current + 1]] = input;
        current += 2;
        break;
      case 4:
        std::cout << v[v[current + 1]] << "\n";
        current += 2;
        break;
      case 99:
        return 0;
      default:
        std::cout << "Something went wrong, instruction: " << instruction << " mode: " << mode << "\n";
        return 1;
    }
  }
  return 0;  
}

