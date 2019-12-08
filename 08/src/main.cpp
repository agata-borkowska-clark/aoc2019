#include <iostream>
#include <fstream>
#include <map>
#include <string>

struct layer {
  std::string pixels;
  int zeroes = 0;
  int ones = 0;
  int twos = 0;
};
const int layer_size = 25 * 6;

int main() {
  std::fstream file("input.txt");
  std::map<std::string, layer> layer_map;
  char pixel;
  file >> pixel;
  std::string candidate_name;
  int candidate_count = layer_size;
  while (file.get(pixel)) {
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
      file >> pixel;
    }
    //std::cout << std::string(layer) << " " << zero_count << " " << one_count << " " << two_count << " " << ++count <<"\n";
    layer l;
    l.pixels = (std::string(layer_pixels));
    l.zeroes = zero_count;
    l.ones = one_count;
    l.twos = two_count;
    layer_map.emplace(l.pixels, l);
    if (zero_count < candidate_count) {
      candidate_count = l.zeroes;
      candidate_name = l.pixels;
    }
  }
  int a, b;
  a = layer_map.find(candidate_name)->second.ones;
  b = layer_map.find(candidate_name)->second.twos;
  std::cout << "Part 1: " << a * b << "\n";
}
