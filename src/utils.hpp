
#ifndef UTILS_HPP_
#define UTILS_HPP_
#include <iostream>
#include <stdint.h>
#include <string>

#define STRINGIFY(x) "x"

#define EPSILON 0.0001f
#define FOV M_PI / 2.0f

void print(std::string s);
void println(std::string s);

uint32_t get_color(uint8_t r, uint8_t g, uint8_t b);
double get_seconds();
void sleep_seconds(double time);

float degrees_to_radians(float degrees);
float radians_to_degrees(float radians);

std::string read_file(const std::string filename);

#endif
