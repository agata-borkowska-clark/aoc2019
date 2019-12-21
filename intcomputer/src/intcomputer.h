#ifndef INTCOMP_H
#define INTCOMP_H

#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class intcomputer {
  public:
    // create an instance of the Integer Computer with a vector as instruction stream
    intcomputer(std::vector<long> v);
    // create an instance of the Integer Computer with a map as the instruction stream
    intcomputer(std::map<unsigned long, long> v);
    
    // add a value to the input list
    void queue_input(long input);
    
    // run the program
    std::vector<long> run();
    // run the program with a single input
    std::vector<long> run(long input);
    // run the program with a list of input values
    // It will replace any existing input with the new value.
    std::vector<long> run(std::deque<long> input);

  private:
    enum Instruction {
      ADDITION = 1,
      MULTIPLICATION = 2,
      INPUT = 3,
      OUTPUT = 4,
      JUMP_TRUE = 5,
      JUMP_FALSE = 6,
      LESS_THAN = 7,
      EQUALS = 8,
      ADJUST_BASE = 9,
      RETURN = 99
    };

    enum Mode {
      POSITION = '0',
      IMMEDIATE = '1',
      RELATIVE = '2'
    };

    std::map<unsigned long, long> local_mem;
    unsigned long relative_base = 0;
    unsigned long current = 0;  // current should always point at an instruction
    std::deque<long> input;
    std::vector<long> output;

    // manually move the pointer to an instruction
    void set_current(long x);
    // change the relative base
    void set_relative_base(long x);
    // split instruction into mode and the actual instruction
    std::pair<std::string, long> split_instruction(long i);
    // work out the mode for a parameter at a given location
    char supply_mode(std::string mode, int param_index);
    // given a raw parameter and the mode, figure out the value to use
    long obtain_value(long val, char mode);
    // provides an address where the result should be stored
    unsigned long supply_result_location(long val, char mode);
    // perform the instruction at current
    int perform_instruction();
};
#endif
