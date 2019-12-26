#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

int do_the_thing(std::vector<int> input, std::vector<int> pattern) {
  long long sum = 0;
  for (size_t i = 0; i < input.size(); ++i) {
    int mult = input[i] * pattern[(i + 1) % pattern.size()];
    //std::cout << "Mult: " << mult << " for i: " << (i + 1) % pattern.size() << " input: " << input[i] << " pattern " << pattern[(i + 1) % pattern.size()] << '\n';
    sum += mult;
    
  }
  sum = std::abs(sum);
  //std::cout << "sum: " << sum << "\n";
  return (int) (sum % 10);
};

std::vector<int> update_pattern(std::vector<int> pattern) {
  int repeats = (int) (pattern.size() / 4) + 1;
  // std::cout << "Repeats: " << repeats << "\n";
  std::vector<int> new_pattern;
  for (int i = 0; i < 4; ++i) {
    //std::cout << "Pattern i: " << pattern[i] << '\n';
    for (int j = 0; j < repeats; ++j) {
      new_pattern.push_back(pattern[i * (repeats - 1)]);
    } 
  }
  //std::cout << "new pattern size: " << new_pattern.size() << '\n';
  return new_pattern;
};

int main() {
  std::fstream file("input.txt");
  std::vector<int> input;
  char c;
  while (file >> c) {
    input.push_back(c - '0');
  }
  int length = input.size();
  std::vector<int> p2input;
  for (int i = 0; i < 10000; ++i) {
    for (int j = 0; j < length; ++j) {
      p2input.push_back(input[j]);
    }
  }
  std::vector<int> pattern;
  pattern.push_back(0);
  pattern.push_back(1);
  pattern.push_back(0);
  pattern.push_back(-1);
  std::vector<int> original_pattern = pattern;
  std::vector<int> output;
  for (int it = 0; it < 100; ++it) {
    //std::cout << "PHASE: " << it << '\n';
    for (size_t digit = 0; digit < input.size(); ++digit) {
      output.push_back(do_the_thing(input, pattern));
      pattern = update_pattern(pattern);
    }
    pattern = original_pattern;
    input = output;
    output.clear();
  }
  std::cout << "Part 1: ";
  for (size_t i = 0; i < 8; ++i) {
    std::cout << input[i];
  }
  std::cout << '\n';

  // PART 2
  pattern = original_pattern;
  for (int it = 0; it < 100; ++it) {
    //std::cout << "PHASE: " << it << '\n';
    for (size_t digit = 0; digit < p2input.size(); ++digit) {
      output.push_back(do_the_thing(p2input, pattern));
      pattern = update_pattern(pattern);
    }
    pattern = original_pattern;
    p2input = output;
    output.clear();
  }
  int offset = 0;
  int power = 1;
  for (int i = 6; i >= 0; --i) {
    offset += p2input[i] * power;
    power *= 10;
  }
  std::cout << "Offset: " << offset << '\n';
  std::cout << "Part 2: ";
  for (int i = offset; i < offset + 8; ++i) {
    std::cout << input[i];
  }
  std::cout << '\n';
}