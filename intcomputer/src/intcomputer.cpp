#include "intcomputer.h"

intcomputer::intcomputer(std::vector<long>* v) {
  for (int i = 0; i < v.size(); ++i) {
    local_mem[i] = v[i];
  }
}

intcomputer::intcomputer(std::map<unsigned long, long>* m) {
  local_mem = *m;
}

std::vector<long> intcomputer::run() {
  while (current < local_mem.size()) {
    // perform instructions
  }
  return output;
}

std::vector<long> intcomputer::run(long  input) {
  this.input = new std::deque<long>(1, input);
  return run();
}

std::vector<long> intcomputer::run(std::deque<long> input) {
  this.input = input;
  return run();
}

void queue_input(long input) {
  this.input->push_back(input);
}


void intcomputer::set_current(long x) {
  current = x;
}

void intcomputer::set_relative_base(long x) {
  relative_base = x;
}

std::pair<std::string, long> split_instruction(long i) {
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

char supply_mode(std::string* mode, int param_index) {
  return mode[3 - param_index];
}

long obtain_value(long val, char mode) {
  switch (mode) {
    case '0':
      return local_mem[val];
    case '1':
      return val;
    case '2':
      return local_mem[val + relative_base];
    default:
      std::cout << "incorrect mode provided: " << mode << "\n";
      return 0l;
  }
}

unsigned long supply_result_location(long val, char mode) {
  unsigned long location = mode == '0' ? (unsigned long) val : relative_base + (unsigned long) val;
  return location;
}

void perform_instruction() {
  // get instruction and mode
  std::pair<std:string, long> mode_instr_pair = split_instruction(*current);
  long param1, param2, result;
  switch (pair->second) {
    case ADDITION:
      param1 = obtain_value(local_mem[current + 1], supply_mode(pair->first, 1));
      param2 = obtain_value(local_mem[current + 2], supply_mode(pair->first, 2));
      result = param1 + param2;
      local_mem[supply_result_location(local_mem[current + 3], supply_mode(pair->first, 3))] = result;
      current += 4;
      break;
    case MULTIPLICATION:
      param1 = obtain_value(local_mem[current + 1], supply_mode(pair->first, 1));
      param2 = obtain_value(local_mem[current + 2], supply_mode(pair->first, 2));
      result = param1 * param2;
      local_mem[supply_result_location(local_mem[current + 3], supply_mode(pair->first, 3))] = result;
      current += 4;
      break;
    case INPUT:
      param1 = obtain_value(local_mem[current + 1], supply_mode(pair->first, 1));
      local_mem[param1] = input.pop_front();
      current += 2;
      break;
    case OUTPUT:
      param1 = obtain_value(local_mem[current + 1], supply_mode(pair->first, 1));
      output.push_back(param1);
      current += 2;
      break;
    case JUMP_TRUE:
      param1 = obtain_value(local_mem[current + 1], supply_mode(pair->first, 1));
      if (param1 != 0) {
        param2 = obtain_value(local_mem[current + 2], supply_mode(pair->first, 2));
        current = param2;
      } else {
        current += 3;
      }
      break;
    case JUMP_FALSE:
      param1 = obtain_value(local_mem[current + 1], supply_mode(pair->first, 1));
      if (param1 == 0) {
        param2 = obtain_value(local_mem[current + 2], supply_mode(pair->first, 2));
        current = param2;
      } else {
        current += 3;
      }
      break;
    case LESS_THAN:
      param1 = obtain_value(local_mem[current + 1], supply_mode(pair->first, 1));
      param2 = obtain_value(local_mem[current + 2], supply_mode(pair->first, 2));
      if (param1 < param2) {
        local_mem[supply_result_location(local_mem[current + 3], supply_mode(pair->first, 3))] = 1;
      } else {
        local_mem[supply_result_location(local_mem[current + 3], supply_mode(pair->first, 3))] = 0;
      }
      current += 4;
      break;
    case EQUALS:
      param1 = obtain_value(local_mem[current + 1], supply_mode(pair->first, 1));
      param2 = obtain_value(local_mem[current + 2], supply_mode(pair->first, 2));
      if (param1 == param2) {
        local_mem[supply_result_location(local_mem[current + 3], supply_mode(pair->first, 3))] = 1;
      } else {
        local_mem[supply_result_location(local_mem[current + 3], supply_mode(pair->first, 3))] = 0;
      }
      current += 4;
      break;
    case ADJUST_BASE:
      param1 = obtain_value(local_mem[current + 1], supply_mode(pair->first, 1));
      relative_base += param1;
      current += 2;
      break;
    case RETURN:
      break;
    default:
      std::cout << "Something went wrong; instruction not matched: " + pair->second;
      break;
  }
}
