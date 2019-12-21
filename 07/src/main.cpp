#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "../../intcomputer/src/intcomputer.h"

long create_and_run(long phase, long signal, const std::vector<long>& original) {
  intcomputer amp(original);
  amp.queue_input(phase);
  amp.queue_input(signal);
  std::vector<long> result = amp.run();
  return result[0];
};

int main() {
  long arr[5] = {0l, 1l, 2l, 3l, 4l};
  long max = 0l;
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
    long result = 0;
    std::cout << "Permutation: " << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << " " << arr[4] << "\n";
    for (int i = 0; i < 5; ++i) {
      result = create_and_run(arr[i], result, original);
    }
    std::cout << "end of run " << result << "\n";
    if (result > max) {
      max = result;
    }
  } while (std::next_permutation(arr, arr + 5));
  std::cout << "Part 1: " << max << "\n";
  return 0;  
}

