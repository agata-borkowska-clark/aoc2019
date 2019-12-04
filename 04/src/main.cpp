#include <iostream>
#include <fstream>

int pow(int a, int b) {
  if (b == 0) {
    return 1;
  } else {
    return a * pow (a, b - 1);
  }
}

bool check_candidate(int x, bool is_part_one) {
  int split[6];
  for (int i = 0; i < 6; ++i) {
    split[i] = (x % pow(10, 6 - i)) / pow(10, 5 - i);
  }
  // check for non-descending
  for (int i = 1; i < 6; ++i) {
    if (split[i - 1] > split[i]) {
      return false;
    }
  }
  // check for repeated digit
  bool double_digit = false;
  for (int i = 1; i < 6; ++i) {
    if (split[i - 1] == split[i]) {
      if (is_part_one) {
        return true;
      } else {
        if ((i == 5 || (i < 5 && split[i] != split[i + 1]))
	    && (i == 1 || (i > 1 && split[i - 1] != split[i - 2]))) {
          double_digit = true;
	}
      }
    }
  }
  return !is_part_one && double_digit;
}
int main() {
  std::fstream file("input.txt");
  int lower, upper;
  char dash;
  file >> lower >> dash >> upper;
  printf("%d %d\n", lower, upper);
  int count1 = 0;
  int count2 = 0;
  for (int i = lower; i <= upper; ++i) {
    if (check_candidate(i, true)) {
      ++count1;
    }
    if (check_candidate(i, false)) {
      ++count2;
    }
  }
  printf("Part 1: %d\n", count1);
  printf("Part 2: %d\n", count2);
}




