#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <vector>

struct body {
  std::string name;
  body* parent;
  std::vector<body*> orbitters;
  int orbit_count = 0;
};

int main() {
  body* com;
  std::map<std::string, body*> map;
  std::fstream file("input.txt");
  std::string line;
  int line_num = 0;
  while(std::getline(file, line)) {
    std::string object_a_name = line.substr(0, 3);
    std::string object_b_name = line.substr(4, 3);
    auto object_a = map.find(object_a_name);
    if (object_a == map.end()) {
      //std::cout << "line " << line_num << ": creating object a\n";
      auto object_a_new = std::make_pair(object_a_name, new body());
      object_a_new.second->name = object_a_name;
      map.insert(object_a_new);
    }
    object_a = map.find(object_a_name);
    
    if (object_a->first == "COM") {
      std::cout << "CoM found at line " << line_num << "\n";
      com = object_a->second;
    }
    auto object_b = map.find(object_b_name);
    if (object_b != map.end()) {
      // obj b seen already, update parent
      object_b->second->parent = object_a->second;
    } else {
      // obj b needs to be created
      auto object_b_new = std::make_pair(object_b_name, new body());
      object_b_new.second->name = object_b_name;
      object_b_new.second->parent = object_a->second;
      map.insert(object_b_new);
    }
    map.find(object_a_name)->second->orbitters.push_back(map.find(object_b_name)->second);
  }
  std::cout << "File parsed\n";
  std::queue<body*> to_process;
  for (auto const object : com->orbitters) {
    std::cout << "Orbitters of CoM\n" << object->orbit_count << '\n';
    object->orbit_count = 1;
    for (auto o : object->orbitters) {
      to_process.push(o);
    }
  }
  while (!to_process.empty()) {
    body* object = to_process.front();
    object->orbit_count = object->parent->orbit_count + 1;
    for (auto o : object->orbitters) {
      to_process.push(o);
    }
    to_process.pop();
  }
  int sum = 0;
  for (auto o : map) {
    sum += o.second->orbit_count;
  }
  std::cout << "Part 1: " << sum << "\n";
}
