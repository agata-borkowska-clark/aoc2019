#include <iostream>
#include <fstream>
#include <vector>

int main() {

  std::fstream file("input.txt");
  std::vector<int> original;
  int a;
  char comma;
  while (file >> a >> comma) {
    original.push_back(a);
  }   
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      std::vector<int> v = original;
      v.at(1) = i;
      v.at(2) = j;
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
	    if (v.at(0) == 19690720) {
	      printf("%d\n", i * 100 + j);
	      return 0;
	    } else {
	      current = v.size();
	    }
	    break;
          default:
	    printf("Something went wrong\n");
	    return 1;

	}
      }
    }
  }
  return 2;
}
