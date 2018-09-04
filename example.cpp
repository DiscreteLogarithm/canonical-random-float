#include <random>
#include <iostream>
#include "canonical_float_random.hpp"

int main () {
  constexpr canonical_float_random<float, std::mt19937> canonical_dist;
  std::mt19937 gen;
  std::cout << canonical_dist (gen) << std::endl;
  return 0;
}
