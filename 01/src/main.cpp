#include <iostream>
#include <fstream>

int main() {
  std::fstream file("input.txt");
  int sum1;
  int a;
  while (file >> a) {
    sum1 += a / 3 - 2;
  }
  printf("Part 1: %d\n", sum1);

  std::fstream file2("input.txt");
  int sum2;
  int b;
  while (file2 >> b) {
    int temp_sum = b / 3 - 2;
    int temp = temp_sum;
    while (temp / 3 - 2 > 0) {
      temp = temp / 3 - 2;
      temp_sum += temp;
    }
    sum2 += temp_sum;
  }
  printf("Part 2: %d\n", sum2);
}

