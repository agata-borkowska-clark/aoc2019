#ifndef INTCOMP_H
#define INTCOMP_H

#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class intcomputer {
  public:
    std::map<unsigned long, long> local_mem;
    unsigned long relative_base = 0;
    unsigned long current = 0;  // current should always point at an instruction
    std::deque<long> input = nullptr;

    // create an instance of the Integer Computer with a vector as instruction stream
    intcomputer(std::vector<long> v);
    // create an instance of the Integer Computer with a map as the instruction stream
    intcomputer(std::map<unsigned long, long> v);
    
    // manually move the pointer to an instruction
    // (calls to this method should be avoided)
    void set_current(long x);
    void set_relative_base(long x);
    
    // run the program
    std::vector<long> run();
    std::vector<long> run(int input);
    std::vector<long> run(std::vector<long> input);

  private:
    std::pair<std::string, int> split_instruction(int i);
    char supply_mode(std::string* mode, int param_index);
    long get_parameter(long val);
    void perform_instruction(long);
}
