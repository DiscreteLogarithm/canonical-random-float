#include <random>
#include <iostream>
#include <chrono>
#include "canonical_float_random.hpp"

int main () {
  using float_type = float;
  using URBG_type = std::mt19937;
  
  constexpr canonical_float_random<float_type, URBG_type> canonical_dist;
  constexpr auto sample_size = 1ull<<30;
  // we calculate the average to prevent the compiler from optimizing out everything
  // this is not a test of accuracy
  float_type x, avg = 0;
  URBG_type gen;
  std::chrono::high_resolution_clock::time_point t0, t;
  std::chrono::high_resolution_clock::duration dt_sum {};
  for (auto i=0ull; i<sample_size; ++i) {
    t0 = std::chrono::high_resolution_clock::now();
    x = canonical_dist (gen);
    t = std::chrono::high_resolution_clock::now();
    // online algorithm should be used to keep the contributions of small values without sorting the numbers first
    avg += (x-avg)/(i+1);
    // but duration uses integral type so the usuall average algorithm is fine
    dt_sum += t-t0;
  }
  std::cout << "canonical float random\naverage time per number: " << 1.*std::chrono::nanoseconds{dt_sum}.count()/sample_size << " ns" << std::endl;
  std::cout << "average of numbers (should be close to 1/2): " << avg << std::endl;
  return 0;
}
