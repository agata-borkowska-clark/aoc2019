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

  max = 0l;
  long arr2[5] = {5l, 6l, 7l, 8l, 9l};
  do {
    std::cout << "Permutation: " << arr2[0] << " " << arr2[1] << " " << arr2[2] << " " << arr2[3] << " " << arr2[4] << "\n";
    intcomputer ampA(original);
    ampA.queue_input(arr2[0]);
    intcomputer ampB(original);
    ampB.queue_input(arr2[1]);
    intcomputer ampC(original);
    ampC.queue_input(arr2[2]);
    intcomputer ampD(original);
    ampD.queue_input(arr2[3]);
    intcomputer ampE(original);
    ampE.queue_input(arr2[4]);
    long result = 0l;
    bool finished = false;
    while (!finished) {
      ampA.queue_input(result);
      result = ampA.run()[0];
      ampB.queue_input(result);
      result = ampB.run()[0];
      ampC.queue_input(result);
      result = ampC.run()[0];
      ampD.queue_input(result);
      result = ampD.run()[0];
      ampE.queue_input(result);
      result = ampE.run()[0];

      finished = ampE.is_done();
    }
    std::cout << "result " << result << "\n";
    if (result > max) {
      max = result;
    }
  } while (std::next_permutation(arr2, arr2 + 5));
  std::cout << "Part 2 " << max << "\n";
  return 0;  
}

