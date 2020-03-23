#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>
#include <set>
#include <stdint.h>
#include <string>
#include <thread>

#include "utils.hpp"

void print(std::string s) { std::cout << s; }

void println(std::string s) { std::cout << s << std::endl; }

uint32_t get_color(uint8_t r, uint8_t g, uint8_t b) {
  return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

float degrees_to_radians(float degrees) { return (degrees * M_PI / 180); }

float radians_to_degrees(float radians) { return (radians * 180 / M_PI); }

double get_seconds() { return (((double)clock()) / CLOCKS_PER_SEC); }

void sleep_seconds(double time) {
  std::chrono::microseconds sleeptime =
      std::chrono::microseconds((uint64_t)(1000 * 1000 * time));
  std::this_thread::sleep_for(sleeptime);
}

// from stack overflow
std::string read_file(std::string filename) {
  std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  } else
    return ("error");
}
