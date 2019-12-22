#include "intcomputer.h"

intcomputer::intcomputer(std::vector<long> v) {
  for (size_t i = 0; i < v.size(); ++i) {
    intcomputer::local_mem[i] = v[i];
  }
}

intcomputer::intcomputer(std::map<unsigned long, long> m) {
  intcomputer::local_mem = m;
}

std::vector<long> intcomputer::run() {
  int code = IN_PROGRESS;
  while (current < local_mem.size() && code == IN_PROGRESS) {
    code = intcomputer::perform_instruction();
  }
  return output;
}

std::vector<long> intcomputer::run(long  input) {
  intcomputer::input.push_back(input);
  return run();
}

std::vector<long> intcomputer::run(std::deque<long> input) {
  this->intcomputer::input = {input};
  return run();
}

void intcomputer::queue_input(long input) {
  this->input.push_back(input);
}

void intcomputer::consume_output() {
  output.erase(output.begin());
}

bool intcomputer::is_done() {
  return done;
}

void intcomputer::set_current(long x) {
  current = x;
}

void intcomputer::set_relative_base(long x) {
  relative_base = x;
}

std::pair<std::string, long> intcomputer::split_instruction(long i) {
  long instruction = i % 100;
  std::string mode = "000";
  std::string instruction_string = std::to_string(i);
  int index = instruction_string.length() - 3;
  int original_mode_length = index + 1;
  while (index >= 0) {
    mode[3 - original_mode_length + index] = instruction_string[index];
    --index;
  }
  return std::pair<std::string, long> (mode, instruction);
}

char intcomputer::supply_mode(std::string mode, int param_index) {
  return mode[3 - param_index];
}

long intcomputer::obtain_value(long val, char mode) {
  switch (mode) {
    case POSITION:
      return local_mem[val];
    case IMMEDIATE:
      return val;
    case RELATIVE:
      return local_mem[val + relative_base];
    default:
      std::cout << "incorrect mode provided: " << mode << "\n";
      return 1l;
  }
}

unsigned long intcomputer::supply_result_location(long val, char mode) {
  unsigned long location = mode == '0' ? (unsigned long) val : this->relative_base + (unsigned long) val;
  return location;
}

void intcomputer::finish_run() {
  done = true;
}

int intcomputer::perform_instruction() {
  // get instruction and mode
  std::pair<std::string, long> mode_instr_pair = split_instruction(local_mem[current]);
  long param1, param2, result;
  unsigned long loc;
  switch (mode_instr_pair.second) {
    case ADDITION:
      param1 = obtain_value(local_mem[current + 1], supply_mode(mode_instr_pair.first, 1));
      param2 = obtain_value(local_mem[current + 2], supply_mode(mode_instr_pair.first, 2));
      result = param1 + param2;
      loc = intcomputer::supply_result_location(local_mem[current + 3], supply_mode(mode_instr_pair.first, 3));
      local_mem[loc] = result;
      current += 4;
      break;
    case MULTIPLICATION:
      param1 = obtain_value(local_mem[current + 1], supply_mode(mode_instr_pair.first, 1));
      param2 = obtain_value(local_mem[current + 2], supply_mode(mode_instr_pair.first, 2));
      result = param1 * param2;
      loc = intcomputer::supply_result_location(local_mem[current + 3], supply_mode(mode_instr_pair.first, 3));
      local_mem[loc] = result;
      current += 4;
      break;
    case INPUT:
      if (intcomputer::input.size() == 0) {
        return WAITING;
      }
      loc = supply_result_location(local_mem[current + 1], supply_mode(mode_instr_pair.first, 1));
      local_mem[loc] = intcomputer::input.front();
      intcomputer::input.pop_front();
      current += 2;
      break;
    case OUTPUT:
      param1 = obtain_value(local_mem[current + 1], supply_mode(mode_instr_pair.first, 1));
      output.push_back(param1);
      current += 2;
      break;
    case JUMP_TRUE:
      param1 = obtain_value(local_mem[current + 1], supply_mode(mode_instr_pair.first, 1));
      if (param1 != 0) {
        param2 = obtain_value(local_mem[current + 2], supply_mode(mode_instr_pair.first, 2));
        current = param2;
      } else {
        current += 3;
      }
      break;
    case JUMP_FALSE:
      param1 = obtain_value(local_mem[current + 1], supply_mode(mode_instr_pair.first, 1));
      if (param1 == 0) {
        param2 = obtain_value(local_mem[current + 2], supply_mode(mode_instr_pair.first, 2));
        current = param2;
      } else {
        current += 3;
      }
      break;
    case LESS_THAN:
      param1 = obtain_value(local_mem[current + 1], supply_mode(mode_instr_pair.first, 1));
      param2 = obtain_value(local_mem[current + 2], supply_mode(mode_instr_pair.first, 2));
      if (param1 < param2) {
        local_mem[supply_result_location(local_mem[current + 3], supply_mode(mode_instr_pair.first, 3))] = 1;
      } else {
        local_mem[supply_result_location(local_mem[current + 3], supply_mode(mode_instr_pair.first, 3))] = 0;
      }
      current += 4;
      break;
    case EQUALS:
      param1 = obtain_value(local_mem[current + 1], supply_mode(mode_instr_pair.first, 1));
      param2 = obtain_value(local_mem[current + 2], supply_mode(mode_instr_pair.first, 2));
      if (param1 == param2) {
        local_mem[supply_result_location(local_mem[current + 3], supply_mode(mode_instr_pair.first, 3))] = 1;
      } else {
        local_mem[supply_result_location(local_mem[current + 3], supply_mode(mode_instr_pair.first, 3))] = 0;
      }
      current += 4;
      break;
    case ADJUST_BASE:
      param1 = obtain_value(local_mem[current + 1], supply_mode(mode_instr_pair.first, 1));
      relative_base += param1;
      current += 2;
      break;
    case RETURN:
      //std::cout << "Program completed run\n";
      // current += intcomputer::local_mem.size();
      finish_run();
      return SUCCESS;
      break;
    default:
      std::cout << "Something went wrong; instruction not matched: " << mode_instr_pair.second << "\n";
      current += intcomputer::local_mem.size();
      return WRONG_INSTR;
      break;
  }
  return IN_PROGRESS;
}
