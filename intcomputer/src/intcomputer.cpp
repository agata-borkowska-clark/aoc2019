#include "intcomputer.h"

public intcomputer::intcomputer(std::vector<long>* v) {
  for (int i = 0; i < v.size(); ++i) {
    local_mem[i] = v[i];
  }
}

public intcomputer::intcomputer(std::map<unsigned long, long>* m) {
  local_mem = *m;
}

public void intcomputer::set_current(long x) {
  current = x;
}

public std::vector<long> intcomputer::run() {
  while (current < local_mem.size()) {
    // perform instructions
  }
}





