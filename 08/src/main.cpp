#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

struct layer {
  std::string pixels;
  int zeroes = 0;
  int ones = 0;
  int twos = 0;
};
//const int layer_size = 2 * 2;
const int layer_size = 25 * 6;

int main() {
  std::fstream file("input.txt");
  std::map<std::string, layer> layer_map;
  std::vector<layer> stack;
  char pixel;
  std::string candidate_name;
  int candidate_count = layer_size;
  while (file >> pixel) {
    char layer_pixels[layer_size];
    int zero_count = 0;
    int one_count = 0;
    int two_count = 0;
    for (int i = 0; i < layer_size; ++i) {
      layer_pixels[i] = pixel;
      if (pixel == '0') {
        ++zero_count;
      } else if (pixel == '1') {
        ++one_count;
      } else {
        ++two_count;
      }
      if (i != layer_size - 1) {
        file >> pixel;
      }
    }
    //std::cout << std::string(layer) << " " << zero_count << " " << one_count << " " << two_count << " " << ++count <<"\n";
    layer l;
    l.pixels = (std::string(layer_pixels));
    l.zeroes = zero_count;
    l.ones = one_count;
    l.twos = two_count;
    layer_map.emplace(l.pixels, l);
    stack.push_back(l);
    if (zero_count < candidate_count) {
      candidate_count = l.zeroes;
      candidate_name = l.pixels;
    }
    //std::cout << l.pixels << "\n";
  }
  int a, b;
  a = layer_map.find(candidate_name)->second.ones;
  b = layer_map.find(candidate_name)->second.twos;
  std::cout << "Part 1: " << a * b << "\n";
  //std::cout << "layer count " << stack.size() << "\n"; 
  // Part 2
  char final_picture[layer_size];
  for (int i = 0; i < layer_size; ++i) {
    int depth = 0;
    char pixel = stack[depth].pixels.at(i);
    //std::cout << pixel << "\n";
    while (pixel == '2') {
      //std::cout << stack[depth].pixels << "\n";
      pixel = stack[++depth].pixels.at(i);
      //std::cout << pixel << "\n";
    }
    final_picture[i] = pixel;
  }
  std::cout << "Part 2:\n";
  for (int x = 0; x < 6; ++x) {
    for (int y = 0; y < 25; ++y) {
      char c = final_picture[x * 25 + y];
      if (c == '0') {
        std::cout << ' ';
      } else {
        std::cout << '#';
      }
    }
    std::cout << "\n";
  }
}

