#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main() {
  int input = 1;
  std::fstream file("input.txt");
  std::map<unsigned long, unsigned long> original;
  unsigned long a;
  char comma;
  int counter = 0;
  while (file >> a >> comma) {
    original.emplace(counter, a);
    ++counter;
  }
  file >> a;
  original.emplace(counter, a);
  std::map<unsigned long, unsigned long> v = original;
  std::cout << v.size() << "\n";
  //v[1] = 12;
  //v[2] = 2;
  unsigned long current = 0;
  unsigned long relative_base = 0;
  while (true) {
    if (current < 0) {
      std::cout << "CURRENT: " << current << "\n";
    }
    unsigned long instruction = v[current];
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
    std::cout << "mode: " <<  mode << " instruction: " << instruction << " position: " << current <<"\n";
    unsigned long param1 = 0;
    unsigned long param2 = 0;
    unsigned long param3 = 0;
    switch (instruction) {
      case 1:
        // add param1 and param2
        param1 = mode.at(2) == '0' ? v[current + 1] : current + 1;
        param2 = mode.at(1) == '0' ? v[current + 2] : current + 2;
        param3 = mode.at(0) == '0' ? v[current + 3] : current + 3;
        param1 = mode.at(2) == '2' ? relative_base + v[current + 1] : current + 1;
        param2 = mode.at(1) == '2' ? relative_base + v[current + 2] : current + 2;
        param3 = mode.at(0) == '2' ? relative_base + v[current + 3] : current + 3;
        if(param1 >= 973) {
          param1 = 0;
        } else {
          param1 = v[param1];
        }
        if (param2 >= 973) {
          param2 = 0;
        }else {
          param2 = v[param2];
        }
        v[param3] = param1 + param2;
        current += 4;
        break;
      case 2:
        // multiply param1 by param2
        param1 = mode.at(2) == '0' ? v[current + 1] : current + 1;
        param2 = mode.at(1) == '0' ? v[current + 2] : current + 2;
        param3 = mode.at(0) == '0' ? v[current + 3] : current + 3;
        param1 = mode.at(2) == '2' ? relative_base + v[current + 1] : current + 1;
        param2 = mode.at(1) == '2' ? relative_base + v[current + 2] : current + 2;
        param3 = mode.at(0) == '2' ? relative_base + v[current + 3] : current + 3;
        if(param1 >= 973) {
          param1 = 0;
        } else {
          param1 = v[param1];
        }
        if (param2 >= 973) {
          param2 = 0;
        }else {
          param2 = v[param2];
        }
        v[param3] = param1 * param2;
        current += 4;
        break;
      case 3:
        param1 = mode.at(2) == '0' ? v[current + 1] : current + 1;
        param2 = mode.at(1) == '0' ? v[current + 2] : current + 2;
        param3 = mode.at(0) == '0' ? v[current + 3] : current + 3;
        param1 = mode.at(2) == '2' ? relative_base + v[current + 1] : current + 1;
        param2 = mode.at(1) == '2' ? relative_base + v[current + 2] : current + 2;
        param3 = mode.at(0) == '2' ? relative_base + v[current + 3] : current + 3;
        if(param1 >= 973) {
          param1 = 0;
        } else {
          param1 = v[param1];
        }
        // store input at position param1
        std::cout << "Param1 " << param1 << " input " << input << "\n";
        v[param1] = input;
        current += 2;
        break;
      case 4:
        //output value from param1
        param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
        std::cout << "Part 1: " << param1 << "\n";
        std::cout << "Vector length: " << v.size() << "\n";
        current += 2;
        break;
      case 5:
        //jump to param2 if param1 is non-zero
        param1 = mode.at(2) == '0' ? v[current + 1] : current + 1;
        param2 = mode.at(1) == '0' ? v[current + 2] : current + 2;
        param3 = mode.at(0) == '0' ? v[current + 3] : current + 3;
        param1 = mode.at(2) == '2' ? relative_base + v[current + 1] : current + 1;
        param2 = mode.at(1) == '2' ? relative_base + v[current + 2] : current + 2;
        param3 = mode.at(0) == '2' ? relative_base + v[current + 3] : current + 3;
        if(param1 >= 973) {
          param1 = 0;
        } else {
          param1 = v[param1];
        }
        if (param2 >= 973) {
          param2 = 0;
        }else {
          param2 = v[param2];
        }
        if (param1 != 0) {
          current = param2;
        } else {
          current += 3;
        }
        break;
      case 6:
        //jump to param2 if param1 is zero
        param1 = mode.at(2) == '0' ? v[current + 1] : current + 1;
        param2 = mode.at(1) == '0' ? v[current + 2] : current + 2;
        param1 = mode.at(2) == '2' ? relative_base + v[current + 1] : current + 1;
        param2 = mode.at(1) == '2' ? relative_base + v[current + 2] : current + 2;
        if(param1 >= 973) {
          param1 = 0;
        } else {
          param1 = v[param1];
        }
        if (param2 >= 973) {
          param2 = 0;
        }else {
          param2 = v[param2];
        }
        std::cout << "param1: " << param1 << " param2 " << param2  << "\n";
        if (param1 == 0) {
          current = param2;
        } else {
          current += 3;
        }
        std::cout << "current: " << current << "\n";
        break;
      case 7:
        //if param1 < param2, store 1 at param3
        param1 = mode.at(2) == '0' ? v[current + 1] : current + 1;
        param2 = mode.at(1) == '0' ? v[current + 2] : current + 2;
        param3 = mode.at(0) == '0' ? v[current + 3] : current + 3;
        param1 = mode.at(2) == '2' ? relative_base + v[current + 1] : current + 1;
        param2 = mode.at(1) == '2' ? relative_base + v[current + 2] : current + 2;
        param3 = mode.at(0) == '2' ? relative_base + v[current + 3] : current + 3;
        if(param1 >= 973) {
          param1 = 0;
        } else {
          param1 = v[param1];
        }
        if (param2 >= 973) {
          param2 = 0;
        }else {
          param2 = v[param2];
        }
        //param3 = mode.at(0) == '0' ? v[v[current + 3]] : v[current + 3];
        std::cout << "param1: " << param1 << " param2 " << param2  << " param3 " << param3 << "\n";
        if (param1 < param2) {
          v[param3] = 1;
        } else {
          v[param3] = 0;
        }
        current += 4;
        break;
      case 8:
        //if param1 equals param2, store 1 at param3
        param1 = mode.at(2) == '0' ? v[current + 1] : current + 1;
        param2 = mode.at(1) == '0' ? v[current + 2] : current + 2;
        param3 = mode.at(0) == '0' ? v[current + 3] : current + 3;
        param1 = mode.at(2) == '2' ? relative_base + v[current + 1] : current + 1;
        param2 = mode.at(1) == '2' ? relative_base + v[current + 2] : current + 2;
        param3 = mode.at(0) == '2' ? relative_base + v[current + 3] : current + 3;
        if(param1 >= 973) {
          param1 = 0;
        } else {
          param1 = v[param1];
        }
        if (param2 >= 973) {
          param2 = 0;
        }else {
          param2 = v[param2];
        }
        //param3 = mode.at(0) == '0' ? v[v[current + 3]] : v[current + 3];
        std::cout << "param1: " << param1 << " param2 " << param2  << " param3 " << param3 << "\n";
        if (param1 == param2) {
          v[param3] = 1;
        } else {
          v[param3] = 0;
        }
        current += 4;
        break;
      case 9:
        param1 = mode.at(2) == '0' ? v[current + 1] : current + 1;
        param2 = mode.at(1) == '0' ? v[current + 2] : current + 2;
        param1 = mode.at(2) == '2' ? relative_base + v[current + 1] : current + 1;
        param2 = mode.at(1) == '2' ? relative_base + v[current + 2] : current + 2;
        if(param1 >= 973) {
          param1 = 0;
        } else {
          param1 = v[param1];
        }
        if (param2 >= 973) {
          param2 = 0;
        }else {
          param2 = v[param2];
        }
        relative_base += param1;
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

