#include <iostream>
#include <fstream>
#include <vector>

int main() {
  std::fstream file("input.txt");
  std::vector<int> v;
  int a;
  char comma;
  while (file >> a >> comma) {
    v.push_back(a);
  }
  v.at(1) = 12;
  v.at(2) = 2;
  unsigned long current = 0;
  while (current < v.size()) {
    switch (v.at(current)) {
      case 1:
	v.at(v.at(current + 3)) = v.at(v.at(current + 1)) + v.at(v.at(current + 2));
	current += 4;
        break;
      case 2:
	v.at(v.at(current + 3)) = v.at(v.at(current + 1)) * v.at(v.at(current + 2));
	current += 4;
	break;
      case 99:
	printf("%d\n", v.at(0));
	return 0;
      default:
	printf("Something went wrong\n");
	return 1;
    }
  }
}
