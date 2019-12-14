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
    
    // manually move the pointer to an instruction
    // (calls to this method should be avoided)
    void set_current(long x);
    // change the relative base
    // calls to this method from other classes should be avoided)
    void set_relative_base(long x);
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
    std::map<unsigned long, long> local_mem;
    unsigned long relative_base = 0;
    unsigned long current = 0;  // current should always point at an instruction
    std::deque<long> input;

    std::pair<std::string, long> split_instruction(long i);
    char supply_mode(std::string* mode, int param_index);
    long obtain_value(long val, char mode);
    void perform_instruction();
}
