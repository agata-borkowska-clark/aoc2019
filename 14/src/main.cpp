#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

constexpr unsigned long TRILLION = 1000000000000;
struct Ingredient {
  std::string name;
  long quantity;
};

using Cookbook = std::map<std::string, std::pair<long, std::vector<Ingredient>>>;

std::pair<std::string, std::pair<long, std::vector<Ingredient>>> parse_reaction(std::string line) {
  std::vector<Ingredient> ingredients;
  long quantity;
  std::string chemical;
  std::stringstream ss(line);
  while (ss) {
    ss >> quantity >> chemical;
    //std::cout << quantity << " " << chemical << " " ;
    if (quantity == 31 && false)
      std::cout << line << "\n";
    if (chemical[chemical.size() - 1] == ',') {
      chemical = chemical.substr(0, chemical.size() - 1);
    }
    if (quantity != 0) {
      Ingredient i;
      i.name = chemical;
      i.quantity = quantity;
      ingredients.push_back(i);
    }
  }
  std::string res = line.substr(line.find("=>") + 3, line.size());
  //std::cout << " => " << res << ": ";
  std::stringstream ssr(res);
  ssr >> quantity >> chemical;
  //std::cout << quantity << " " << chemical << "\n";
  return std::make_pair(chemical, std::make_pair(quantity, ingredients));
}

long ore_needed(std::string chemical, long quantity, const Cookbook& reactions, std::map<std::string, long>& excess) {
  //std::cout << "need " << quantity << " of " << chemical << "\n";
  if (excess.find(chemical) != excess.end()) {
    long excess_quantity = excess.find(chemical)->second;
    if (excess_quantity >= quantity) {
      excess[chemical] = excess_quantity - quantity;
      return 0;
    } else if (excess_quantity > 0) {
      excess[chemical] = 0;
      return ore_needed(chemical, quantity - excess_quantity, reactions, excess);
    }
  }
  if (reactions.find(chemical) == reactions.end()) {
    std::cout << "REACTION NOT FOUND, map size " << reactions.size() << "\n";
    return -1;
  }
  long reaction_outcome = reactions.find(chemical)->second.first;
  long multiplier = 0;
  if (quantity % reaction_outcome == 0) {
    multiplier = quantity / reaction_outcome;
  } else {
    multiplier = 1 + quantity / reaction_outcome;
    excess[chemical] = reaction_outcome - quantity % reaction_outcome;
  }
  long sum = 0;
  for (Ingredient i : reactions.find(chemical)->second.second) {
    if (i.name == "ORE") {
      sum += i.quantity * multiplier;
    } else {
      sum += ore_needed(i.name, i.quantity * multiplier, reactions, excess);
    }
  }
  return sum;
}

unsigned long bin_search(unsigned long a, unsigned long b, const Cookbook& reactions) {
  if (a + 1 == b) {
    return a;
  }
  unsigned long mid = a + (b - a) / 2;
  std::map<std::string, long> excess;
  unsigned long mid_fuel = ore_needed("FUEL", mid, reactions, excess);
  if (mid_fuel == TRILLION) {
    return mid_fuel;
  } else if (mid_fuel < TRILLION) {
    return bin_search(mid, b, reactions);
  } else {
    return bin_search(a, mid, reactions);
  }
}

int main() {
  std::fstream file("input.txt");
  Cookbook reactions;
  std::string line;
  while (std::getline(file, line)) {
    reactions.insert(parse_reaction(line));
    //reaction.insert(parse_reaction(line));
  }
  // we may create excess chemical that can be used later
  std::map<std::string, long> excess;
  long ore = ore_needed("FUEL", 1, reactions, excess);
  std::cout << "Part 1: " << ore << "\n";
  unsigned long div = TRILLION / ore;
  //std::cout << "Part 2: " << div << " needs " << div * ore + ore << " ore\n";
  std::cout << "Part 2: " << bin_search(div, div * 100L, reactions) << "\n"; 
}
