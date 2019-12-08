#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
  int arr[5] = {0, 1, 2, 3, 4};
  int max = 0;
  std::fstream file("input.txt");
  std::vector<long> original;
  long a;
  char comma;
  while (file >> a >> comma) {
    original.push_back(a);
  }
  file >> a;
  original.push_back(a);
  do {
    int input = 0;
    std::cout << "Permutation: " << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << " " << arr[4] << "\n";
    for (int i = 0; i < 5; ++i) {
      bool phase_setting = true;
      std::vector<long> v = original;
      //int input_pointer = 0;
      //v[1] = 12;
      //v[2] = 2;
      unsigned long current = 0;
      bool running = true;
      while (running) {
        long instruction = v[current];
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
        // std::cout << "mode: " <<  mode << " instruction: " << instruction << " position: " << current <<"\n";
        long param1 = 0;
        long param2 = 0;
        long param3 = 0;
        switch (instruction) {
          case 1:
            // add param1 and param2
            param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
            param2 = mode.at(1) == '0' ? v[v[current + 2]] : v[current + 2];
            v[v[current + 3]] = param1 + param2;
            current += 4;
            break;
          case 2:
            // multiply param1 by param2
            param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
            param2 = mode.at(1) == '0' ? v[v[current + 2]] : v[current + 2];
            v[v[current + 3]] = param1 * param2;
            current += 4;
            break;
          case 3:
            // store input at position param1
            if (phase_setting) {
              v[v[current + 1]] = arr[i];
              phase_setting = false;
            } else {
              v[v[current + 1]] = input;
            }
            current += 2;
            break;
          case 4:
            //output value from param1
            param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
            //std::cout << "Instruction 4: " << param1 << "\n";
            input = param1;
            current += 2;
            break;
          case 5:
            //jump to param2 if param1 is non-zero
            param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
            param2 = mode.at(1) == '0' ? v[v[current + 2]] : v[current + 2];
            if (param1 != 0) {
              current = param2;
            } else {
              current += 3;
            }
            break;
          case 6:
            //jump to param2 if param1 is zero
            param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
            param2 = mode.at(1) == '0' ? v[v[current + 2]] : v[current + 2];
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
            param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
            param2 = mode.at(1) == '0' ? v[v[current + 2]] : v[current + 2];
            //param3 = mode.at(0) == '0' ? v[v[current + 3]] : v[current + 3];
            std::cout << "param1: " << param1 << " param2 " << param2  << " param3 " << param3 << "\n";
            if (param1 < param2) {
              v[v[current + 3]] = 1;
            } else {
              v[v[current + 3]] = 0;
            }
            current += 4;
            break;
          case 8:
            //if param1 equals param2, store 1 at param3
            param1 = mode.at(2) == '0' ? v[v[current + 1]] : v[current + 1];
            param2 = mode.at(1) == '0' ? v[v[current + 2]] : v[current + 2];
            //param3 = mode.at(0) == '0' ? v[v[current + 3]] : v[current + 3];
            std::cout << "param1: " << param1 << " param2 " << param2  << " param3 " << param3 << "\n";
            if (param1 == param2) {
              v[v[current + 3]] = 1;
            } else {
              v[v[current + 3]] = 0;
            }
            current += 4;
            break;
          case 99:
            running = false;
            break;
          default:
            std::cout << "Something went wrong, instruction: " << instruction << " mode: " << mode << "\n";
            return 1;
        }
      }
    }
    std::cout << "end of run " << input << "\n";
    if (input > max) {
      max = input;
    }
  } while (std::next_permutation(arr, arr + 5));
  std::cout << "Part 1: " << max << "\n";
  return 0;  
}

