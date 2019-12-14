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

public std::vector<long> intcomputer::run(long  input) {
  this.input = new std::deque<long>(1, input);
  return run();
}

public std::vector<long> intcomputer::run(std::deque<long> input) {
  this.input = input;
  return run();
}

public void queue_input(long input) {
  this.input->push_back(input);
}

private std::pair<std::string, long> split_instruction(long i) {
  long instruction = i % 100;
  std::string mode = "000";
  std::string instruction_string = to_string(i);
  int index = instruction_string.length() - 3;
  int original_mode_length = index + 1;
  while (index >= 0) {
    mode[3 - original_mode_length + index] = instruction_string[index];
    --index;
  }
  return std::pair<std::string, logn> (mode, instruction);
}

private char supply_mode(std::string* mode, int param_index) {

}

private long obtain_value(long val, char mode) {

}

private voide perform_instruction() {
    // get instruction and mode
    std::pair<std:string, long> mode_instr_pair = split_instruction(*current);
    switch (pair->second) {
      case 1:

        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
      case 99:
        break;
      default:
        break;
    }

}
